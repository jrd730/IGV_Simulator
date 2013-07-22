#include "WayPoint.h"

WayPoint::WayPoint(){

}

WayPoint::WayPoint(int _x, int _y, unsigned char _type) : WorldObject(_x, _y, _type) 
{

}

WayPoint::~WayPoint(){

}

void WayPoint::glow(){ 
    perform_glow_effect_grid(coord_x, coord_y, width, height); 
}