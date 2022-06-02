#pragma once
#include "document.h"
#include "render.h"

class defaultRender : public render {
public:
	defaultRender() = default;
	virtual void draw(document* doc) override {};
	
private:

};