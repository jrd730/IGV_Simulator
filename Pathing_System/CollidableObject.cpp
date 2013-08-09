
#include "CollidableObject.h"

 CollidableObject::CollidableObject(){

 }

// takes x and y pixel coordinates..
CollidableObject::CollidableObject(int _x, int _y, unsigned char _type) 
: WorldObject(_x, _y, _type) 
{

}

void CollidableObject::glow(){ 
    perform_glow_effect_grid(coord_x, coord_y, width, height); 
}
