#pragma once
#include "document.h"

class render {
public:
	render() = default;
	virtual void draw(document* doc) = 0;
	
private:

};