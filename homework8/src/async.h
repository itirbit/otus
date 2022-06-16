#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <thread>
#include <condition_variable>
#include <mutex>

class asyncLogger {
public:
	void connect(int n);
	void disconnect();
	void receive(std::vector<std::string> buffer);
	void flushToFile(int n);
	void flushToLog();
	void flush(std::vector<std::string>& buffer);

private:
	std::vector<std::thread> threads;
	std::condition_variable cvLog;
	std::condition_variable cvFile;
	std::mutex mutexToFile;
	std::mutex mutexToLog;
	std::vector<std::string> bufferToLog;
	std::vector<std::string> bufferToFile;
	bool done = false;

};