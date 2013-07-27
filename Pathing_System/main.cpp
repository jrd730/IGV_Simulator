/******************************************************************************************
    
IGV Simulator:

    TODO:
    Simulator keeps track of objects and IGV in the REAL MAP..
    IGV_Bot moves around on the REAL MAP.. 
        -> Expects to move to point A: -> stores Point A as it's Location in IGV_Bot->EXPLORED_MAP
        -> However, the IGV_Bots actual location might not be point A.
            --> the Simulator knows this.. and the REAL MAP keeps track of this.
            (Simulator needs to randomly change the bot's position OR
                the IGV needs to place itself incorrectly on the REAL MAP (delibrately))
    

*********************************************************************************************/


                // Simulator should be storing IGV's:
                //      grid location
                //      pixel location
                //      graph coord location
                // IGV :
                //      grid location
                //      pixel location
                //      graph coord location

#include "GA_CONSTANTS.h"


#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
//#include <windows.h>
#include <iostream>
#include <vector>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

using namespace std;
typedef unsigned char   uchar;
typedef long double     ld;

#include "Vertex.h"
#include "IGV_Bot.h"
#include "Globals.h"
#include "GridSquare.h"
#include "CollidableObject.h"



// Drawing settings..
uchar      DRAW_GRID_LINES        = 1;    // the representation of the grid
uchar      DRAW_SIM_REAL_MAP      = 1;    // the objects populated on the WORLD/(real) map..
uchar      DRAW_IGV_EXPLORED_MAP  = 1;    // the explored territory
uchar      DRAW_IGV_PATH          = 0;    // path to travel
uchar      DRAW_IGV_PATH_HISTORY  = 0;

uchar      STATE_ADD_WAYPOINT     = 1;
uchar      STATE_ADD_OBSTACLE     = 0;


/*      GLOBALS 
*/
/* --------------- WINDOW & GRID PROPERTIES --------------- */
// window
int height = 600;
int width = 800;
struct Window window = { width, height };

// X graph min/max + ratio
float graphXMin = -12;
float graphXMax = 12;
float graphXRange = graphXMax - graphXMin;
float pixToXCoord = graphXRange/window.width;

// Y graph min/max + ratio
float graphYMin = -9;
float graphYMax = 9;
float graphYRange = graphYMax - graphYMin;
float pixToYCoord = graphYRange/window.height;



/* --------------- GRID PROPERTIES --------------- */
// GRID width & height of entire window..
const  int grid_blocks_x   = 50; // of the width of the screen
const  int grid_blocks_y   = 50;


const  float pix_per_grid_block_x = (window.width * 1.0) / (grid_blocks_x);        
const  float pix_per_grid_block_y = (window.height * 1.0) / (grid_blocks_y);


float incr_next_col = graphXMax / (grid_blocks_x/2);    // increment val
float incr_next_row = graphYMax / (grid_blocks_y/2);

// ================== END GLOBALS ================== //


// drawing and mvoement stuff..
float theta[] = {0.0, 45.0, 90.0, 135.0, 180.0, 225.0, 270.0, 315.0, 360.0};




/* = = = = = = = = = = = = =
    Function Prototypes
*/
long double randomFloat ();
bool initialize ();
void update ();
void addCollidableToGrid(int x, int y);
void fillGrid();
void clearTheGrid();


//bool operator < (PSeries first, PSeries second){return first.difference < second.difference;}


/*  Important Considerations: (DEALING WITH COORDS)
        Pixel coordinates start at top left of screen..
        Graph coordinates start at the center and are proportional 
            to 1 pixel  by  graphXRange/width and graphYRange/height.

        THE GRID starts at the top left (sits TheGrid[0][0])

        Problem:    Map pixel clicks to TheGrid Index..
*/
// ----------------------------------   - - - - MAP OBJECTS
//Target Points
vector <vertex> targetPoint;

//objects that are collidable..
vector <WorldObject*> collidable_vector;


