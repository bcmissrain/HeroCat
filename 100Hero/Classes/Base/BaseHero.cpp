#include "BaseHero.h"

//Stand
ActionState StandStatus::getState()
{
	return ActionState::Stand;
}

void StandStatus::initState(BaseHero* hero)
{
	hero->_BeginStand();
}

void StandStatus::checkState(BaseHero* hero)
{
	if (hero->_ifClickLeft == ClickState::Begin || hero->_ifClickLeft == ClickState::Still)
	{
		hero->changeStateTo(ActionState::Run);
	}

	if (hero->_ifClickRight == ClickState::Begin || hero->_ifClickRight == ClickState::Still)
	{
		hero->changeStateTo(ActionState::Run);
	}

	if (hero->_ifClickAttack == ClickState::Begin || hero->_ifClickAttack == ClickState::Still)
	{
		hero->_Attack(hero->_ifClickAttack);
		hero->_ifClickAttack = ClickState::Still;
	}

	if (hero->_ifClickJump == ClickState::Begin)
	{
		hero->_ifClickJump = ClickState::Still; //force change to still
		hero->changeStateTo(ActionState::JumpUp);
	}
}

void StandStatus::updateState(BaseHero* hero, float deltaTime /* = 0 */)
{
	hero->_Stand(deltaTime);
}

//Run
ActionState RunStatus::getState()
{
	return ActionState::Run;
}

void RunStatus::initState(BaseHero* hero)
{
	hero->_BeginRun();
}

void RunStatus::checkState(BaseHero* hero)
{
	//end run
	if (hero->_ifClickLeft == ClickState::None || hero->_ifClickLeft == ClickState::End)
	{
		if (hero->_ifClickRight == ClickState::None || hero->_ifClickRight == ClickState::End)
		{
			hero->changeStateTo(ActionState::Stop);
		}
	}

	//attack
	if (hero->_ifClickAttack == ClickState::Begin || hero->_ifClickAttack == ClickState::Still)
	{
		hero->_Attack(hero->_ifClickAttack);
		hero->_ifClickAttack = ClickState::Still;
	}

	//drop
	if (hero->_CollideState == CollideState::NoneSupport)
	{
		hero->changeStateTo(ActionState::JumpDown);
	}

	//jumpup
	if (hero->_ifClickJump == ClickState::Begin)
	{
		hero->_ifClickJump = ClickState::Still; //force change to still
		hero->changeStateTo(ActionState::JumpUp);
	}
}

void RunStatus::updateState(BaseHero* hero, float deltaTime)
{
	if (hero->_SpriteTimeline->isDone())
	{
		hero->_BeginRun();
	}
	hero->_Run(deltaTime);
}

//Stop
ActionState StopStatus::getState()
{
	return ActionState::Stop;
}

void StopStatus::initState(BaseHero* hero)
{

}

void StopStatus::checkState(BaseHero* hero)
{
	//end run
	if (hero->_ifClickLeft == ClickState::None || hero->_ifClickLeft == ClickState::End)
	{
		if (hero->_ifClickRight == ClickState::None || hero->_ifClickRight == ClickState::End)
		{
			if (hero->_MoveStateCache == MoveState::None)
			{
				hero->changeStateTo(ActionState::Stand);
			}
		}
	}

	//attack
	if (hero->_ifClickAttack == ClickState::Begin || hero->_ifClickAttack == ClickState::Still)
	{
		hero->_Attack(hero->_ifClickAttack);
		hero->_ifClickAttack = ClickState::Still;
	}

	//drop
	if (hero->_CollideState == CollideState::NoneSupport)
	{
		hero->changeStateTo(ActionState::JumpDown);
	}

	//jumpup
	if (hero->_ifClickJump == ClickState::Begin)
	{
		hero->_ifClickJump = ClickState::Still; //force change to still
		hero->changeStateTo(ActionState::JumpUp);
	}
}

void StopStatus::updateState(BaseHero* hero, float deltaTime /* = 0 */)
{
	hero->_Stop(deltaTime);
}

