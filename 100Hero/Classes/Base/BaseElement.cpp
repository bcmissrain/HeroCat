#include "BaseElement.h"

int BaseElement::elementCodeCounter = 0;

BaseElement::BaseElement()
{
	elementCodeCounter++;
	this->_elementCode = elementCodeCounter;
}

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

void BaseElement::afterUpdate()
{
	this->_LastRect = getBoundingBox();
}

cocos2d::Rect BaseElement::getBoundingBox()
{
	return cocos2d::Rect(getVisualCenter() - getVisualSize() / 2, getVisualSize());
}

cocos2d::Size BaseElement::getVisualSize()
{
	return boundingBoxSize;
}

cocos2d::Point BaseElement::getVisualCenter()
{
	return this->convertToWorldSpace(this->getPosition());
}