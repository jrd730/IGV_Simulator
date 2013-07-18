
#include "GridObject.h"

GridObject::GridObject(){

}
GridObject::~GridObject(){

}



GridSquare::GridSquare(CollidableObject* obj_to_set){
    is_object = false;
    object = obj_to_set;
}
GridSquare::~GridSquare(){

}