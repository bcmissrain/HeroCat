#include "BaseElement.h"

bool BaseElement::init()
{
	initElement();
	return true;
}

bool BaseElement::initElement()
{
	_IsValid = true;
	_CanClean = false;
	return true;
}