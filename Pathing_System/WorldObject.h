#ifndef WORLD_OBJECT
#define WORLD_OBJECT
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <queue>
#include "Globals.h"

/* Any object ever.. */
class WorldObject{
public:
	WorldObject(){ type = 1; }
	WorldObject(int _x, int _y, unsigned char _type = 1);
	~WorldObject() { }

	virtual void glow() = 0;
	unsigned char getType();

    unsigned char type;
    int x;  //pixels
    int y;

    // in graph coordinates...
    float coord_x;
    float coord_y;

     // shape variables.. describe the shape..
    float width;
    float height;

    float width_coord;
    float height_coord;

};

#endif