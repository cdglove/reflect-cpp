#include <iostream>
#include <vector>
#include <type_traits>
#include <sstream>
#include "function_traits.hpp"

// class schema : public reflector<schema>
// {
// public:

// 	schema()
// 	{}

// 	template<typename Member>
// 	schema(char const* name, Member member)
// 	{
// 		static_assert(sizeof(node<Member>) <= sizeof(node_), "doesn't fit");
// 		new(&node_) node<Member>(name, member);
// 	}

// 	template<typename Composite, typename Parent>
// 	void visit_composite(char const* name, Composite Parent::*member)
// 	{
// 		children_.push_back(schema(name, member));
// 		reflect(children_.back(), 0, static_cast<Composite*>(nullptr));
// 	}

// 	template<typename Primitive, typename Parent>
// 	void visit_primitive(char const* name, Primitive Parent::*member)
// 	{
// 		children_.push_back(schema(name, member));		
// 	}

// 	template<typename Container, typename SizeType>
// 	void visit_container_size(SizeType (Container::*fn)() const)
// 	{

// 	}

// 	template<typename Container, typename RetType, typename ValueType>
// 	void visit_container_items(RetType (Container::*fn)(ValueType))
// 	{

// 	}

// 	template<typename T>
// 	void root(T& t)
// 	{
// 		new(&node_) node_base("root");
// 		reflect(*this, 0, static_cast<T*>(nullptr));
// 	}

// 	template<typename Visitor>
// 	void recurse(Visitor& v)
// 	{
// 		for(auto&& child : children_)
// 		{
// 			v(child);
// 			child.recurse(v);
// 		}
// 	}

// //private:

// 	struct node_base
// 	{
// 		node_base(char const* name)
// 			: name_(name)
// 		{}

// 		char const* name_;
// 	};

// 	node_base* get_node()
// 	{
// 		return reinterpret_cast<node_base*>(&node_);
// 	}

// 	node_base const* get_node() const
// 	{
// 		return reinterpret_cast<node_base const*>(&node_);
// 	}

// 	template<typename Member>
// 	struct node : node_base
// 	{
// 		node(char const* name, Member member)
// 			: node_base(name)
// 			, member_(member)
// 		{}

// 		Member member_;
// 	};

// 	std::aligned_storage<24, 8>::type node_;
// 	std::vector<schema> children_;
// };

template<typename T>
class print_value
{
public:
	print_value(T& t)
		: instance_(t)
	{}

	template<typename Child, typename Parent>
	void member(char const* name, Child Parent::*member)
	{
	 	print_value<Child> print_child(instance_.*member);
	 	using reflection::reflect;
		reflect(print_child, 0, static_cast<Child*>(nullptr));
	}

	template<typename SizeFun, typename InsertFun>
	void container(SizeFun size, InsertFun)
	{
		std::cout << size(instance_) << std::endl;

		typedef std::decay_t<
			typename function_traits<InsertFun>::template argument<1>::type
		> value_type;

		for(auto&& i : instance_)
		{
			print_value<value_type> print_child(i);
			using reflection::reflect;
			reflect(print_child, 0, static_cast<value_type*>(nullptr));
		}
	}

	void primitive()
	{
		std::cout << instance_ << std::endl;
	}

	T& instance_;
};

template<typename T, typename Stream>
class save_values
{
public:
	save_values(T& t, Stream& s)
		: instance_(t)
		, stream_(s)
	{}

	template<typename Child, typename Parent>
	void member(char const* name, Child Parent::*member)
	{
	 	save_values<Child, Stream> save_child(instance_.*member, stream_);
	 	using reflection::reflect;
		reflect(save_child, 0, static_cast<Child*>(nullptr));
	}

	template<typename SizeFun, typename InsertFun>
	void container(SizeFun size, InsertFun insert)
	{
		auto num_elements = size(instance_);
		stream_.write(reinterpret_cast<char const*>(&num_elements), sizeof(num_elements));

		typedef std::decay_t<
			typename function_traits<InsertFun>::template argument<1>::type
		> value_type;

		for(auto&& i : instance_)
		{
			save_values<value_type, Stream> save_child(i, stream_);
			using reflection::reflect;
			reflect(save_child, 0, static_cast<value_type*>(nullptr));
		}
	}

	void primitive()
	{
		stream_.write(reinterpret_cast<char const*>(&instance_), sizeof(instance_));
	}

private:

	T& instance_;
	Stream& stream_;
};

template<typename Stream>
class save_archive
{
public:

	save_archive(Stream& s)
		: stream_(s)
	{}

