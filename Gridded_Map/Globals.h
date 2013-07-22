#ifndef GLOBALS_H
#define GLOBALS_H

#include <climits>
/* --------------- WINDOW & GRAPH PROPERTIES --------------- */


struct Window{
    int width;
    int height;
};

extern struct Window window;

// window
extern int height ;
extern int width ;

// X graph min/max + ratio
extern float graphXMin;
extern float graphXMax ;
extern float graphXRange ;
extern float pixToXCoord ;
// Y graph min/max + ratio
extern float graphYMin;
extern float graphYMax ;
extern float graphYRange ;
extern float pixToYCoord ;





/* --------------- GRID PROPERTIES --------------- */



// GRID width & height of entire window..
extern const  int grid_blocks_x  ;
extern const  int grid_blocks_y  ;


extern const  float pix_per_grid_block_x ;       
extern const  float pix_per_grid_block_y ;


extern float incr_next_col ;   // increment val
extern float incr_next_row ;

extern void perform_glow_effect_grid(float coord_x, float coord_y, float bwidth, float bheight);


#endif

/* Finds the indecies in the grid at pixel x and pixel y..*/
#define grid_X(x) (int)((x) / pix_per_grid_block_x) 
#define grid_Y(y) (int)((y) / pix_per_grid_block_y)

/* find the graph coord at pixel x and pixel y */
#define toX_Coord(x) (((x) * pixToXCoord) + graphXMin)
#define toY_Coord(y) (((-y) * pixToYCoord) + graphYMax)

/* find x and y from graph coord*/
#define pixFromCoordX(x)  (((x) - graphXMin) / pixToXCoord)
#define pixFromCoordY(y) (-1 * ((y) - graphYMax) / pixToYCoord)

/* convert/find grid coordinate to graph coordinate */
#define toX_Coord_From_GridCoord(x) ((pix_per_grid_block_x * (x)) + graphXMin)
#define toY_Coord_From_GridCoord(y) (-1 * (pix_per_grid_block_y * (y)) + graphYMax)


