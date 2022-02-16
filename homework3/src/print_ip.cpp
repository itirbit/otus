#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <type_traits>
#include <limits>


template <typename T>
using EnableIfString = std::enable_if_t<std::is_convertible_v<T, std::string>>;

template <typename T>
using EnableIfNonString = std::enable_if_t<!std::is_convertible_v<T, std::string>>;

template <typename T>
using EnableIfInt = std::enable_if_t<std::is_convertible_v<T, int>>;

template <typename T, typename Fake = EnableIfString<T>>
void print_ip(T t, Fake* f = nullptr) {
	std::cout << t << "\n";
}

template<typename T, typename Fake = EnableIfInt<T>>
void print_ip(T val) {
	int bytes = sizeof(T);
	for (int i = (8 * bytes - 8); i >= 0; i -= 8) {
		std::cout << ((val >> i) & 255);
		if (i != 0)
			std::cout << ".";
	}
	std::cout << "\n";
}

template<typename T, typename Fake = EnableIfNonString<T>>
auto print_ip(T arr) -> decltype(arr.size()) {
	int i = 0;
	for (auto val : arr) {
		std::cout << val;
		if (i != arr.size()-1)
			std::cout << ".";
		++i;
	}
	std::cout << "\n";
	return arr.size();
}

int main() {
	print_ip(int8_t{ -1 }); // 255
	print_ip(int16_t{ 0 }); // 0.0
	print_ip(int32_t{ 2130706433 }); // 127.0.0.1
	print_ip(int64_t{ 8875824491850138409 });// 123.45.67.89.101.112.131.41
	print_ip(std::string{"Hello, World!"}); // Hello, World!
	print_ip(std::vector<int>{100, 200, 300, 400}); // 100.200.300.400
	print_ip(std::list<short>{400, 300, 200, 100}); // 400.300.200.100

	return 0;
}