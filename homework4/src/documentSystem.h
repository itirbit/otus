#pragma once
#include "document.h"

class documentSystem {
public:
	documentSystem() = default;
	~documentSystem() {}

	void create(const std::string& name) {}
	void open(std::string path) {}
	void save(std::string path) {}
	document* getDocument() { return currentDocument; }
	
private:
	document* currentDocument = nullptr;
};