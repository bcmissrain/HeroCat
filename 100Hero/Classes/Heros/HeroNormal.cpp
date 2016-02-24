#include "HeroNormal.h"
#include "../Weapons/Bianbian.h"
USING_NS_CC;

bool HeroNormal::init()
{
	this->_BaseScale = 0.5f;
	this->_BaseRunSpeed = 400;
	this->_BaseAcceleration = 4;
	this->_JumpTime = 0.3f;
	this->_JumpHeight = 200;
	this->_CanDoubleJump = true;
	this->_IsDoubleJump = false;
	this->_JumpTime2 = 0.2f;
	this->_JumpHeight2 = 160;
	this->setTag(ELEMENT_HERO_TAG);
	this->_AttackState = AttackState::NotAttack;
	_AttackColdTime = 3;

	_Sprite = static_cast<cocostudio::timeline::SkeletonNode*>(CSLoader::createNode("Hulu.csb"));
	this->addChild(_Sprite);
	_SpriteTimeline = CSLoader::createTimeline("Hulu.csb");
	_SpriteTimeline->retain();
	_Sprite->runAction(_SpriteTimeline);
	this->_Sprite->setScale(_BaseScale);
	changeStateTo(ActionState::Stand);


	auto _Weapon = Sprite::create("point.png");
	this->_Sprite->addChild(_Weapon,100);
	_Weapon->setPosition(Vec2(getVisualSize().width/2, 0));
	this->_Weapons.pushBack(_Weapon);
	return true;
}

void HeroNormal::_BeginStand()
{
	_SpriteTimeline->gotoFrameAndPause(0);
}

void HeroNormal::_BeginRun()
{
	_SpriteTimeline->gotoFrameAndPlay(0, 20, true);
}

void HeroNormal::_BeginJumpUp()
{
	_SpriteTimeline->gotoFrameAndPlay(30,40,false);
	auto jumpUpAction = EaseOut::create(MoveBy::create(_JumpTime, Vec2(0, _JumpHeight)),2.0);
	jumpUpAction->setTag(ACTION_TAG_JUMP_UP);
	this->runAction(jumpUpAction);
}

void HeroNormal::_BeginJumpUp2()
{
	this->stopActionByTag(ACTION_TAG_JUMP_DOWN);
	this->stopActionByTag(ACTION_TAG_JUMP_UP);
	this->_IsDoubleJump = true;
	_SpriteTimeline->gotoFrameAndPlay(38, 40, false);
	auto jumpUpAction = EaseOut::create(MoveBy::create(_JumpTime2, Vec2(0, _JumpHeight2)), 2.0);
	jumpUpAction->setTag(ACTION_TAG_JUMP_UP_2);
	this->runAction(jumpUpAction);
}

void HeroNormal::_BeginJumpDown()
{
	this->stopActionByTag(ACTION_TAG_JUMP_UP);
	this->stopActionByTag(ACTION_TAG_JUMP_UP_2);
	_SpriteTimeline->gotoFrameAndPlay(40, 45, false);
	auto jumpDownAction = EaseIn::create(MoveBy::create(_JumpTime * 2, Vec2(0, -_JumpHeight * 4)),2.0);
	jumpDownAction->setTag(ACTION_TAG_JUMP_DOWN);
	this->runAction(jumpDownAction);
}

void HeroNormal::_BeginJumpFinish()
{
	this->stopActionByTag(ACTION_TAG_JUMP_DOWN);
	_SpriteTimeline->gotoFrameAndPlay(50, 55, false);
	this->_IsDoubleJump = false;
}

void HeroNormal::onFloorCollide(cocos2d::Point point, CollideOperate opType,BaseElement* gameElement)
{
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

void HeroNormal::onWallCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
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

void HeroNormal::_Attack(ClickState clickState)
{
	if (_AttackMaxTimes > 0)
	{
		if (_AttackCount >= _AttackMaxTimes)
			return;
	}

	if (_AttackState == AttackState::NotAttack)
	{		
		if (clickState == ClickState::Begin)
		{
			_SpriteTimeline->gotoFrameAndPlay(60, 70, false);
			_SpriteTimeline->setLastFrameCallFunc([=](){
				if (_SpriteTimeline->getCurrentFrame() == 70)
				{
					if (this->_CurrentState->getState() == ActionState::Run || this->_CurrentState->getState() == ActionState::Stop)
					{
						this->_BeginRun();
					}
					_SpriteTimeline->setLastFrameCallFunc(nullptr);
				}	
			});
			_eventDispatcher->dispatchCustomEvent("Bianbian", this);
			CCLOG("Add Bianbian");
			_AttackState = AttackState::Attacking;
			_AttackCount++;
			this->scheduleOnce([=](float delta){
				_AttackState = AttackState::NotAttack;
			}, _AttackColdTime, "yeah");
		}
	}
}