WorldObject* MouseSelectedObject;           //with the mouse selects the object in the world 

/* THE GRID */
GridSquare*  **TheGrid;  // must be initialized


// --------------------------------//
// ------   IGV  SETTINGS   ------ //
IGV_Bot* IGV; //= new IGV_Bot();   //see IGV_Bot.h

// ------ SIMULATOR  SETTINGS ------ //
bool    going (false);
int     generation  = 0;
int     showBest    = 1;
uint    cur_mouseclick_buttonpressed = -1;  // state variable
// ------    END SETTINGS   ------ //



void  initializeViewMatrix ()
{
    pixToXCoord = graphXRange/window.width;
    pixToYCoord = graphYRange/window.height;
}

long double randomFloat (){
    long double x=((long double)rand()/(long double)RAND_MAX);
    return x;
}


/* Calling during idling... Animates the stuff on the screen 
    Main logic...
*/
void update ()
{

    // IGV->checkForObstacles() .. 
    // IGV->storeObstaclesFound()... if not already stored
    // Given obstacles and the Path structure, determine if
    //  path should be updated.
    //  if new obstacle added:
    //      IGV->Path.updatePath();     // redetermine Path, given current location and current Path Space State..
                                            // Path Space state... the state of the space of possible paths..
                                                // this is grown as space and obstcacles are found
                                                // in a dynamic environment they es would update remotely or remain
                                                    // as ancient data..

    // if this current space leads to a worse outome ( by some worseness weight measure..) 
    // than traveling back to the previous good path..
    //   then turn around and go back to the previous path (back track)
    // IGV->moveTo() // .. next location

    glColor3f (1, 0.2, 0.4);                    // set "glowing" color for obstacle found..
   
    IGV->runSearchWithinRadius(TheGrid);        // searching the 2d space for collidable objects..
    IGV->moveToNextWaypoint();
    
   


}



static void key(unsigned char key, int x, int y)
{
    //int modifier_key_combo = glutGetModifiers();
    //  << modifier_key_combo << ":"<< key << endl;

    switch (key){
        case 't':
        case 'T':
            update();
         break;

        case 'g':
        case 'G':
            going = !going;
         break;

        case 'c':
        case 'C':{
            // randomly generate obstacles
            for (int i=0; i < 50; ++i){
                if(STATE_ADD_WAYPOINT & 1)
                    IGV->waypoints.newWaypoint(rand()%window.width, rand()%window.height);
                else 
                    addCollidableToGrid( rand()%window.width, rand()%window.height);

            }
        }

        break;
        
        case 'r':
        case 'R':
            initialize();
        break;
        case 'f':
            fillGrid();
        break;

        case '~': {
            STATE_ADD_WAYPOINT ^= 1; 
            STATE_ADD_OBSTACLE = STATE_ADD_WAYPOINT ^ 1;
            if(STATE_ADD_WAYPOINT & 1)
                cout << "STATE: Add Waypoints..." << endl;
            else
                cout << "STATE: Add Obstacles..." << endl;
        }
        break;
        case '!':
            DRAW_GRID_LINES ^= 1;
        break;
        case '@':
            DRAW_SIM_REAL_MAP ^= 1;
            DRAW_IGV_EXPLORED_MAP = DRAW_SIM_REAL_MAP ^ 1;
        break;

        case '+':
        case '=':
            showBest *= 2;
        if (showBest >= MAX_POPULATION)
            showBest = MAX_POPULATION-1;
        break;

        case '-':
            showBest /= 2;
            if (showBest < 1)
                showBest = 1;
        break;

    }
    //glutPostRedisplay();
}


/* called on motion when mouse was pressed*/
static void motion (int x, int y)
{
    if(cur_mouseclick_buttonpressed == GLUT_LEFT_BUTTON){
            //MouseSelectedObject.moveTo(x,y);
            IGV->moveTo(x, y);
    } else if(cur_mouseclick_buttonpressed == GLUT_RIGHT_BUTTON){
        if(STATE_ADD_OBSTACLE){
            addCollidableToGrid(x, y);
        }
    }
    // cout << "mouse clicked at " << x << " " << y << endl;
    // cout << "new point at " << newpoint.x << " " << newpoint.y << endl;
    // cout << "points: " << targetPoint.size() << endl;
}

