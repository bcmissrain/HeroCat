#include "UIRunningNode.h"
#define MOVE_TIME_ONCE 0.02f
USING_NS_CC;

UIRunningNode* UIRunningNode::create(int target, float totalTime,std::string fontName,float fontSize)
{
	UIRunningNode *pRet = new(std::nothrow) UIRunningNode();
	if (pRet && pRet->init(target,totalTime,fontName,fontSize))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool UIRunningNode::init(int target, float totalTime, std::string fontName, float fontSize)
{
	if (!Node::init())
	{
		return false;
	}
	this->_totalTime = totalTime;
	this->_targetInt = target;
	this->_targetStr = Value(target).asString();
	this->_labelSize = _targetStr.length();
	this->_fontName = fontName;
	this->_fontSize = fontSize;

	if (_totalTime < 0 || _targetInt < 0)
	{
		return false;
	}
	auto dealSize = getContentSize() / 2;
	for (int i = 0; i < _labelSize; i++)
	{
		Label* lable = Label::create(Value(i % 10).asString(), _fontName, _fontSize);
		lable->setTag(i);
		this->addChild(lable);
		lable->setPosition(Vec2(i*lable->getBoundingBox().size.width - dealSize.width, 0));
		CCLOG("Label Pos %d (%f,%f,%f,%f)", i, lable->getPositionX(), lable->getPositionY(), lable->getBoundingBox().size.width, lable->getBoundingBox().size.height);
	}

	return true;
}

void UIRunningNode::beginRun()
{
	if (_totalTime < 0 || _targetInt < 0)
	{
		return;
	}

	auto moveAction = Sequence::create(DelayTime::create(MOVE_TIME_ONCE), CallFunc::create([=](){
		for (int i = 0; i < _labelSize; i++)
		{
			Label* label = (Label*)this->getChildByTag(i);
			if (label)
			{
				int value = Value(label->getString()).asInt();
				value = (value + 1) % 10;
				label->setString(Value(value).asString());
			}
		}
	}), NULL);
	
	auto stopAction = CallFunc::create([=](){
		for (int i = 0; i < _labelSize; i++)
		{
			Label* label = (Label*)this->getChildByTag(i);
			if (label)
			{
				int num = (int)(_targetInt / pow(10, _labelSize - i - 1)) % 10;
				label->setString(Value(num).asString());
			}
		}
	});
	int repeatTime = _totalTime / MOVE_TIME_ONCE;
	this->runAction(Sequence::create(Repeat::create(moveAction,repeatTime),stopAction,NULL));
}

Size UIRunningNode::getContentSize()
{
	if (_labelSize <= 0)
	{
		return Size::ZERO;
	}
	else
	{
		auto labelSize = Label::create("0", _fontName, _fontSize)->getBoundingBox().size;
		return Size(_labelSize*labelSize.width, labelSize.height);
	}
}