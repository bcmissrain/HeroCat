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

cocos2d::Rect BaseElement::getDetectingBox()
{
	if (getJumpState() == DropState::Still)
	{
		return getBoundingBox();
	}
	else if (getJumpState() == DropState::Up)
	{
		float width = getVisualSize().width;
		float height = getVisualSize().height+getMaxJumpSpeed();
		return cocos2d::Rect(getVisualCenter() - getVisualSize(), cocos2d::Size(width, height));
	}
	else if (getJumpState() == DropState::Down)
	{
		float width = getVisualSize().width;
		float height = getVisualSize().height + getMaxJumpSpeed();
		auto beginPos = getVisualCenter() - getVisualSize();
		beginPos.y -= getMaxJumpSpeed();
		return cocos2d::Rect(beginPos, cocos2d::Size(width, height));
	}
}