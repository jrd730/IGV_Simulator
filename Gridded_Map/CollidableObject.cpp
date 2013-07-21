
#include "CollidableObject.h"



 CollidableObject::CollidableObject(){

 }

// takes x and y pixel coordinates..
CollidableObject::CollidableObject(int _x, int _y, unsigned char _type){
    x = _x;   y = _y;   type = _type;   

    coord_x = grid_X(x) * pix_per_grid_block_x*pixToXCoord + graphXMin; 
    coord_y = -1*((grid_Y(y)+1) * pix_per_grid_block_y*pixToYCoord) + graphYMax; 
    width = pix_per_grid_block_x*pixToXCoord;
    height = pix_per_grid_block_y*pixToYCoord;
}

void CollidableObject::glow(){ 
    perform_glow_effect_grid(coord_x, coord_y, width, height); 
}
