#ifndef __CHALK_ENEMY_H__
#define  __CHALK_ENEMY_H__
#include "Enemy360.h"
class ChalkEnemy : public Enemy360
{
public:
	CREATE_FUNC(ChalkEnemy);
	virtual bool init() override;
};
#endif