
#ifndef   GRID_H
#define   GRID_H

#include "GridSquare.h"
#include "CollidableObject.h"

/* Grid .. contains "grid squares".. only one instance allowed */
/* After the Grid has been init.. and a gridObject is returned to 
the user.. the user of the grid can then initGrid, ClearGrid, and initGrid again
and start using the grid by addingCollidables to the grid at x,y pixel coord
NOTE:  to access a gridsquare, call the at() or use []*/
class Grid {
    public:
        static Grid* init(int width = 4, int height = 4); // initializes only one grid
        bool initGrid();
        bool clearGrid();    // wipe out all traces of objects , start a new grid

        void addCollidableToGrid(int x, int y); // at an object at x and y pixels
        void fillGrid(); // completely fill it up with random objects..

        GridSquare* at(int x, int y); // at pixels
        GridSquare* at_grid_coord(int x, int y); // at grid coord
        //const GridSquare* *operator[](const int); //.. alias for at function..

        ~Grid();

        //objects that are collidable..
        std::vector <WorldObject*> collidable_vector;
    private:
        // this is the object that the user
        // has access to
        static Grid*  gridObject;   //returned to the user to be used
        

        int width_grid_x;
        int height_grid_y;

        Grid();
        Grid(int width, int height);


        /* this is the actual map.. */
        static GridSquare*  **m_theGrid;  // must be initialized

        Grid(const Grid&); //overwrite default copy constructor
        const Grid& operator=(const Grid&); //.. and assignment
};

#endif

