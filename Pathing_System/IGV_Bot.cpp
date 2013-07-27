
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

	searchRadius = 72; //px

	// shape in pixels
	width = 18;
	height = 18;

	// shpe in graph coord units
	width_coord = pixToXCoord * width;
	height_coord = pixToYCoord * height;

	// where to draw.. drawing coordinates
	draw_coord_x = coord_x - (width_coord/2);  //current coord but offset left and down..  
	draw_coord_y = coord_y - (height_coord/2); // by the Width & height

	//initialize the map
	Map = NULL;
	initMap();
}

bool IGV_Bot::initMap(){
	if(Map)		// if the Map DOES exist.. then it doesnt need to be reinit... just clean it..
		return false;

	Map = new GridSquare**[grid_blocks_x];
	for (int i = 0; i < grid_blocks_x; ++i){
    	Map[i] = new GridSquare*[grid_blocks_y];
        for (int j = 0; j < grid_blocks_y; ++j){
            Map[i][j] = new GridSquare(i, j, NULL);
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
