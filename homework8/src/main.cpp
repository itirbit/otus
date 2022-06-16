#include "async.h"
#include <vector>
#include <string>

int main(int argc, char** argv) {
	int n = std::stoi(std::string(argv[1]));
	asyncLogger handler;
	handler.connect(n);
	for(int i = 1; i < 100; ++i) {
		std::vector<std::string> v;
		v.reserve(i);
		for(auto j = 0; j < i; ++j){
			v.push_back(std::string("command") + std::to_string(j));
		}
		handler.receive(v);
	}
	handler.disconnect();
	return 0;
}