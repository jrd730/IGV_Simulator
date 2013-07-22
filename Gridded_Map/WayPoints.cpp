#include "WayPoints.h"


/* -------------------------- */
/* DEFINES THE WAYPOINTS STRUCTURE */
WayPoints::WayPoints(){

}
WayPoints::~WayPoints(){
	clear();
}

 
 /* 
	Usage:

	IGV->waypoints.new .. next . pop.. clear .. count

 */

void WayPoints::newWaypoint(int _x, int _y){
	wp_queue.push(new WayPoint(_x, _y));
}

WayPoint* WayPoints::next(){ 
	if(wp_queue.size())
		return wp_queue.front(); 
	return NULL;
}

void WayPoints::pop(){ wp_queue.pop(); }

void WayPoints::clear(){
	std::queue<WayPoint*> empty;
 	std::swap(wp_queue, empty);
}

int WayPoints::count(){ return wp_queue.size(); }

int WayPoints::size(){ return wp_queue.size(); }


/* -------------------------- */
/* DEFINES THE WAYPOINT point itself */

WayPoint::WayPoint(){

}

WayPoint::WayPoint(int _x, int _y, unsigned char _type)
{
	x = _x;
	y = _y;

	coord_x = toX_Coord(x);
	coord_y = toY_Coord(y);

	width  = 10;
	height = width;

	width_coord  = pixToXCoord * width;
	height_coord = pixToYCoord * height;
}

WayPoint::~WayPoint(){

}

void WayPoint::glow(){ 
    perform_glow_effect_grid(coord_x, coord_y, width, height); 
}