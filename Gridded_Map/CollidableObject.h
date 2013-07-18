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

        unsigned char type;
        int x;  //pixels
        int y;

        // in graph coordinates...
        float coord_x;
        float coord_y;
        float width;
        float height;
};



#endif