//JumpUp
ActionState JumpUpStatus::getState()
{
	return ActionState::JumpUp;
}

void JumpUpStatus::initState(BaseHero* hero)
{
	hero->_BeginJumpUp();
}

void JumpUpStatus::checkState(BaseHero* hero)
{
	if (hero->getActionByTag(ACTION_TAG_JUMP_UP) == nullptr)
	{
		hero->changeStateTo(ActionState::JumpDown);
	}

	if (hero->_ifClickJump == ClickState::Begin)
	{
		if (hero->_CanDoubleJump && hero->_IsDoubleJump == false)
		{
			hero->changeStateTo(ActionState::JumpUp2);
		}
	}

	if (hero->_ifClickAttack == ClickState::Begin || hero->_ifClickAttack == ClickState::Still)
	{
		hero->_Attack(hero->_ifClickAttack);
		hero->_ifClickAttack = ClickState::Still;
	}

	if (hero->_CollideState == CollideState::HeadCollide)
	{
		hero->changeStateTo(ActionState::JumpDown);
	}
}

void JumpUpStatus::updateState(BaseHero* hero, float deltaTime)
{
	hero->_JumpUp(deltaTime);
}

//JumpUp2
ActionState JumpUp2Status::getState()
{
	return ActionState::JumpUp2;
}

void JumpUp2Status::initState(BaseHero* hero)
{
	hero->_BeginJumpUp2();
}

void JumpUp2Status::checkState(BaseHero* hero)
{
	if (hero->getActionByTag(ACTION_TAG_JUMP_UP_2) == nullptr)
	{
		hero->changeStateTo(ActionState::JumpDown);
	}

	if (hero->_CollideState == CollideState::HeadCollide)
	{
		hero->changeStateTo(ActionState::JumpDown);
	}

	if (hero->_ifClickAttack == ClickState::Begin || hero->_ifClickAttack == ClickState::Still)
	{
		hero->_Attack(hero->_ifClickAttack);
		hero->_ifClickAttack = ClickState::Still;
	}
}

void JumpUp2Status::updateState(BaseHero* hero, float deltaTime /* = 0 */)
{
	hero->_JumpUp2(deltaTime);
}
//JumpDown
ActionState JumpDownStatus::getState()
{
	return ActionState::JumpDown;
}

void JumpDownStatus::initState(BaseHero* hero)
{
	hero->_BeginJumpDown();
}

void JumpDownStatus::checkState(BaseHero* hero)
{
	if (hero->_ifClickJump == ClickState::Begin)
	{
		if (hero->_CanDoubleJump && hero->_IsDoubleJump == false)
		{
			hero->changeStateTo(ActionState::JumpUp2);
		}
	}

	if (hero->_CollideState == CollideState::HaveSupport)
	{
		hero->changeStateTo(ActionState::JumpFinish);
	}

	if (hero->_ifClickAttack == ClickState::Begin || hero->_ifClickAttack == ClickState::Still)
	{
		hero->_Attack(hero->_ifClickAttack);
		hero->_ifClickAttack = ClickState::Still;
	}
}

void JumpDownStatus::updateState(BaseHero* hero, float deltaTime)
{
	hero->_JumpDown(deltaTime);
}

//JumpFinish
ActionState JumpFinishStatus::getState()
{
	return ActionState::JumpFinish;
}

void JumpFinishStatus::initState(BaseHero* hero)
{
	hero->_BeginJumpFinish();
}

void JumpFinishStatus::checkState(BaseHero* hero)
{
	if (!hero->_SpriteTimeline->isPlaying())
	{
		if (hero->_MoveStateCache == MoveState::None)
		{
			hero->changeStateTo(ActionState::Stand);
		}
		else
		{
			hero->changeStateTo(ActionState::Run);
		}
	}

	if (hero->_ifClickAttack == ClickState::Begin || hero->_ifClickAttack == ClickState::Still)
	{
		hero->_Attack(hero->_ifClickAttack);
		hero->_ifClickAttack = ClickState::Still;
	}

	//jumpup
	if (hero->_ifClickJump == ClickState::Begin)
	{
		hero->_ifClickJump = ClickState::Still; //force change to still
		hero->changeStateTo(ActionState::JumpUp);
	}
}

