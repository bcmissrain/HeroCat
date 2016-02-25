#include "FloorNormal.h"

bool FloorNormal::init()
{
	this->setTag(ELEMENT_FLOOR_TAG);
	initElement();
	return true;
}