#pragma once
#include "documentSystem.h"

class documentSystemInstance {
public:
	static documentSystem* getInstance() {
		static documentSystem instance;
		return &instance;
	}
};