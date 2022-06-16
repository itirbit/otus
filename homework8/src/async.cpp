#include "async.h"

void asyncLogger::connect(int n){
	threads.push_back(std::thread(&asyncLogger::flushToFile, this, 2));
	threads.push_back(std::thread(&asyncLogger::flushToFile, this, 1));
	threads.push_back(std::thread(&asyncLogger::flushToLog, this));
}

void asyncLogger::disconnect(){
	while (true) {
		if (bufferToFile.empty() && bufferToLog.empty())
			break;
	}
	done = true;
	for (auto& t : threads) {
		t.join();
	}
}

void asyncLogger::receive(std::vector<std::string> buffer){
	flush(buffer);
}

void asyncLogger::flushToFile(int n) {
	while (!done) {
		std::unique_lock lk(mutexToFile);
		if (bufferToFile.empty() && !done)
			cvFile.wait(lk);
		else {
			std::stringstream ss;
			for (std::size_t i = 0; i < bufferToFile.size(); ++i) {
				ss << bufferToFile[i];
				if (i + 1 < bufferToFile.size())
					ss << ", ";
			}
			bufferToFile.clear();
			ss << "\n";
			std::string filename = "bulk" + std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) + "_" + std::to_string(n) + ".log";

			std::fstream fs;
			fs.open(filename, std::fstream::in | std::fstream::app);
			fs << ss.rdbuf();
			fs.close();
		}
	}
}

void asyncLogger::flushToLog() {
	while (!done) {
		std::unique_lock lk(mutexToLog);
		if (bufferToLog.empty() && !done)
			cvLog.wait(lk);
		else {
			std::stringstream ss;
			for (std::size_t i = 0; i < bufferToLog.size(); ++i) {
				ss << bufferToLog[i];
				if (i + 1 < bufferToLog.size())
					ss << ", ";
			}
			bufferToLog.clear();
			ss << "\n";
			std::cout << ss.rdbuf()->str();
		}
	}
}

void asyncLogger::flush(std::vector<std::string>& buffer) {
	{
		std::unique_lock lk(mutexToFile);
		bufferToFile.insert(bufferToFile.end(), buffer.begin(), buffer.end());
		cvFile.notify_all();
	}
	{
		std::unique_lock lk(mutexToLog);
		bufferToLog.insert(bufferToLog.end(), buffer.begin(), buffer.end());
		cvLog.notify_all();
	}
	buffer.clear();
}