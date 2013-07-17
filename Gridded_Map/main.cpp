/******************************************************************************************
    


*********************************************************************************************/
 
#include "PSeries.h"
#include "Vertex.h"
#include "GA_CONSTANTS.h"
#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
//#include <windows.h>
#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>

using namespace std;


long double randomFloat ();
void initialize ();
void score ();
void update ();
void displayBest ();
void perform_glow_effect_grid(float coord_x, float coord_y, float bwidth, float bheight);

bool operator < (PSeries first, PSeries second){return first.difference < second.difference;}


/*  Important Consideration:
        Pixel coordinates start at top left of screen..
        Graph coordinates start at the center and are proportional 
            to 1 pixel  by  graphXRange/width and graphYRange/height.

        THE GRID starts at the top left (sits TheGrid[0][0])

        Problem:    Map pixel clicks to TheGrid Index..

*/
// window
static int height = 600;
static int width = 800;

// X graph min/max + ratio
static float graphXMin = -12;
static float graphXMax = 12;
float graphXRange = graphXMax - graphXMin;
float pixToXCoord = graphXRange/width;

// Y graph min/max + ratio
static float graphYMin = -9;
static float graphYMax = 9;
float graphYRange = graphYMax - graphYMin;
float pixToYCoord = graphYRange/height;

// GRID width & height of entire window..
const static int grid_width     = 7;
const static int grid_height    = 7;
const static float pix_per_grid_width  = (width * 1.0) / (grid_width-1);        
const static float pix_per_grid_height = (height * 1.0) / (grid_height-1);
float incr_next_col = graphXMax / (grid_width/2);
float incr_next_row = graphYMax / (grid_height/2);

/* Finds the indecies in the grid at pixel x..*/
#define grid_X(x) (int)(x / pix_per_grid_width) 
#define grid_Y(y) (int)(y / pix_per_grid_height)

class Player{
    public:
        Player(){ x = 0; y = 0;}
        int x;  //pixels..
        int y;

};


class CollidableObject{
    public: 
        CollidableObject(){}
        CollidableObject(int _x, int _y, unsigned char _type = 0){
            x = _x;   y = _y;   type = _type;   
     
            coord_x = grid_X(x) * pix_per_grid_width*pixToXCoord + graphXMin; 
            coord_y = -1*((grid_Y(y)+1) * pix_per_grid_height*pixToYCoord) + graphYMax; 
            width = pix_per_grid_width*pixToXCoord;
            height = pix_per_grid_height*pixToYCoord;
        }

        void glow_red(){
            glColor3f (1, 0.1, 0);
            perform_glow_effect_grid(coord_x, coord_y, width, height); 
        }
        void glow(){ 
            glColor3f (0.5, 0.2, 0);
            perform_glow_effect_grid(coord_x, coord_y, width, height); 
        }

        unsigned char type;
        int x;  //pixels
        int y;

        // in graph coordinates...
        float coord_x;
        float coord_y;
        float width;
        float height;
};


// or maybe a grid tree?
class GridSquare{
    public:
        GridSquare(CollidableObject* obj_to_set = NULL){
            is_object = false;
            object = obj_to_set;
        }
        void glow(){ }
        bool is_object;
        CollidableObject* object;
        int x;   //pixels
        int y;
};




//PSeries
vector <PSeries> ps;

//Target Points
vector <vertex> targetPoint;
vector <CollidableObject*> collidable_vector;

/* THE GRID */
GridSquare*  TheGrid[grid_width][grid_height];
Player PLAYER;





static float PLAYER_X       = 1.0; 
static float PLAYER_Y       = 1.0;
static float PLAYER_WIDTH   = 1.0;


bool going (false);
int generation = 0;
int showBest = 1;
unsigned int cur_mouseclick_buttonpressed = -1;







void  initializeViewMatrix ()
{
    pixToXCoord = graphXRange/width;
    pixToYCoord = graphYRange/height;
}

long double randomFloat (){
    long double x=((long double)rand()/(long double)RAND_MAX);
    return x;
}

