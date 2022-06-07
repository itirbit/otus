#pragma once
#include <unordered_map>
#include <vector>
#include <tuple>

template <typename T, T Value>
struct Row {
	Row() {
		defaultValue = Value;
	}

	T& operator[](int i) {
		if (data.find(i) == data.end())
			data[i] = defaultValue;
		return data[i];
	}

	const T& operator[](int i) const {
		return data[i];
	}

	std::unordered_map<int, T>& getData() {
		return data;
	}
private:
	std::unordered_map<int, T> data;
	T defaultValue;
};

template <typename T, T defaultValue>
class Matrix {
public:
	typename std::vector<std::tuple<int,int,T>>::iterator begin() {
		calculateIterators();
		return iterators.begin();
	}

	typename std::vector<std::tuple<int,int,T>>::iterator end() {
		return iterators.end();
	}

	Row<T, defaultValue>& operator[](int i) {
		return data[i];
	}

	const Row<T, defaultValue>& operator[](int i) const {
		return data[i];
	}

	std::size_t size() {
		std::size_t ans = 0; 
		for(auto row : data) {
			auto mapa = row.second.getData();
			for(auto entry : mapa) {
				if (entry.second != defaultValue)
					++ans;
			}
		}
		return ans;
	}
private:

	void calculateIterators() {
		iterators.clear();
		for (auto row : data) {
			auto mapa = row.second.getData();
			for(auto entry : mapa) {
				if (entry.second != defaultValue)
					iterators.push_back(std::make_tuple(row.first, entry.first, entry.second));
			}
		}
	}

	std::unordered_map<int, Row<T, defaultValue>> data;
	std::vector<std::tuple<int,int,T>> iterators;
};
