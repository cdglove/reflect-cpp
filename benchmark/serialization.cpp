// *****************************************************************************
// 
// reveal/benchmark/serilization.cpp
//
// Benchmark serialization routines.
//
// Copyright Chris Glover 2016
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// ****************************************************************************
#include "benchmark/benchmark.h"

#include <sstream>
#include <fstream>
#include <memory>

#include <stdio.h>

#include "reveal/reflect_type.hpp"
#include "reveal/serialize/json_writer.hpp"
#include "reveal/serialize/json_reader.hpp"
#include "reveal/serialize/simple_binary_writer.hpp"
#include "reveal/serialize/simple_binary_reader.hpp"
#include "reveal/std/vector.hpp"
#include "../test/test_primitive_types.hpp"

#ifdef _WIN32

#include <Windows.h>
#include <io.h>

FILE* open_file(char const* file_name, char const* f)
{
	HANDLE file_handle = CreateFile(
		file_name,
		*f == 'r' ? GENERIC_READ : GENERIC_WRITE, 
		0,
		NULL,
		*f == 'r' ? OPEN_EXISTING : OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | (*f == 'w' ? FILE_FLAG_WRITE_THROUGH : 0),
		NULL
	);

	if (file_handle != INVALID_HANDLE_VALUE) 
	{
		int file_descriptor = _open_osfhandle((intptr_t)file_handle, 0);

		if (file_descriptor != -1) 
		{
			return _fdopen(file_descriptor, f);
		}
	}

	return NULL;
}
#else
char const* open_file(char const* file_name, char const* f)
{
	return file_name;
}
#endif

// -----------------------------------------------------------------------------
//
struct primitives_noctor : primitives
{};

template<typename Visitor>
decltype(auto) reflect(Visitor& v, reveal::version_t, reveal::tag<primitives_noctor>)
{
	return v.template base<primitives>();
}

struct primitives_blob : primitives_noctor
{
	primitives_blob()
	{}
};

template<typename Visitor>
decltype(auto) reflect(Visitor& v, reveal::version_t, reveal::tag<primitives_blob>)
{
	return v.pod();
}

struct memory_stream_buf
{
	char* gptr()
	{
		return &*get_;
	}

	typedef std::vector<char> buffer_t;
	buffer_t buffer_;
	buffer_t::iterator get_;
};

struct memory_stream
{
	void read(char* dest, std::size_t count)
	{
		//switch(count)
		{
		//case 1: read_impl_1(dest); break;
		//case 2: read_impl_2(dest); break;
		//case 4: read_impl_4(dest); break;
		//case 8: read_impl_8(dest); break;
		//default:
			auto first = buffer_.get_;
			buffer_.get_ += count;
			//std::copy(first, get_, dest);
			std::memcpy(dest, &*first, count);
		};

	}

	void write(char const* src, std::size_t count)
	{
		std::copy(src, src + count, std::back_inserter(buffer_.buffer_));
	}

	void seekg(std::size_t off)
	{
		buffer_.get_ = buffer_.buffer_.begin() + off;
	}

	std::size_t tellg()
	{
		return buffer_.get_ - buffer_.buffer_.begin();
	}

	memory_stream_buf* rdbuf()
	{
		return &buffer_;
	}

private:

	memory_stream_buf buffer_;
};

//struct memory_stream2
//{
//	void read(char* dest, std::size_t count)
//	{
//		auto first = get_;
//		get_ += count;
//		std::copy(first, get_, dest);
//	}
//
//	template<std::size_t count>
//	void read(char* dest)
//	{
//		auto first = get_;
//		get_ += count;
//		std::copy(first, get_, dest);
//	}
//
//	template<>
//	void read<1>(char* dest)
//	{
//		*dest = *get_;
//		++get_;
//	}
//
//	template<>
//	void read<2>(char* dest)
//	{
//		auto first = get_;
//		get_ += 2;
//		typedef std::uint16_t type;
//		type* src_ = reinterpret_cast<type*>(&*first);
//		type* dest_ = reinterpret_cast<type*>(dest);
//		*dest_ = *src_;
//	}
//
//	template<>
//	void read<4>(char* dest)
//	{
//		auto first = get_;
//		get_ += 4;
//		typedef std::uint32_t type;
//		type* src_ = reinterpret_cast<type*>(&*first);
//		type* dest_ = reinterpret_cast<type*>(dest);
//		*dest_ = *src_;
//	}
//	
//	template<>
//	void read<8>(char* dest)
//	{
//		auto first = get_;
//		get_ += 8;
//		typedef std::uint64_t type;
//		type* src_ = reinterpret_cast<type*>(&*first);
//		type* dest_ = reinterpret_cast<type*>(dest);
//		*dest_ = *src_;
//	}
//
//	void write(char const* src, std::size_t count)
//	{
//		std::copy(src, src + count, std::back_inserter(buffer_));
//	}
//
//	void seekg(std::size_t off)
//	{
//		get_ = buffer_.begin() + off;
//	}
//
//	typedef std::vector<char> buffer_t;
//	buffer_t buffer_;
//	buffer_t::iterator get_;
//};

