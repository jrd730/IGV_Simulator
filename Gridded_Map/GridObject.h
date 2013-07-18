#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <stdlib.h>

#include <iostream>
#include <vector>

class CollidableObject;

class GridObject
{
public:
	GridObject();
	~GridObject();
};



// or maybe a grid tree?
class GridSquare : public GridObject {
    public:
        GridSquare(CollidableObject* obj_to_set = NULL);
        ~GridSquare();
        void glow(){ }
        bool is_object;
        CollidableObject* object;
        int x;   //pixels
        int y;
};