	template<typename T>
	void operator()(T& t)
	{
		save_values<T, Stream> save(t, stream_);
		using reflection::reflect;
		reflect(save, 0, static_cast<T*>(nullptr));
	}

private:

	Stream& stream_;
};

template<typename T, typename Stream>
class load_values
{
public:
	load_values(T& t, Stream& s)
		: instance_(t)
		, stream_(s)
	{}

	template<typename Child, typename Parent>
	void member(char const* name, Child Parent::*member)
	{
	 	load_values<Child, Stream> load_child(instance_.*member, stream_);
		reflect(load_child, 0, static_cast<Child*>(nullptr));
	}

	template<typename SizeFun, typename InsertFun>
	void container(SizeFun size, InsertFun insert)
	{
		auto num_elements = size(instance_);
		stream_.read(reinterpret_cast<char*>(&num_elements), sizeof(num_elements));

		typedef std::decay_t<
			typename function_traits<InsertFun>::template argument<1>::type
		> value_type;

		for(std::size_t i = 0; i < num_elements; ++i)
		{
			value_type value;
			load_values<value_type, Stream> load_child(value, stream_);
			using reflection::reflect;
			reflect(load_child, 0, static_cast<value_type*>(nullptr));
			insert(instance_, std::move(value));
		}
	}

	void primitive()
	{
		stream_.read(reinterpret_cast<char*>(&instance_), sizeof(instance_));
	}

private:

	T& instance_;
	Stream& stream_;
};

template<typename Stream>
class load_archive
{
public:

	load_archive(Stream& s)
		: stream_(s)
	{}

	template<typename T>
	void operator()(T& t)
	{
		load_values<T, Stream> load(t, stream_);
		using reflection::reflect;
		reflect(load, 0, static_cast<T*>(nullptr));
	}

	Stream& stream_;
};

class print_name
{
public:

	template<typename Child, typename Parent>
	void member(char const* name, Child Parent::*member)
	{
		std::cout << name << std::endl;
		using reflection::reflect;
		reflect(*this, 0, static_cast<Child*>(nullptr));
	}

	template<typename SizeFun, typename InsertFun>
	void container(SizeFun size, InsertFun insert)
	{
		typedef std::decay_t<
			typename function_traits<InsertFun>::template argument<1>::type
		> value_type;

		using reflection::reflect;
		reflect(*this, 0, static_cast<value_type*>(nullptr));
	}

	void primitive()
	{}
};

namespace ns
{
	struct Child1
	{
		int a_;
		float b_;
	};

	template<typename Visitor>
	void reflect(Visitor& v, reflection::version_t, Child1* p)
	{
		v.member("a_", &Child1::a_);
		v.member("b_", &Child1::b_);
	}

	struct Child2
	{
		std::vector<double> c_;
		unsigned int d_;
	};

	template<typename Visitor>
	void reflect(Visitor& v, reflection::version_t, Child2*)
	{
		v.member("c_", &Child2::c_);
		v.member("d_", &Child2::d_);
	}

	struct Parent1
	{
		Child1 f_;
		Child2 s_;
	};

	template<typename Visitor>
	void reflect(Visitor& v, reflection::version_t, Parent1*)
	{
		v.member("f_", &Parent1::f_);
		v.member("s_", &Parent1::s_);
	}
}

template<typename Visitor, typename T, typename Allocator>
void reflect(Visitor& v, reflection::version_t, std::vector<T, Allocator>*)
{
	v.container(
		[](std::vector<T, Allocator> const& v) { return v.size(); },
		[](std::vector<T, Allocator>& v, T&& i) { return v.push_back(std::forward<T>(i)); }
	);
}

int main()
{
	ns::Parent1 obj;
	obj.f_.a_ = 1;
	obj.f_.b_ = 2;
	obj.s_.c_.push_back(3);
	obj.s_.c_.push_back(4);
	obj.s_.d_ = 4;

	//schema r;
	//r.root(obj);

	//print_name_visitor p;
	//r.recurse(p);

	std::cout << "Structure: " << std::endl;
	print_name name_printer;
	using reflection::reflect;
	reflect(name_printer, 0, static_cast<ns::Parent1*>(nullptr));

	std::cout << "Initial Values: " << std::endl;
	reflector<print_value> value_printer;
	value_printer(obj);

	std::stringstream outs;
	save_archive<std::stringstream> s(outs);
	s(obj);

	obj.f_.a_ = 0;
	obj.f_.b_ = 0;
	obj.s_.c_.clear();
	obj.s_.d_ = 0;

	std::cout << "Values post-save:" << std::endl;
	value_printer(obj);

	load_archive<std::stringstream> l(outs);
	l(obj);

	std::cout << "Values post-load:" << std::endl;
	value_printer(obj);
}