#include "Grid.h"

Grid* Grid::gridObject = NULL;				// ptr to the grid object
GridSquare* **Grid::m_theGrid = NULL;		// 2d array of pts to gridsquares

Grid* Grid::init(int width, int height){
	if(!gridObject){
		//create grid
		gridObject = new Grid(width, height); // and it has been init during the construction
	}
	return gridObject;
}

Grid::Grid(){

}

Grid::~Grid(){
	this->clearGrid();	// delete the grid;
	// then delete this;
}

        
Grid::Grid(int width, int height){
	width_grid_x  = width;
	height_grid_y = height;
	this->initGrid();
}

GridSquare* Grid::at(int x, int y){ // expects pixels.. needs to convert to grid coord..
	return this->at_grid_coord(grid_X(x), grid_Y(y)); //return gridsquare at grid coord X and Y..
} // at pixels

// could return null
GridSquare* Grid::at_grid_coord(int gridx, int gridy){	// epxects grid coords
	return m_theGrid[gridx][gridy];	// return the gridsquare at gridx gridy..
} // at grid coord


void Grid::addCollidableToGrid(int x, int y){ // pixels
    x &= INT_MAX;   // no negatives....(the x and y values are mirrored)
    y &= INT_MAX;
    x = x % window.width;  
    y = y % window.height; 

    if(m_theGrid[grid_X(x)][grid_Y(y)]->object){
        // then its already there...
    } else {
        m_theGrid[grid_X(x)][grid_Y(y)]->object = new CollidableObject((x), (y));
        m_theGrid[grid_X(x)][grid_Y(y)]->is_object = true;
        //cout << x << " " << grid_X(x) << " " <<  y << " " << grid_Y(y) << endl;
        this->collidable_vector.push_back(m_theGrid[grid_X(x)][grid_Y(y)]->object);
    }
}

/* fill up the grid..*/
void Grid::fillGrid(){
    for (int i = 0; i < grid_blocks_x; ++i)
    {
        for (int j = 0; j < grid_blocks_y; ++j)
        {
        		if(!m_theGrid[i][j]){
        			m_theGrid[i][j] = new GridSquare(i, j, NULL);
        		}
                if(m_theGrid[i][j]->object){
                    // then its already there...
                } else {
                    m_theGrid[i][j]->object 
                        = new CollidableObject( i*pix_per_grid_block_x + pix_per_grid_block_x/2,
                                                j*pix_per_grid_block_y + pix_per_grid_block_y/2);
                    m_theGrid[i][j]->is_object = true;
                    //cout << x << " " << grid_X(x) << " " <<  y << " " << grid_Y(y) << endl;
                    this->collidable_vector.push_back(m_theGrid[i][j]->object);
                }
        }
    }
}


// empty the grid.. must be re-init..
// sets the m_thegrid to NULL..
bool Grid::clearGrid(){
    for (int i = 0; i < grid_blocks_x; ++i)
    {
        for (int j = 0; j < grid_blocks_y; ++j)
        {
            delete m_theGrid[i][j];	// pointer to grid square
            m_theGrid[i][j] = NULL;
        }
        delete m_theGrid[i]; // pointer to pointers to grid squares..
        m_theGrid[i] = NULL;
    }
    delete m_theGrid; // one pointer to: pointers to: pointers to grid squares
    m_theGrid = NULL;

    return true; 
}

// called in the constructor.. and when reinit needs to occur
// initalizes GridSquares to the grid
bool Grid::initGrid(){
	if(m_theGrid){
		clearGrid();
	}
	//if(!m_theGrid){
    	m_theGrid = new GridSquare**[width_grid_x];
	//} 
    for (int i = 0; i < width_grid_x; ++i){
        //if(!m_theGrid[i]){
            m_theGrid[i] = new GridSquare*[height_grid_y];
        //}
        for (int j = 0; j < height_grid_y; ++j)
        {
            m_theGrid[i][j] = new GridSquare(i, j, NULL);
        }
    }

    return true;
}

