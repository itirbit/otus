#pragma once
#include <cstddef>
#include <memory>

template <typename T, typename Allocator = std::allocator<T>> 
struct simpleContainer {
	simpleContainer(int size) {
		capacity = size;
		data = alloc.allocate(capacity+1);
		endVal = data;
	}
	~simpleContainer(){
		alloc.deallocate(data, capacity+1);
	}
	T* begin() {
		return data;
	}

	T* end() {
		return endVal;
	}

	void push_back(T val) {
		data[counter++] = val;
		endVal = data + counter;
	}

	std::size_t capacity;
	std::size_t counter = 0;
	T* data;
	T* endVal = nullptr;
	Allocator alloc;
};