#include <iostream>
#include <tuple>
#include <cassert>
#include "matrix.h"

int main(int, char* []) {
	Matrix<int, -1> matrix;
	assert(matrix.size() == 0);
	const auto a = matrix[0][0];
	assert(a == -1);
	assert(matrix.size() == 0);
	matrix[100][100] = 314;
	assert(matrix[100][100] == 314);
	assert(matrix.size() == 1);
	// выведется одна строка
	// 100100314
	for(auto c: matrix)
	{
		int x;
		int y;
		int v;
	 	std::tie(x, y, v) = c;
	 	std::cout << x << y << v << "\n";
	}

	int n = 10;
	Matrix<int, -1> testMatrix;
	for(int i = 0; i < n; ++i) {
		testMatrix[i][i] = i;
		testMatrix[i][n-1-i] = n-1-i;
	}

	std::cout << testMatrix.size() << "\n";

	for(int i = 1; i < n-1; ++i) {
		for(int j = 1; j < n-1; ++j) {
			std::cout << testMatrix[i][j] << "  ";
		}
		std::cout << "\n";
	}

	for(auto c: testMatrix)
	{
		int x;
		int y;
		int v;
	 	std::tie(x, y, v) = c;
	 	std::cout << "matrix[" << x << "]" << "[" << y << "]" << "=" << v << "\n";
	}

	return 0;
}