#define BENCHMARK_TEST(x) \
    BENCHMARK(x)->Arg(8)->Arg(512)->Arg(8192)->Arg(1024 * 1024)->Arg(10 * 1024 * 1024)

static void BM_MemCpy(benchmark::State& state) 
{
	auto src = std::make_unique<primitives[]>(state.range_x());
	auto dest = std::make_unique<primitives[]>(state.range_x());
	std::memcpy(src.get(), dest.get(), sizeof(primitives) * state.range_x());
	while (state.KeepRunning())
	{
		std::memcpy(dest.get(), src.get(), sizeof(primitives) * state.range_x());
		benchmark::DoNotOptimize(dest);
	}
}
BENCHMARK_TEST(BM_MemCpy);

static void BM_BinaryRead(benchmark::State& state) 
{
	std::vector<primitives> obj(state.range_x());
	memory_stream archive;
	reveal::serialize::simple_binary_writer binary_writer;
	binary_writer(obj, archive);

	reveal::serialize::simple_binary_reader binary_reader;

	while (state.KeepRunning())
	{
		obj.clear();
		archive.seekg(0);
		binary_reader(obj, archive);
		benchmark::DoNotOptimize(obj);
	}
}
BENCHMARK_TEST(BM_BinaryRead);

static void BM_BinaryReadBlob(benchmark::State& state) 
{
	std::vector<primitives_blob> obj(state.range_x());
	memory_stream archive;
	reveal::serialize::simple_binary_writer binary_writer;
	binary_writer(obj, archive);

	reveal::serialize::simple_binary_reader binary_reader;

	while (state.KeepRunning())
	{
		obj.clear();
		archive.seekg(0);
		binary_reader(obj, archive);
		benchmark::DoNotOptimize(obj);
	}
}
BENCHMARK_TEST(BM_BinaryReadBlob);

//static void BM_BinaryRead2(benchmark::State& state) 
//{
//	std::vector<primitives> obj(state.range_x());
//	memory_stream2 archive;
//	reveal::serialize::simple_binary_writer binary_writer;
//	binary_writer(obj, archive);
//
//	reveal::serialize::simple_binary_reader binary_reader;
//
//	while (state.KeepRunning())
//	{
//		obj.clear();
//		archive.seekg(0);
//		binary_reader(obj, archive);
//		benchmark::DoNotOptimize(obj);
//	}
//}
//BENCHMARK_TEST(BM_BinaryRead2);

static void BM_MemCpyFile(benchmark::State& state) 
{
	auto src = std::make_unique<primitives[]>(state.range_x());
	std::ofstream out(open_file("test.bin", "w"));
	out.write(reinterpret_cast<char const*>(src.get()), sizeof(primitives) * state.range_x());
	out.close();
	auto dest = std::make_unique<primitives[]>(state.range_x());
	while (state.KeepRunning())
	{
		std::ifstream in(open_file("test.bin", "r"));
		in.read(reinterpret_cast<char*>(dest.get()), sizeof(primitives) * state.range_x());
		benchmark::DoNotOptimize(dest);
		in.close();
	}
}
BENCHMARK_TEST(BM_MemCpyFile);

static void BM_BinaryReadFile(benchmark::State& state) 
{
	std::vector<primitives> obj(state.range_x());
	std::ofstream archive_out(open_file("test.bin", "w"));
	reveal::serialize::simple_binary_writer binary_writer;
	binary_writer(obj, archive_out);
	archive_out.close();

	reveal::serialize::simple_binary_reader binary_reader;

	while (state.KeepRunning())
	{
		std::ifstream archive_in(open_file("test.bin", "r"));
		obj.clear();
		binary_reader(obj, archive_in);
		benchmark::DoNotOptimize(obj);
		archive_in.close();
	}
}
BENCHMARK_TEST(BM_BinaryReadFile);

static void BM_BinaryReadFileBlob(benchmark::State& state) 
{
	std::vector<primitives_blob> obj(state.range_x());
	std::ofstream archive_out(open_file("test.bin", "w"));
	reveal::serialize::simple_binary_writer binary_writer;
	binary_writer(obj, archive_out);
	archive_out.close();

	reveal::serialize::simple_binary_reader binary_reader;

	while (state.KeepRunning())
	{
		std::ifstream archive_in(open_file("test.bin", "r"));
		obj.clear();
		binary_reader(obj, archive_in);
		benchmark::DoNotOptimize(obj);
		archive_in.close();
	}
}
BENCHMARK_TEST(BM_BinaryReadFileBlob);
