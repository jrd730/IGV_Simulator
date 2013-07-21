#ifndef   IGV_BOT_H
#define   IGV_BOT_H

#include "Globals.h"

class IGV_Bot{
    public:
        IGV_Bot();
        void moveTo(int _x, int _y);
        //pixels coordinates
        int x;  
        int y;

        float searchRadius; // in pixels

        // graph coordinates
        float coord_x;
        float coord_y;


        // ONLY SET WHEN CREATED! (i suppose)
        // shape variables.. describe the shape..
        //--------------------------------------
        // pixels..
        float height;
        float width;

        //coord units
        float width_coord;
        float height_coord;


        // simulator specific
           // graph coordinates
        float draw_coord_x;
        float draw_coord_y;


};

#endif

