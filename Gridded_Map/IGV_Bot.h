#ifndef   IGV_BOT_H
#define   IGV_BOT_H

class IGV_Bot{
    public:
        IGV_Bot();
        int x;  //pixels..
        int y;

        float searchRadius; // px

        // graph coordinates
        float coord_x;
        float coord_y;

        // shape variables.. describe the shape..
        float width;
        float height;

        float height_coord;
        float width_coord;


};

#endif