static void mouse (int button, int state, int x, int y)
{
    if(state == GLUT_DOWN){
        switch (button){
            case GLUT_LEFT_BUTTON:
                cur_mouseclick_buttonpressed = GLUT_LEFT_BUTTON;
                // set MouseSelectedObject to the selected object..
                // 
                //if the current select grid square contains teh IGV,
                // tehn select the IGV..
                if ( TheGrid[grid_X(x)][grid_Y(y)]->containsIGV() ){
                    IGV->moveTo(x, y);
                } else {

                }
                // cout << "mouse clicked at " << x << " " << y << endl;
                // cout << "new point at " << newpoint.x << " " << newpoint.y << endl;
            break;
            case GLUT_RIGHT_BUTTON:
                cur_mouseclick_buttonpressed = GLUT_RIGHT_BUTTON;
                if(STATE_ADD_OBSTACLE){
                    addCollidableToGrid(x, y);
                } else if(STATE_ADD_WAYPOINT){
                    IGV->waypoints.newWaypoint(x, y);
                }

            break;
        }
    } else if(state == GLUT_UP){ // GLUT_UP
        // clear MouseSelectedObject to NULL;
        cur_mouseclick_buttonpressed = -1;
    }
}

static void idle(void)
{
    if (going){
         //update();
    }
    glutPostRedisplay();  // calls display()
    //sleep (15);
}

