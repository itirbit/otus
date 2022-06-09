#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>

void flush(std::vector<std::string>& buffer) {
	std::stringstream ss;
	for (std::size_t i = 0; i < buffer.size(); ++i) {
		ss << buffer[i];
		if (i+1 < buffer.size())
			ss << ", ";
	}
	ss << "\n";
	std::string filename = "bulk" + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) + ".log";

	std::fstream fs;
  	fs.open (filename, std::fstream::in | std::fstream::app);
  	fs << ss.rdbuf();
  	fs.close();

  	std::cout << ss.rdbuf()->str();
  	
	buffer.clear();
}

int main(int argc, char** argv) {
	int n = std::stoi(std::string(argv[1]));
	std::stack<std::string> s;
	std::vector<std::string> buffer;
	std::string line;
	while(getline(std::cin, line)) {
		//std::cout << line << "\n";
		if (line == "EOF") {
			if (s.empty()) {
				flush(buffer);
			}
			break;
		}
		else if (line == "{") {
			if (s.empty()) {
				flush(buffer);
			}
			s.push(line);
		}
		else if (line == "}") {
			if (s.empty() || s.top() == "}") {
				//wrong close command interpret as usual string
				buffer.push_back(line);
				if (buffer.size() >= n) {
					flush(buffer);
				}
				continue;
			}
			s.pop();
			if (s.empty()) {
				flush(buffer);
			}
		}
		else {
			buffer.push_back(line);
			if (s.empty() && buffer.size() >= n) {
				flush(buffer);
			}
		}
	}

	return 0;
}