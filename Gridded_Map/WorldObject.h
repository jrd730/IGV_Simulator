#ifndef WORLD_OBJECT
#define WORLD_OBJECT
#include <stdlib.h>

/* Any object ever.. */
class WorldObject{
public:
	WorldObject(){ }
	~WorldObject() { }

	virtual void glow() = 0;
	unsigned char getType();

private:
	unsigned char type;

};

#endif