#include <iostream>
#include <map>
#include <iostream>
#include "reserveAllocator.h"
#include "simpleContainer.h"

int getFactorial(int n) {
	if (n <= 1)
		return n;
	return n * getFactorial(n - 1);
}

int main(int, char* []) {
	std::map<int, int> usualMap;

	for (int i = 0; i < 10; ++i) {
		usualMap[i] = getFactorial(i);
	}
	for (int i = 0; i < 10; ++i) {
		std::cout << i << " " << usualMap[i] << "\n";
	}

	auto reserveMap = std::map<
		int,
		int,
		std::less<int>,
		reserveAllocator<
		std::pair<
		const int, int>, 10>>{};

	for (int i = 0; i < 10; ++i) {
		reserveMap[i] = getFactorial(i);
	}
	for (int i = 0; i < 10; ++i) {
		std::cout << i << " " << reserveMap[i] << "\n";
	}

	simpleContainer<int> simpleArray(10);
	for (int i = 0; i < 10; ++i) {
		simpleArray.push_back(i);
	}
	for (auto i : simpleArray) {
		std::cout << i << " ";
	}
	std::cout << "\n";

	simpleContainer<int, reserveAllocator<int, 10>> reserveArray(10);
	for (int i = 0; i < 10; ++i) {
		reserveArray.push_back(i);
	}
	for (auto i : simpleArray) {
		std::cout << i << " ";
	}
	std::cout << "\n";

	return 0;
}