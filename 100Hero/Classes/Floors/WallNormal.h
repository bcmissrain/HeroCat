#ifndef __WALL_NORMAL__
#define __WALL_NORMAL__
#include "../Base/BaseWall.h"

class WallNormal : public BaseWall
{
public:
	virtual bool init() override;
	virtual bool collideWithGameElement(BaseElement* gameElement) override;
	CREATE_FUNC(WallNormal);
};

#endif