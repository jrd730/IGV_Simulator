#ifndef WAY_POINT_H
#define WAY_POINT_H

#include "WorldObject.h"




/* -------------------------- */
/* DEFINES THE WAYPOINT point itself */

class WayPoint : public WorldObject
{
public:
	WayPoint();
	WayPoint(int _x, int _y, unsigned char _type = 1);	//x,y are in pixels
	~WayPoint();

	void glow();

	float width_coord;
	float height_coord;
};




/* -------------------------- */
/* DEFINES THE WAYPOINTS STRUCTURE */

class WayPoints
{
public:	
	WayPoints();
	~WayPoints();

	void newWaypoint(int _x, int _y);
	WayPoint* next();
	void pop();
	void clear();
	int count();
	int size();
	std::queue <WayPoint*> getWaypoint_Q() { return wp_queue; }

	std::queue <WayPoint*> wp_queue; // the waypoint queue..

};

#endif