PSeries randomPSeries (int maxdegree)
{
    PSeries p;
    for (int j=0; j<=maxdegree; j++){
        p.addTerm( -(randomFloat() * initial[j])/2.0 + (randomFloat() * initial[j]) );
    }

    return p;
}

/* determine the total difference of the given pseries  */
void score ()
{
    for (unsigned i=0; i<ps.size(); i++){
        long double totalDifference = 0;
        for (unsigned j=0; j<targetPoint.size(); j++){

            // difference between y values... (from line to target..)
            totalDifference += abs(ps[i].evaluate(targetPoint[j].x) - targetPoint[j].y );
        }
        ps[i].difference = totalDifference;
        ps[i].avgDifference = totalDifference/targetPoint.size();
    }
    stable_sort (ps.begin(), ps.end());
}

/* Calling during idling... Animates the PSeries on the screen 
    Main logic...
*/
void update ()
{


    // vector <PSeries> newGen;
    // newGen.resize(MAX_POPULATION+CLONES);

    // unsigned i=0;
    // for (; i<CLONES; i++){
    //     newGen[i] = ps[i];
    // }
    // for (; i<newGen.size(); i++){
    //     PSeries parent1 = ps[ rand()%ps.size() * PARENTING_RATE ];
    //     PSeries parent2 = ps[ rand()%ps.size() * PARENTING_RATE ];
    //     PSeries child;

    //     int crossover = rand()%(MAX_DEGREE+1);
    //     for (int j=0; j<crossover; j++){
    //         child.addTerm(parent1.coefficient[j]);
    //     }
    //     for (int j=crossover; j<=MAX_DEGREE; j++){
    //         child.addTerm(parent2.coefficient[j]);
    //     }

    //     if (randomFloat() <= MUTATION_RATE){
    //         int mutatedGene = rand()%(MAX_DEGREE+1);
    //         if (rand()%2 == 1)
    //             child.coefficient[mutatedGene] += (randomFloat () * modifier[mutatedGene]);
    //         else
    //             child.coefficient[mutatedGene] -= (randomFloat () * modifier[mutatedGene]);
    //     }
    //     newGen[i] = child;
    // }
    // ps = newGen;
    // generation++;
    // score();    // determine distance between current result and expected results

}

void displayBest ()
{
    cout << "Best candidate from generation " << generation << "\n";
    cout << "Y =";
    for (unsigned j=0; j<ps[0].coefficient.size(); j++){
        if (ps[0].coefficient[j] != 0){
            cout << " ("  << ps[0].coefficient[j] << " * X^" << j << ") ";
            if (j < ps[0].coefficient.size()-1)
                cout << "+";
        }
    }
    cout << "\n";
    cout << "\ttotal difference  : " << ps[0].difference << "\n";
    cout << "\taverage difference: " << ps[0].avgDifference << "\n\n";
}




static void key(unsigned char key, int x, int y)
{
    switch (key){
        case 't':
        case 'T':
            update();
            displayBest();
         break;

        case 'g':
        case 'G':
            going = !going;
         break;

        case 'c':
        case 'C':
            targetPoint.clear();
            generation = 0;
        break;

        case 'r':
        case 'R':
            initialize();
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
            PLAYER_X = (x * pixToXCoord + graphXMin)  - PLAYER_WIDTH/2;
            PLAYER_Y = (-y * pixToYCoord + graphYMax) - PLAYER_WIDTH/2;

            PLAYER.x = x;
            PLAYER.y = y;
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
                PLAYER_X = (x * pixToXCoord + graphXMin)  - PLAYER_WIDTH/2;
                PLAYER_Y = (-y * pixToYCoord + graphYMax) - PLAYER_WIDTH/2;
                 PLAYER.x = x;
                PLAYER.y = y;

                // cout << "mouse clicked at " << x << " " << y << endl;
                // cout << "new point at " << newpoint.x << " " << newpoint.y << endl;
            break;
            case GLUT_RIGHT_BUTTON:
                cur_mouseclick_buttonpressed = GLUT_RIGHT_BUTTON;
                vertex newpoint ( x*pixToXCoord + graphXMin,
                                  -y*pixToYCoord + graphYMax);
                targetPoint.push_back(newpoint);


                TheGrid[grid_X(x)][grid_Y(y)]->object = new CollidableObject((x), (y));
                TheGrid[grid_X(x)][grid_Y(y)]->is_object = true;
                cout << x << " " << grid_X(x) << " " <<  y << " " << grid_Y(y) << endl;
                collidable_vector.push_back(TheGrid[grid_X(x)][grid_Y(y)]->object);
            break;
        }
    } else { // GLUT_UP
        cur_mouseclick_buttonpressed = -1;
    }
}

