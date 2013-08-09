#ifndef   IGV_BOT_H
#define   IGV_BOT_H

#include <iostream>
#include "CollidableObject.h"
#include "WorldObject.h"
#include "GridSquare.h"
#include "WayPoints.h"
#include "Vertex.h"
#include "Grid.h"


class IGV_Bot : public WorldObject
{
    public:
        IGV_Bot();
        IGV_Bot(int _x, int _y, unsigned char _type = -1);

        /* run search on this 2d space.. */
        bool    checkForObstacles(Grid* grid);
        bool    moveToNextWaypoint();
        bool    decideNextPathpoint();

        bool addObjectToMap(WorldObject* worldobj);
        bool objectAt(int grid_x, int grid_y);
        void displayMap();
        void moveTo(int _x, int _y);
        void glow();


/*  In the base class:
        // location in pixels 
        int x; 
        int y; 
    
        // location in graph coordinates
        float coord_x;
        float coord_y;


        // shape in pixels..
        float height;
        float width;
*/

        float searchRadius; // in pixels

        // shpe in graph coord units
        float width_coord;
        float height_coord;

        // simulator specific, draw locations..
           // graph coordinates
        float draw_coord_x;
        float draw_coord_y;

        //std::vector <WayPoint*> WayPoints;     // contains an ordered list of waypoints
        WayPoints waypoints;  // the waypoints object.. handles waypoint stuff..

        GridSquare* **Map; //.. 2d map of points to grid squares...
        std::vector <WorldObject*> collidable_vector;

    private:
        void init();
        bool initMap();
        bool cleanMap();

        int   GPS_WAYPOINT_RADIUS;
        float fractionalDistance_x ;    // the accumulated & saved distance that hasn't been travelled 
        float fractionalDistance_y ;    //  but should be travelled eventually.. so collect it..

        double wheelBase, 
            tireDiameter,
            angularVelocity,
            maxAngularVelocity,
            leftVelocity, 
            rightVelocity,
            rotation;
};

#endif

