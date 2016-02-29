#include "CheetahCat.h"
#include "../Levels/BaseLevel.h"
#include "../Weapons/Bianbian.h"
USING_NS_CC;

bool CheetahCat::init()
{
	this->setTag(ELEMENT_HERO_TAG);
	this->_BaseScale = 0.25f;
	this->_BaseRunSpeed = 500;
	//this->_BaseAcceleration = 6;
	this->_JumpTime = 0.3f;
	this->_JumpHeight = 210;
	this->_CanDoubleJump = true;
	this->_IsDoubleJump = false;
	this->_JumpTime2 = 0.2f;
	this->_JumpHeight2 = 160;
	_Sprite = static_cast<cocostudio::timeline::SkeletonNode*>(CSLoader::createNode("Cheet.csb"));
	this->addChild(_Sprite);
	_SpriteTimeline = CSLoader::createTimeline("Cheet.csb");
	_SpriteTimeline->retain();
	_Sprite->runAction(_SpriteTimeline);

	auto _Weapon = Sprite::create("point.png");
	this->_Sprite->addChild(_Weapon, 100);
	_Weapon->setPosition(Vec2(getVisualSize().width / 2, 0));
	this->_Weapons.pushBack(_Weapon);

	initElement();
	return true;
}

bool CheetahCat::initElement()
{
	_IsValid = true;
	_CanClean = false;
	this->_AttackState = AttackState::NotAttack;
	_AttackColdTime = 0.2f;
	this->_Sprite->setScale(_BaseScale);
	this->setRotation(0);
	changeStateTo(ActionState::Stand);
	return true;
}

void CheetahCat::_BeginStand()
{
	_SpriteTimeline->gotoFrameAndPause(0);
}

void CheetahCat::_BeginRun()
{
	_SpriteTimeline->gotoFrameAndPlay(0, 20, true);
}

void CheetahCat::_BeginJumpUp()
{
	_SpriteTimeline->gotoFrameAndPlay(30, 40, false);
	auto jumpUpAction = EaseOut::create(MoveBy::create(_JumpTime, Vec2(0, _JumpHeight)), 2.0);
	jumpUpAction->setTag(ACTION_TAG_JUMP_UP);
	this->runAction(jumpUpAction);
}

void CheetahCat::_BeginJumpUp2()
{
	this->stopActionByTag(ACTION_TAG_JUMP_DOWN);
	this->stopActionByTag(ACTION_TAG_JUMP_UP);
	this->_IsDoubleJump = true;
	_SpriteTimeline->gotoFrameAndPlay(38, 40, false);
	auto jumpUpAction = EaseOut::create(MoveBy::create(_JumpTime2, Vec2(0, _JumpHeight2)), 2.0);
	jumpUpAction->setTag(ACTION_TAG_JUMP_UP_2);
	this->runAction(jumpUpAction);
}

void CheetahCat::_BeginJumpDown()
{
	this->stopActionByTag(ACTION_TAG_JUMP_UP);
	this->stopActionByTag(ACTION_TAG_JUMP_UP_2);
	_SpriteTimeline->gotoFrameAndPlay(40, 45, false);
	auto jumpDownAction = EaseIn::create(MoveBy::create(_JumpTime * 2, Vec2(0, -_JumpHeight * 4)), 2.0);
	/*Sequence::create(EaseIn::create(MoveBy::create(_JumpTime , Vec2(0, -_JumpHeight)), 2.0),
	MoveBy::create(_JumpTime*4,Vec2(0,-_JumpHeight*4)),
	NULL);*/
	jumpDownAction->setTag(ACTION_TAG_JUMP_DOWN);
	this->runAction(jumpDownAction);
}

void CheetahCat::_BeginJumpFinish()
{
	this->stopActionByTag(ACTION_TAG_JUMP_DOWN);
	_SpriteTimeline->gotoFrameAndPlay(50, 55, false);
	this->_IsDoubleJump = false;
}

void CheetahCat::onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
	if (!this->_IsValid)
	{
		return;
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

void CheetahCat::onWallCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
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

void CheetahCat::onEnemyCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
	if (!this->_IsValid)
	{
		return;
	}
	this->setRotation(180);
	this->_IsValid = false;
}

void CheetahCat::_BeginAttack()
{
	if (_AttackState == AttackState::NotAttack)
	{
		_SpriteTimeline->gotoFrameAndPlay(60, 75, false);
		_SpriteTimeline->setLastFrameCallFunc([=](){
			if (_SpriteTimeline->getCurrentFrame() == 75)
			{
				if (this->_CurrentState->getState() == ActionState::Run || this->_CurrentState->getState() == ActionState::Stop)
				{
					this->_BeginRun();
				}
				_SpriteTimeline->setLastFrameCallFunc(nullptr);
			}
		});
		_eventDispatcher->dispatchCustomEvent("Cheetah", this);

		_AttackCount++;
		this->scheduleOnce([=](float delta){
			_AttackState = AttackState::NotAttack;
		}, _AttackColdTime, "attack");
		_AttackState = AttackState::Attacking;
	}
}

void CheetahCat::_Attack(ClickState clickState)
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