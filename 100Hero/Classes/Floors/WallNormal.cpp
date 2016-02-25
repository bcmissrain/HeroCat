#include "WallNormal.h"

bool WallNormal::init()
{
	this->setTag(ELEMENT_FLOOR_TAG);
	initElement();
	return true;
}