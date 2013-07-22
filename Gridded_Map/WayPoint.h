#ifndef WAY_POINT_H
#define WAY_POINT_H

#include "WorldObject.h"

class WayPoint : public WorldObject
{
public:
	WayPoint();
	WayPoint(int _x, int _y, unsigned char _type = 1);
	~WayPoint();

	void glow();
};

#endif

