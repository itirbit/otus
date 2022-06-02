#pragma once
#include "document.h"
#include "render.h"

class darkModeRender : public render {
public:
	darkModeRender() = default;
	virtual void draw(document* doc) override {};
	
private:

};