#include "TransparentCat.h"
#include "../Levels/BaseLevel.h"
USING_NS_CC;

HeroType TransparentCat::getHeroType()
{
	return HeroType::TransparentCat;
}

bool TransparentCat::init()
{
	this->setTag(ELEMENT_HERO_TAG);
	this->_BaseScale = 0.25f;
	this->_BaseRunSpeed = 280;
	this->_JumpTime = 0.3f;
	this->_JumpHeight = 210;
	this->_CanDoubleJump = false;
	this->_IsDoubleJump = false;
	this->_JumpTime2 = 0.2f;
	this->_JumpHeight2 = 160;
	_Sprite = static_cast<cocostudio::timeline::SkeletonNode*>(CSLoader::createNode("Cheet.csb"));
	this->addChild(_Sprite);
	_SpriteTimeline = CSLoader::createTimeline("Cheet.csb");
	_SpriteTimeline->retain();
	_Sprite->runAction(_SpriteTimeline);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	auto _Weapon = Sprite::create("point.png");
#else
	auto _Weapon = Node::create();
#endif
	this->_Sprite->addChild(_Weapon, 100);
	_Weapon->setPosition(Vec2(getVisualSize().width / 2, 0));
	this->_Weapons.pushBack(_Weapon);

	initElement();
	return true;
}

bool TransparentCat::initElement()
{
	//init jump info
	float revTime = 0;
	if (_JumpTime != 0)
	{
		revTime = 1 / _JumpTime;
	}
	_BaseJumpAcceleration = _JumpHeight * 2 * revTime * revTime;
	_BaseJumpSpeed = _JumpTime * _BaseJumpAcceleration;

	//init jump2 info
	float revTime2 = 0;
	if (_JumpTime2 != 0)
	{
		revTime2 = 1 / _JumpTime2;
	}
	_BaseJumpAcceleration2 = _JumpHeight2 * 2 * revTime2 * revTime2;
	_BaseJumpSpeed2 = _JumpTime2 * _BaseJumpAcceleration2;

	_IsValid = true;
	_CanClean = false;
	this->_AttackState = AttackState::NotAttack;
	_AttackColdTime = 0.2f;
	this->_Sprite->setScale(_BaseScale);
	this->setRotation(0);
	changeStateTo(ActionState::Stand);
	_BeginBorn();
	return true;
}

void TransparentCat::_BeginStand()
{
	_SpriteTimeline->gotoFrameAndPause(0);
}

void TransparentCat::_BeginRun()
{
	_SpriteTimeline->gotoFrameAndPlay(0, 20, true);
}

void TransparentCat::_BeginJumpUp()
{
	_SpriteTimeline->gotoFrameAndPlay(30, 40, false);
	this->_JumpSpeed = this->_BaseJumpSpeed + _SupportSpeed;
}

void TransparentCat::_BeginJumpUp2()
{
	this->_IsDoubleJump = true;
	_SpriteTimeline->gotoFrameAndPlay(38, 40, false);
	this->_JumpSpeed2 = this->_BaseJumpSpeed2;
}

void TransparentCat::_BeginJumpDown()
{
	_SpriteTimeline->gotoFrameAndPlay(40, 45, false);
}

void TransparentCat::_BeginJumpFinish()
{
	this->_JumpSpeed = 0;
	this->_JumpSpeed2 = 0;
	_SpriteTimeline->gotoFrameAndPlay(50, 55, false);
	this->_IsDoubleJump = false;
}

void TransparentCat::onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
	if (!this->_IsValid)
	{
		return;
	}

	if (gameElement)
	{
		auto ele = (BaseFloor*)gameElement;
		if (ele)
		{
			this->_SupportSpeed = ele->_SupportJumpSpeed;
		}
	}

	switch (opType)
	{
	case CollideOperate::CollideLeft:
		this->setPositionX(point.x - _Sprite->getBoundingBox().size.width * 0.5f);
		break;
	case CollideOperate::CollideRight:
		this->setPositionX(point.x + _Sprite->getBoundingBox().size.width *0.5f);
		break;
	case CollideOperate::CollideUp:
		_CollideState = CollideState::HaveSupport;
		this->setPositionY(point.y + _Sprite->getBoundingBox().size.height* 0.35f);
		break;
	case CollideOperate::CollideDown:
		_CollideState = CollideState::HeadCollide;
		this->_JumpSpeed = this->_JumpSpeed2 = 0;
		this->setPositionY(point.y - _Sprite->getBoundingBox().size.height*0.65f);
		break;
	default:
		break;
	}
}

void TransparentCat::onWallCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
	if (!this->_IsValid)
	{
		return;
	}

	switch (opType)
	{
	case CollideOperate::CollideLeft:
		this->setPositionX(point.x - _Sprite->getBoundingBox().size.width * 0.7f);
		_onWallCollide();
		break;
	case CollideOperate::CollideRight:
		this->setPositionX(point.x + _Sprite->getBoundingBox().size.width *0.7f);
		_onWallCollide();
		break;
	case CollideOperate::CollideUp:
		_CollideState = CollideState::HaveSupport;
		this->setPositionY(point.y + _Sprite->getBoundingBox().size.height* 0.32f);
		break;
	case CollideOperate::CollideDown:
		_CollideState = CollideState::HeadCollide;
		this->setPositionY(point.y - _Sprite->getBoundingBox().size.height*0.68f);
		break;
	default:
		break;
	}
}

void TransparentCat::onEnemyCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
	if (!this->_IsValid)
	{
		return;
	}
	if (this->_IsBorning)
	{
		return;
	}
	if (this->_isTransparent)
	{
		return;
	}

	this->setRotation(180);
	this->_IsValid = false;
}

void TransparentCat::_BeginAttack()
{
	_isTransparent = !_isTransparent;
	if (_isTransparent)
	{
		this->removeAllChildren();
		_Sprite = static_cast<cocostudio::timeline::SkeletonNode*>(CSLoader::createNode("Transparent.csb"));
		this->addChild(_Sprite);
		_SpriteTimeline = CSLoader::createTimeline("Transparent.csb");
		_SpriteTimeline->retain();
		_Sprite->runAction(_SpriteTimeline);
		this->_Sprite->setScale(_BaseScale);
		if (_Direction == Direction::Left)
		{
			this->_Sprite->setScaleX(-_BaseScale);
		}
	}
	else
	{
		this->removeAllChildren();
		_Sprite = static_cast<cocostudio::timeline::SkeletonNode*>(CSLoader::createNode("Cheet.csb"));
		this->addChild(_Sprite);
		_SpriteTimeline = CSLoader::createTimeline("Cheet.csb");
		_SpriteTimeline->retain();
		_Sprite->runAction(_SpriteTimeline);
		this->_Sprite->setScale(_BaseScale);
		if (_Direction == Direction::Left)
		{
			this->_Sprite->setScaleX(-_BaseScale);
		}
	}
}

void TransparentCat::_Attack(ClickState clickState)
{
	if (!this->_IsValid)
	{
		return;
	}

	if (_AttackMaxTimes > 0)
	{
		if (_AttackCount >= _AttackMaxTimes)
			return;
	}
	
	if (clickState == ClickState::Begin)
	{
		_BeginAttack();
	}
}