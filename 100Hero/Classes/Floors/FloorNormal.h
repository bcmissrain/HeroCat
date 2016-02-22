#ifndef __FLOOR_NORMAL_H__
#define __FLOOR_NORMAL_H__

#include "../Base/BaseFloor.h"

class FloorNormal : public BaseFloor
{
public:
	virtual bool init() override;
	CREATE_FUNC(FloorNormal);
};
#endif