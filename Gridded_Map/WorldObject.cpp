#include "WorldObject.h"

unsigned char WorldObject::getType(){
	return type;
}

WorldObject::WorldObject(int _x, int _y, unsigned char _type){
    x = _x;   y = _y;   type = _type;   

    //graph coords
    coord_x =  grid_X(x) *pix_per_grid_block_x*pixToXCoord + graphXMin;
    coord_y = -1*((grid_Y(y)+1) * pix_per_grid_block_y*pixToYCoord) + graphYMax; 

   	//coord_x = toX_Coord(_x); //precise (without offset..)
	//coord_y = toY_Coord(_y);
    
    // shape
    width = pix_per_grid_block_x*pixToXCoord;
    height = pix_per_grid_block_y*pixToYCoord;
}