static void idle(void)
{
    if (going){
        if (ps[0].avgDifference > TARGET_AVG_DIFFERENCE && generation < MAX_GENERATIONS){
            update();
        }
    }
    glutPostRedisplay();  // calls display()
    //sleep (15);
}

static void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

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


    
    // x/y axis
    glColor3f (1, 1, 1);
    glBegin (GL_LINES);
        glVertex2f (0, graphYMax);
        glVertex2f (0, graphYMin);
        glVertex2f (graphXMax, 0);
        glVertex2f (graphXMin, 0);
    glEnd();

    // red square
    glColor3f (1, 0, 0);
    glBegin (GL_QUADS);
        glVertex2f (0.5 , 0.5 );
        glVertex2f (1.5 , 0.5 );
        glVertex2f (1.5 , 1.5 );
        glVertex2f (0.5 , 1.5 );
    glEnd();





    //target points
    glColor3f (0, 0, 1);
    glPointSize (6.0);
    glBegin (GL_POINTS);
        for (unsigned i=0; i<targetPoint.size(); i++){
            glVertex2f (targetPoint[i].x, targetPoint[i].y);
        }
    glEnd();

    //for all collidable objects.. call its "glow" function..
    for (unsigned int i = 0; i < collidable_vector.size(); ++i){
        collidable_vector[i]->glow();
    }

       

    if (TheGrid[grid_X(PLAYER.x)][grid_Y(PLAYER.y)]->is_object){
        TheGrid[grid_X(PLAYER.x)][grid_Y(PLAYER.y)]->object->glow_red();
    }



    // yellow square (the player)
    glColor3f (1, 1, 0);
    glPointSize (6.0);
    glBegin (GL_POLYGON);
        glVertex2f (PLAYER_X , PLAYER_Y + PLAYER_WIDTH  );
        glVertex2f (PLAYER_X , PLAYER_Y    );
        glVertex2f (PLAYER_X    + PLAYER_WIDTH, PLAYER_Y   );
        glVertex2f (PLAYER_X    + PLAYER_WIDTH, PLAYER_Y   + PLAYER_WIDTH);
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
    width = w;
    height = h;
    initializeViewMatrix();
    glViewport (0,0,(GLsizei)width, (GLsizei)height);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D (graphXMin, graphXMax, graphYMin, graphYMax);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void initialize ()
{
    generation = 0;
    ps.clear();
    ps.resize(MAX_POPULATION);
    for (int i=0; i<MAX_POPULATION; i++){
         ps[i] = randomPSeries(MAX_DEGREE);
    }
    for (int i = 0; i < grid_width; ++i)
    {
        for (int j = 0; j < grid_height; ++j)
        {
            TheGrid[i][j] = new GridSquare(NULL);
        }
    }
}

int main(int argc, char *argv[])
{
    srand (time (0));
    ifstream fin;
    cout << "Loading target points...";
    fin.open(argv[1]);
    if (!fin.fail()){
        while (fin.good()){
            long double newX, newY;
            fin >> newX >> newY;
            vertex newTargetPoint (newX, newY);
            targetPoint.push_back(newTargetPoint);
        }
        cout << "complete!\n";
    }
    else{
        cout << "\nError: input file not found\n";
    }

    cout << "Initializing population...";
    initialize ();
    cout << "complete!\n\n";

    score ();
    displayBest();

    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Curve Fit");
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
