#include "IronCat.h"
#include "../Levels/BaseLevel.h"
#include "../Weapons/Bianbian.h"
USING_NS_CC;

HeroType IronCat::getHeroType()
{
	return HeroType::IronCat;
}

bool IronCat::init()
{
	this->setTag(ELEMENT_HERO_TAG);
	this->_BaseScale = 0.28f;
	this->_BaseRunSpeed = 500;
	this->_BaseAcceleration = 6;
	this->_JumpTime = 0.3f;
	this->_JumpHeight = 150;
	this->_CanDoubleJump = true;
	this->_IsDoubleJump = false;
	this->_JumpTime2 = 0.3f;
	this->_JumpHeight2 = 140;
	_Sprite = static_cast<cocostudio::timeline::SkeletonNode*>(CSLoader::createNode("IronCat.csb"));
	this->addChild(_Sprite);
	_SpriteTimeline = CSLoader::createTimeline("IronCat.csb");
	_SpriteTimeline->retain();
	_Sprite->runAction(_SpriteTimeline);

#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
	auto _Weapon = Sprite::create("point.png");
#else
	auto _Weapon = Node::create();
#endif
	this->_Sprite->addChild(_Weapon, 100);
	_Weapon->setPosition(Vec2(getVisualSize().width / 1.8f, 0));
	this->_Weapons.pushBack(_Weapon);

	initElement();
	return true;
}

bool IronCat::initElement()
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
	_AttackColdTime = 0.20f;
	this->_Sprite->setScale(_BaseScale);
	this->setRotation(0);
	changeStateTo(ActionState::Stand);
	_BeginBorn();
	return true;
}

void IronCat::_BeginStand()
{
	_SpriteTimeline->gotoFrameAndPause(0);
}

void IronCat::_BeginRun()
{
	_SpriteTimeline->gotoFrameAndPlay(0, 20, true);
}

void IronCat::_BeginJumpUp()
{
	_SpriteTimeline->gotoFrameAndPlay(30, 40, false);
	this->_JumpSpeed = this->_BaseJumpSpeed + _SupportSpeed;
}

void IronCat::_BeginJumpUp2()
{
	//this->_IsDoubleJump = true;
	_SpriteTimeline->gotoFrameAndPlay(38, 40, false);
	this->_JumpSpeed2 = this->_BaseJumpSpeed2;
}

void IronCat::_BeginJumpDown()
{
	_SpriteTimeline->gotoFrameAndPlay(40, 45, false);
}

void IronCat::_BeginJumpFinish()
{
	this->_JumpSpeed = 0;
	this->_JumpSpeed2 = 0;
	_SpriteTimeline->gotoFrameAndPlay(50, 55, false);
	this->_IsDoubleJump = false;
}

void IronCat::onFloorCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
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
		this->setPositionY(point.y + _Sprite->getBoundingBox().size.height* 0.36f);
		break;
	case CollideOperate::CollideDown:
		_CollideState = CollideState::HeadCollide;
		this->_JumpSpeed = this->_JumpSpeed2 = 0;
		this->setPositionY(point.y - _Sprite->getBoundingBox().size.height*0.64f);
		break;
	default:
		break;
	}
}

void IronCat::onWallCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
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

void IronCat::onEnemyCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
	if (!this->_IsValid)
	{
		return;
	}
	if (this->_IsBorning)
	{
		return;
	}
	this->setRotation(180);
	this->_IsValid = false;
}

void IronCat::_BeginAttack()
{
	if (_AttackState == AttackState::NotAttack)
	{
		/*just for fun
		bool haveBianbian = false;
		for (auto wea = BaseLevel::_weapons.begin(); wea != BaseLevel::_weapons.end(); wea++)
		{
		if ((*wea)->_IsValid)
		{
		if ((*wea)->getName() == WEAPON_BIANBIAN_NAME)
		{
		haveBianbian = true;
		}
		}
		}

		if (!haveBianbian){
		*/
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
		_eventDispatcher->dispatchCustomEvent(EVENT_WEAPON_CREATE, (void*)(WeaponEventType::ThrowCannon));

		_AttackCount++;
		this->scheduleOnce([=](float delta){
			_AttackState = AttackState::NotAttack;
		}, _AttackColdTime, "attack");
		_AttackState = AttackState::Attacking;
		/*just for fun
		}*/
	}
}

void IronCat::_Attack(ClickState clickState)
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