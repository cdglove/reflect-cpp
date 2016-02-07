#include <vector>
#include <iostream>

#include "reflect/reflect_type.hpp"
#include "reflect/serialize/print_names.hpp"
#include "test_user_types.hpp"

int main()
{
	ns::Parent1 obj;
	obj.f_.a_ = 1;
	obj.f_.b_ = 2;
	obj.s_.c_.push_back(3);
	obj.s_.c_.push_back(4);
	obj.s_.d_ = 4;

	// //schema r;
	// //r.root(obj);

	// //print_name_visitor p;
	// //r.recurse(p);

	// std::cout << "Structure: " << std::endl;
	// print_name name_printer;
	reflect::reflector<
		ns::Parent1, 
		reflect::serialize::print_names
	> name_printer;

	name_printer(std::cout);
	// using reflection::reflect;
	// reflect(name_printer, 0, static_cast<ns::Parent1*>(nullptr));

	// std::cout << "Initial Values: " << std::endl;
	// reflector<print_value> value_printer;
	// value_printer(obj);

	// std::stringstream outs;
	// save_archive<std::stringstream> s(outs);
	// s(obj);

	// obj.f_.a_ = 0;
	// obj.f_.b_ = 0;
	// obj.s_.c_.clear();
	// obj.s_.d_ = 0;

	// std::cout << "Values post-save:" << std::endl;
	// value_printer(obj);

	// load_archive<std::stringstream> l(outs);
	// l(obj);

	// std::cout << "Values post-load:" << std::endl;
	// value_printer(obj);

	return 0;
}