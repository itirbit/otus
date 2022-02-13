#pragma once
#include <memory>

template <typename T, size_t S>
struct reserveAllocator {
	using value_type = T;

	using pointer = T *;
	using const_pointer = const T *;
	using reference = T &;
	using const_reference = const T &;

	template <typename U>
	struct rebind {
		using other = reserveAllocator<U,S>;
	};

	reserveAllocator() {
		size = S;
		mem = std::malloc(size * sizeof(T));
	};
	~reserveAllocator() {
		std::free(mem);
	}

	template <typename U>
	reserveAllocator(const reserveAllocator<U, S> & o) {

	}

	T *allocate(std::size_t n) {
		auto offset = counter * sizeof(T);
		if (counter > size) {
			throw std::bad_alloc();
		}
		counter += n;
		return reinterpret_cast<T*>(static_cast<char*>(mem) + offset);
	}

	void deallocate(T *p, std::size_t n) {

	}

	template <typename U, typename... Args>
	void construct(U *p, Args &&...args) {
		new (p) U(std::forward<Args>(args)...);
	};

	template <typename U>
	void destroy(U *p) {
		p->~U();
	}

	void* mem;
	size_t size = 0;
	size_t counter = 0;
};