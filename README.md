###IGV_Simulator


>####Simulates the Motion of the IGV
>##### Pathfinding..
--

## Project Details:

>  +  2d Map of Terrain contains: Obstacles, GPS Waypoints.
>  +  We need to get from Start to Target..
   
   
## Problems:

>  +  How can we describe objects in the map?
>  +  How do we find the list of nearby objects we are interested in?
>  +  What methodology is needed to find a path?
>  +  How can we be sure that our path is **drivable**?
>  +  How do we define **drivable**? (ie: max turn radius at given speeds, not enough space, ..)
  

  
## Solutions:

>   1.  Map<> 
>   2.  Using IGV(x,y) .. index into map.. 
>   3.  A* 
>   4.  JSmoke libraries :)
>   5.  ...

## Ideas:

#### Path:
Map starts out fully drivable with no obstacles..

Open space. Drivable along path: Start -> GPS Points -> Target 

  + When IGV detects obstacle.. create two nodes, to the left and right of the obstacle (store in graph with distances h)
  
Detect obstacle with Camera Code..

However, in the simulator we detect an obstacle by finding it in a map structure of some sort...

>   Use kd tree.

