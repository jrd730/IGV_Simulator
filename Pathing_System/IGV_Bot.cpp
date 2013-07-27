
#include "IGV_Bot.h"


/* default */
IGV_Bot::IGV_Bot() : WorldObject(50, 50) 
{ 
    init(); 
}

/* explicit */
IGV_Bot::IGV_Bot(int _x, int _y, unsigned char _type) : WorldObject(_x, _y, _type)
{ 

	init();
}


bool IGV_Bot::runSearchWithinRadius(GridSquare* **GridSpace){
	    /* NEAR OR COLLISION */
    int min_grid_x = grid_X((this->x - this->searchRadius));
    int max_grid_x = grid_X((this->x + this->searchRadius));
    int min_grid_y = grid_Y((this->y - this->searchRadius));
    int max_grid_y = grid_Y((this->y + this->searchRadius));


    // check window bounds..
    if(min_grid_x < 0)
        min_grid_x = 0;
    if(min_grid_y < 0)
        min_grid_y = 0;
    if(max_grid_x >= grid_blocks_x)
        max_grid_x = grid_blocks_x-1;
    if(max_grid_y >= grid_blocks_y)
        max_grid_y = grid_blocks_y-1;


    std::cout << "igv: " << grid_X(this->x) << "," << grid_Y(this->y) << std::endl;
    std::cout << 
    "min_x: "  <<  min_grid_x << ".. " <<
    "max_x: "  <<  max_grid_x << ".." << std::endl << 
    "min_y: "  <<  min_grid_y << ".. " <<
    "max_y: "  <<  max_grid_y << ".. " << std::endl << std::endl;

    

    // for all search spaces near the IGV .. if there is an object.. -> make it glow :)
    for(int grid_iter_y = min_grid_y; grid_iter_y <= max_grid_y; ++grid_iter_y){
        for(int grid_iter_x = min_grid_x; grid_iter_x <= max_grid_x; ++grid_iter_x){ 
                // std::cout << "Searching..: (" << grid_iter_x << "," << grid_iter_y << ").." << std::endl;
                if (GridSpace[grid_iter_x][grid_iter_y]->is_object){  
                    // do you have an object??
                    // if so then  do some stuff with the object..
                     std::cout << "Object found at: (" << grid_iter_x << "," << grid_iter_y << ") type: "
                        << GridSpace[grid_iter_x][grid_iter_y]->object->type << std::endl;
                    GridSpace[grid_iter_x][grid_iter_y]->glow();
                    // discover object.. discover type.. now insert into the igv map..

                    // ASSERT: the x and y are within the window.. at this point obejcts from the world are
                    //  guarenteed to fit within the igv's world..(although it may seem contrary)
                    if(!this->objectAt(grid_iter_x, grid_iter_y)){
                        WorldObject* wobj = GridSpace[grid_iter_x][grid_iter_y]->object;
                        this->addObjectToMap(new CollidableObject(wobj->x, wobj->y));
                    }
                }
        }
    } 
    return true;
}

bool IGV_Bot::moveToNextWaypoint(){
	 /* UPDATE CURRENT POSITION by  moving a specified increment distance */
    // given waypoints.. move to waypoints..

    WayPoint* wp = this->waypoints.next();
    float MOVE_CONSTANT = 5.0;								// the whole amount possible to move on screen in one frame

    float dx;
    float dy;
    float distance_to_travel;
    if(wp != NULL){
        dx = (wp->x - this->x);
        dy = (wp->y - this->y);
        distance_to_travel = sqrt(dx * dx + dy * dy);
        if (distance_to_travel < GPS_WAYPOINT_RADIUS) {		// if so: then Waypoint Reached!
            this->waypoints.pop();	
        } else {  											// else:
            dx = MOVE_CONSTANT*(dx/distance_to_travel);     // the actual distance we need to travel this round
            dy = MOVE_CONSTANT*(dy/distance_to_travel);

            fractionalDistance_x += dx - floor(dx);         // how much distance is fractional -> accumulated for later
            fractionalDistance_y += dy - floor(dy);

            this->moveTo( fractionalDistance_x + floor(dx) + this->x,   // move to the whole numbered pixel coordinate
                          fractionalDistance_y + floor(dy) + this->y);

            fractionalDistance_x -= floor(fractionalDistance_x);		// reduce saved fractional count by whole number
            fractionalDistance_y -= floor(fractionalDistance_y);
        }   
    }
    return true;
}

bool IGV_Bot::addObjectToMap(WorldObject* worldobj){
	bool object_insert_successful  = true;

	(Map[grid_X(worldobj->x)][grid_Y(worldobj->y)])
		->setObject(worldobj);

	collidable_vector.push_back(worldobj);

	return object_insert_successful;
}

 bool IGV_Bot::objectAt(int grid_x, int grid_y){
 	if(Map[grid_x][grid_y]->is_object)
 		return true;
 	return false;
 }

void IGV_Bot::displayMap(){
	//draw_the_IGV_Map((void***)Map)''
    for (unsigned int i = 0; i < collidable_vector.size(); ++i){
        collidable_vector[i]->glow();
    }

}

void IGV_Bot::moveTo(int _x, int _y){
	if (_x > window.width)
		_x = window.width;
	if (_x < 0)
		_x = 0;
	if (_y > window.height)
		_y = window.height;
	if (_y < 0)
		_y = 0;

	x = _x;
	y = _y;

	coord_x = toX_Coord(_x);
	coord_y = toY_Coord(_y);

	draw_coord_x = coord_x - (width_coord/2);
	draw_coord_y = coord_y - (height_coord/2);
}




void IGV_Bot::glow(){ 
    perform_glow_effect_grid(coord_x, coord_y, width, height); 
}




void IGV_Bot::init(){ 

	/* --- Shape Parameters --- */

	// shape in pixels
	width = 18;
	height = 18;

	// shpe in graph coord units
	width_coord = pixToXCoord * width;
	height_coord = pixToYCoord * height;

	// Simulator specific IGV Drawing parameters..
	draw_coord_x = coord_x - (width_coord/2);  //current coord but offset left and down..  
	draw_coord_y = coord_y - (height_coord/2); // by the Width & height

	//Initialize the IGV's Map
	Map = NULL;
	initMap();

	/* Searching Parameters */
	searchRadius = 72; //px

	/* --- Waypoint Parameters --- */
	GPS_WAYPOINT_RADIUS = 5; 					// Literally the radius of a waypoint..(must be within Radius to reach)

	/* --- Motion Parameters --- */
	fractionalDistance_x = 0;
 	fractionalDistance_y = 0;
}

bool IGV_Bot::initMap(){
	if(Map)		// if the Map DOES exist.. then it doesnt need to be reinit... just clean it..
		return false;

	Map = new GridSquare**[grid_blocks_x];			// create a new map
	for (int i = 0; i < grid_blocks_x; ++i){		
    	Map[i] = new GridSquare*[grid_blocks_y];
        for (int j = 0; j < grid_blocks_y; ++j){
            Map[i][j] = new GridSquare(i, j, NULL);	// populate with real elements
        }
    }
    return true;
}

bool IGV_Bot::cleanMap(){
	if(!Map)		// if it DOESNT exist.. then return false.. need to init first..
		return false;

	for (int i = 0; i < grid_blocks_x; ++i)
        for (int j = 0; j < grid_blocks_y; ++j){
            delete Map[i][j];
            Map[i][j] = new GridSquare(i, j, NULL);
         }
    return true;
}
