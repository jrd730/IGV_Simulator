
#ifndef   GRID_SQUARE
#define   GRID_SQUARE

#include "WorldObject.h"
#include "Globals.h"

/* Grid Squares.. */
class GridSquare {
    public:
        GridSquare(WorldObject* obj_to_set = NULL);
        GridSquare(int _x, int _y, WorldObject* obj_to_set = NULL);   //converts the position from 
        ~GridSquare();

        void setObject(WorldObject* obj_to_set);

        void glow(){ 
            if(object){
                object->glow();
            }
            else { 
                perform_glow_effect_grid(coord_x, coord_y, width, height); 
            }
        }
        bool containsIGV(){ return thisContainsIGV; }

        bool is_object;
        WorldObject* object;    // objects that are contained in this grid square.. 

        
        int grid_x;
        int grid_y;

        float coord_x;
        float coord_y;

        float width;
        float height;

        bool  thisContainsIGV;
};

#endif