static void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


    if(DRAW_GRID_LINES == true){
        glColor3f (0, 0, 1);
        // the grid lines Y
       for (long double y = graphYMin; y <= graphYMax; y += incr_next_row){
            glBegin (GL_LINES);
                glVertex2f (graphXMin, y);
                glVertex2f (graphXMax, y);
            glEnd();
        }

        // the grid lines X
        for (long double x = graphXMin; x <= graphXMax; x += incr_next_col){
           glBegin (GL_LINES);
               glVertex2f (x, graphYMin);
               glVertex2f (x, graphYMax);
           glEnd();
       }
    }
            // x/y axis
    glColor3f (1, 1, 1);
    glBegin (GL_LINES);
        glVertex2f (0, graphYMax);
        glVertex2f (0, graphYMin);
        glVertex2f (graphXMax, 0);
        glVertex2f (graphXMin, 0);
    glEnd();


    /* Objects on the Real Map */

    // draw red square target
    //drawTarget();

    //void drawTarget(){
    if(IGV->waypoints.size()){
        // draw the next waypoint.. 
        WayPoint* wp = IGV->waypoints.next();
        cout << wp->coord_x << " " << wp->coord_y << endl;
        glColor3f (1, 0, 0);
        glBegin (GL_QUADS);
            glVertex2f ((wp->coord_x - wp->width_coord/2), (wp->coord_y - wp->height_coord/2));
            glVertex2f ((wp->coord_x + wp->width_coord/2), (wp->coord_y - wp->height_coord/2));
            glVertex2f ((wp->coord_x + wp->width_coord/2), (wp->coord_y + wp->height_coord/2) );
            glVertex2f ((wp->coord_x - wp->width_coord/2), (wp->coord_y + wp->height_coord/2) );
        glEnd();  

        std::queue <WayPoint*> wp_queue = IGV->waypoints.getWaypoint_Q();
        wp_queue.pop();
        int wp_length = wp_queue.size();

        glColor3f (0.5, 0.2, 0.9);
        glBegin (GL_QUADS);
        for(int iter = 0; iter < wp_length; iter++){
            wp = wp_queue.front();
            glVertex2f ((wp->coord_x - wp->width_coord/2), (wp->coord_y - wp->height_coord/2));
            glVertex2f ((wp->coord_x + wp->width_coord/2), (wp->coord_y - wp->height_coord/2));
            glVertex2f ((wp->coord_x + wp->width_coord/2), (wp->coord_y + wp->height_coord/2) );
            glVertex2f ((wp->coord_x - wp->width_coord/2), (wp->coord_y + wp->height_coord/2) );
            wp_queue.pop();
        }
        glEnd(); 
    }  

        
    //}

    //target points
    glColor3f (0, 0, 1);
    glPointSize (6.0);
    glBegin (GL_POINTS);
        for (unsigned i=0; i<targetPoint.size(); i++){
            //glVertex2f (targetPoint[i].x, targetPoint[i].y);
        }
    glEnd();


    //SHOW THE REAL MAP
    if(DRAW_SIM_REAL_MAP){
        // show the collidable objects on the map..
        glColor3f (0, 0.1, 1);
        for (unsigned int i = 0; i < collidable_vector.size(); ++i){
            collidable_vector[i]->glow();
        }
    }      

    // SHOW THE MAP THAT THE IGV KNOWS ABOUT...
    if(DRAW_IGV_EXPLORED_MAP){
        // then draw the IGV's map..
         glColor3f (0.1, 0.4, 0.5);
         IGV->displayMap();         // (currently the IGV tells the elements in the map to glow.. )
    }


    // THIS REALLY should be moved to it's own draw function... 
    // for now this just causes the obejcts within the IGV's 
    // search radius to glow a pink color..
    if(going){
        update();
    } // end if going and simuating the IGV


    /* IGV */
    // yellow square (the IGV)  
    //  the igv is located where ever the mouse hs clicked.
    //  that is absolute..
    //  the draw location.. however, is not absolute..
    //  i decide to offsetthe pixels..
    glColor3f (1, 1, 0);
    glPointSize (6.0);
    glBegin (GL_POLYGON);
        glVertex2f (IGV->draw_coord_x, IGV->draw_coord_y + IGV->height_coord);
        glVertex2f (IGV->draw_coord_x, IGV->draw_coord_y);
        glVertex2f (IGV->draw_coord_x + IGV->width_coord, IGV->draw_coord_y);
        glVertex2f (IGV->draw_coord_x + IGV->width_coord, IGV->draw_coord_y + IGV->height_coord);
    glEnd();

    // // best curves
    // for (int i=showBest; i>=0; i--){
    //     glColor3f ((long double) i/(long double)showBest, (((long double)showBest - (long double) i)/(long double)showBest), 0);
    //     //glColor3f (0, 0, 0);
    //     glBegin (GL_LINE_STRIP);
    //         for (long double x = graphXMin; x <= graphXMax; x += 0.125){
    //             glVertex2f (x, ps[i].evaluate(x));
    //         }
    //     glEnd();
    // }

    glFlush();
    glutSwapBuffers();
}

void perform_glow_effect_grid(float coord_x, float coord_y, float bwidth, float bheight){
    // colored square
    
    glBegin (GL_QUADS);
        glVertex2f (coord_x, coord_y);
        glVertex2f (coord_x + bwidth, coord_y);
        glVertex2f (coord_x + bwidth, coord_y + bheight);
        glVertex2f (coord_x, coord_y + bheight);
    glEnd();

    // glFlush();
}



