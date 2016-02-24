#ifndef __BASE_WALL__
#define __BASW_WALL__
#include "BaseDefine.h"
#include "BaseFloor.h"

class BaseWall : public BaseFloor
{
public:
	BaseWall(){}
	~BaseWall(){}

	virtual bool collideWithGameElement(BaseElement* gameElement) override;
protected:
	virtual float _getBorderScale() override;
};
#endif