void JumpFinishStatus::updateState(BaseHero* hero, float deltaTime /* = 0 */)
{
	hero->_JumpFinish(deltaTime);
}

void BaseHero::onMoveLeft(ClickState clickState)
{
	this->_ifClickLeft = clickState;
	if (clickState == ClickState::Begin || clickState == ClickState::Still)
	{
		this->_Direction = Direction::Left;
		this->_MoveState = MoveState::MoveLeft;
		//this->_MoveStateCache = MoveState::MoveLeft;
		this->_Sprite->setScaleX(-_BaseScale);
	}
	else
	{
		if (_ifClickRight == ClickState::None || _ifClickRight == ClickState::End)
		{
			this->_MoveState = MoveState::None;
		}
	}
}

void BaseHero::onMoveRight(ClickState clickState)
{
	this->_ifClickRight = clickState;
	if (clickState == ClickState::Begin || clickState == ClickState::Still)
	{
		this->_Direction = Direction::Right;
		this->_MoveState = MoveState::MoveRight;
		//this->_MoveStateCache = MoveState::MoveRight;
		this->_Sprite->setScaleX(_BaseScale);
	}
	else
	{
		if (_ifClickLeft == ClickState::None || _ifClickLeft == ClickState::End)
		{
			this->_MoveState = MoveState::None;
		}
	}
}

void BaseHero::onJump(ClickState clickState)
{
	this->_ifClickJump = clickState;
}

void BaseHero::onAttack(ClickState clickState)
{
	this->_ifClickAttack = clickState;
}

cocos2d::Size BaseHero::getVisualSize()
{
	return _Sprite->getBoundingBox().size;
}

cocos2d::Point BaseHero::getVisualCenter()
{
	return this->convertToWorldSpace(cocos2d::Vec2(_Sprite->getBoundingBox().getMidX(), _Sprite->getBoundingBox().getMidY()));
}

cocos2d::Rect BaseHero::getBoundingBox()
{
	return cocos2d::Rect(getVisualCenter() - getVisualSize() / 2,getVisualSize());
}

void BaseHero::onWeaponCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
	CCLOG("Collide with Weapon");
}

void BaseHero::onEnemyCollide(cocos2d::Point point, CollideOperate opType, BaseElement* gameElement)
{
	CCLOG("Collide with Enemy");
}

void BaseHero::_onWallCollide()
{
	if (this->_CurrentState->getState() == ActionState::Run || this->_CurrentState->getState() == ActionState::Stop)
	{
		this->_MoveStateCache = this->_MoveState = MoveState::None;
		this->_RunSpeed = 0;
		_ifClickLeft = ClickState::None;
		_ifClickRight = ClickState::None;
	}
}

cocos2d::Point BaseHero::getWeaponPosByIndex(int index)
{
	if (index < _Weapons.size())
	{
		auto tempPos =_Sprite->convertToWorldSpace(_Weapons.at(index)->getPosition());
		//CCLOG("Weapon Pos %f , %f", tempPos.x, tempPos.y);
		return tempPos;
	}
	return cocos2d::Point(0,0);
}

void BaseHero::_BeginStand(){}

void BaseHero::_BeginRun(){}

void BaseHero::_BeginStop(){};

void BaseHero::_BeginJumpUp(){}

void BaseHero::_BeginJumpUp2(){}

void BaseHero::_BeginJumpDown(){}

void BaseHero::_BeginJumpFinish(){}

void BaseHero::_BeginAttack(){}

void BaseHero::_Stand(float deltaTime){ _Run(deltaTime); }