static void resize(int w, int h)
{
    window.width = w;
    window.height = h;
    initializeViewMatrix();
    glViewport (0,0,(GLsizei)window.width, (GLsizei)window.height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D (graphXMin, graphXMax, graphYMin, graphYMax);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void addCollidableToGrid(int x, int y){
    x &= INT_MAX;   // no negatives....(the x and y values are mirrored)
    y &= INT_MAX;
    x = x % window.width;  
    y = y % window.height; 

    vertex newpoint ( x*pixToXCoord + graphXMin,
                      -y*pixToYCoord + graphYMax);

    targetPoint.push_back(newpoint);

    if(TheGrid[grid_X(x)][grid_Y(y)]->object){
        // then its already there...
    } else {
        TheGrid[grid_X(x)][grid_Y(y)]->object = new CollidableObject((x), (y));
        TheGrid[grid_X(x)][grid_Y(y)]->is_object = true;
        //cout << x << " " << grid_X(x) << " " <<  y << " " << grid_Y(y) << endl;
        collidable_vector.push_back(TheGrid[grid_X(x)][grid_Y(y)]->object);
    }
}

/* assumes the grid has been initialized at least once */
void fillGrid(){
    for (int i = 0; i < grid_blocks_x; ++i)
    {
        for (int j = 0; j < grid_blocks_y; ++j)
        {
                if(TheGrid[i][j]->object){
                    // then its already there...
                } else {
                    TheGrid[i][j]->object 
                        = new CollidableObject( i*pix_per_grid_block_x + pix_per_grid_block_x/2,
                                                j*pix_per_grid_block_y + pix_per_grid_block_y/2);
                    TheGrid[i][j]->is_object = true;
                    //cout << x << " " << grid_X(x) << " " <<  y << " " << grid_Y(y) << endl;
                    collidable_vector.push_back(TheGrid[i][j]->object);
                }
        }
    }
}


void clearTheGrid(){
    for (int i = 0; i < grid_blocks_x; ++i)
    {
        for (int j = 0; j < grid_blocks_y; ++j)
        {
            delete TheGrid[i][j];
            TheGrid[i][j] = new GridSquare(i, j, NULL);
        }
    }
}

bool initialize ()
{   
    MouseSelectedObject = NULL; //pls dont call delete on this..
    if(IGV)
        delete IGV;
    IGV = new IGV_Bot(200, 70);

    clearTheGrid();
    targetPoint.clear();
    collidable_vector.clear();
    IGV->waypoints.clear();
    generation = 0;

    return true;
}

bool initGrid(int grid_width, int grid_height){
    TheGrid = new GridSquare**[grid_width];
    for (int i = 0; i < grid_width; ++i){
        TheGrid[i] = new GridSquare*[grid_height];
            for (int j = 0; j < grid_height; ++j)
            {
                TheGrid[i][j] = NULL;
            }
    }

    return true;
}

int main(int argc, char *argv[])
{
    srand (time (0));
    ifstream fin;
    cout << "Loading target points...";
    fin.open(argv[1]);
    if (!fin.fail()){
        while (fin.good()){
            // get input from file here..
        }
        cout << "complete!\n";
    }
    else{
        cout << "\nError: input file not found\n";
    }

    cout << "Initializing Grid..." ;
    cout << "complete!\n" ;
    initGrid(grid_blocks_x, grid_blocks_y);
    cout << "Initializing Simulator...";
    initialize ();
    cout << "complete!\n\n" ;

    glutInit(&argc, argv);
    glutInitWindowSize(window.width,window.height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Grid System");
    glutReshapeFunc(resize);        // called on window resize
    glutDisplayFunc(display);       // called by glutPostRedisplay .. (or in glutMainLoop??)
    glutKeyboardFunc(key);          // interrupt handler on key press
    glutMouseFunc(mouse);           // interrupt handler on mouse click
    glutMotionFunc(motion);         // interrupt handler on mouse move while button pressed
    glutIdleFunc(idle);             // called as much as glut can call it.. in mainLoop();

    glClearColor(0,0,0,0);
    glutMainLoop();

    return EXIT_SUCCESS;
}

/*  
    Options to controlling the rate at which the display is updated:
        (using glutPostRedisplay... or calling the handler function directly..)

    + Control when the glutPostRedisplay() is called by .. 
        -> Polling      ->  Simple calling the glutPostRedisplay in the idle task...
        -> Interrupt    ->  Call the glutPostRedisplay() on an interrupt when an event occurs...


    + Notes on IDLE and DISPLAY funcs ..
        -> IDLE         ->  called all the time as much as glut can call it.. 
*/
