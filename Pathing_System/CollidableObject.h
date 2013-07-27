#ifndef     COLLIDABLE_OBJECT
#define     COLLIDABLE_OBJECT

#include "WorldObject.h"

/* --- */
class CollidableObject : public WorldObject
{
    public: 
        CollidableObject();
        CollidableObject(int _x, int _y, unsigned char _type = 1);
        ~CollidableObject(){}

        void glow();

};



#endif