void BaseHero::_Run(float deltaTime)
{
	//set move cache
	if (_MoveStateCache == MoveState::None && _MoveState != MoveState::None)
	{
		_MoveStateCache = _MoveState;
	}
	//reset speed
	if (_MoveStateCache == _MoveState)
	{
		if (_MoveState != MoveState::None)
		{
			_RunSpeed += _BaseAcceleration;
		}
	}
	else//diff or none
	{
		if (_MoveState == MoveState::None)
		{
			_RunSpeed = _RunSpeed - _BaseAcceleration;
		}
		else
		{
			_RunSpeed = _RunSpeed - 2 * _BaseAcceleration;
		}
	}

	if (_RunSpeed > _BaseRunSpeed)
	{
		_RunSpeed = _BaseRunSpeed;
	}
	else if (_RunSpeed <= 0)
	{
		_RunSpeed = 0;
		this->_MoveStateCache = this->_MoveState;
	}

	//move
	if (_MoveState == MoveState::MoveLeft)
	{
		if (_MoveState == _MoveStateCache)
		{
			this->setPositionX(this->getPositionX() - _RunSpeed*deltaTime);
		}
		else
		{
			this->setPositionX(this->getPositionX() + _RunSpeed*deltaTime);
		}
	}
	else if (_MoveState == MoveState::MoveRight)
	{
		if (_MoveState == _MoveStateCache)
		{
			this->setPositionX(this->getPositionX() + _RunSpeed*deltaTime);
		}
		else
		{
			this->setPositionX(this->getPositionX() - _RunSpeed*deltaTime);
		}
	}
	else if (_MoveState == MoveState::None)
	{
		if (_MoveStateCache == MoveState::MoveLeft)
		{
			this->setPositionX(this->getPositionX() - _RunSpeed*deltaTime);
		}
		else if (_MoveStateCache == MoveState::MoveRight)
		{
			this->setPositionX(this->getPositionX() + _RunSpeed*deltaTime);
		}
	}

	//CCLOG("Run state %d , %d ,speed %f", _MoveState, _MoveStateCache, _RunSpeed);
}

void BaseHero::_Stop(float deltaTime){	_Run(deltaTime); }

void BaseHero::_JumpUp(float deltaTime){ _Run(deltaTime); }

void BaseHero::_JumpUp2(float deltaTime){ _Run(deltaTime);  }

void BaseHero::_JumpDown(float deltaTime){ _Run(deltaTime); }

void BaseHero::_JumpFinish(float deltaTime){ _Run(deltaTime); }

void BaseHero::_Attack(ClickState clickState){}

void BaseHero::_Hurt(){}

void BaseHero::changeStateTo(ActionState state)
{
	//CCLOG("Change to %d", state);
	switch (state)
	{
	case ActionState::Stand:
		CC_SAFE_DELETE(_CurrentState);
		_CurrentState = new StandStatus();
		_CurrentState->initState(this);
		break;
	case ActionState::Run:
		CC_SAFE_DELETE(_CurrentState);
		_CurrentState = new RunStatus();
		_CurrentState->initState(this);
		break;
	case ActionState::Stop:
		CC_SAFE_DELETE(_CurrentState);
		_CurrentState = new StopStatus();
		_CurrentState->initState(this);
		break;
	case ActionState::JumpUp:
		CC_SAFE_DELETE(_CurrentState);
		_CurrentState = new JumpUpStatus();
		_CurrentState->initState(this);
		break;
	case ActionState::JumpUp2:
		CC_SAFE_DELETE(_CurrentState);
		_CurrentState = new JumpUp2Status();
		_CurrentState->initState(this);
		break;
	case ActionState::JumpDown:
		CC_SAFE_DELETE(_CurrentState);
		_CurrentState = new JumpDownStatus();
		_CurrentState->initState(this);
		break;
	case ActionState::JumpFinish:
		CC_SAFE_DELETE(_CurrentState);
		_CurrentState = new JumpFinishStatus();
		_CurrentState->initState(this);
		break;
	default:
		break;
	}
}

void BaseHero::afterUpdate()
{
	this->_CollideState = CollideState::NoneSupport;

}