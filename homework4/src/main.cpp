#include <iostream>
#include <map>
#include <iostream>
#include "documentSystemInstance.h"
#include "documentSystem.h"
#include "defaultRender.h"

int main(int, char* []) {
	defaultRender render;
	auto doc = documentSystemInstance::getInstance()->getDocument();
	render.draw(doc);
	return 0;
}