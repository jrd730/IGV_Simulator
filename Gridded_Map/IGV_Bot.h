#ifndef   IGV_BOT_H
#define   IGV_BOT_H

#include "WorldObject.h"
#include "GridSquare.h"
#include "WayPoints.h"



class IGV_Bot : public WorldObject
{
    public:
        IGV_Bot();
        IGV_Bot(int _x, int _y, unsigned char _type = -1);

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

        double wheelBase, 
            tireDiameter,
            angularVelocity,
            maxAngularVelocity,
            leftVelocity, 
            rightVelocity,
            rotation;

};

#endif

