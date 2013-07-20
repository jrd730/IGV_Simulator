###IGV_Simulator


>####Simulates the Motion of the IGV
>##### Pathfinding..
--

## Project Details:

>  +  Simualator contains 2D map of environment..
>  +  Environment contains: Bot, Obstacles, GPS_Waypoints
>  +  Bot needs to be able to move through the simulator; Pathfind from Start to Target
>  +  Bot contains:  It's own information about the environment..
   
   
## Problems:

>  +  How can we describe objects in the map?
>  +  How do we find the list of nearby objects we are interested in?
>  +  What methodology is needed to find a path?
>  +  How can we be sure that our path is **drivable**? (A Path is one thing, the physical limitations of the IGV are another..)
>  +  How do we define **drivable**? (ie: max turn radius at given speeds, not enough space, ..) 

## 
--
>  +  Bot has Search Radius. When an obstacle enters the Bot radius.. the Bot must store the position of said obstacle
>  +  in it's internal map. (The Obstacle has it's own properties/functions that describe it's surface)
>  +  When we need to generate the Bot's Path, the Bot needs to consider Obstacles in it's map
>  +  When we need to identify obstacles.. we need to make a prediction given the information about the obstacle..
 
>> #####   Predictions are based on: 
>> +  Surface Structure (the part that is visible to us from our perspective)
>> +  Color..


  
## Solutions:

>   1.  Points, whose shape covers a discrete surface area of the map.. stored in the Grid Map System
>   2.  Using IGV(x,y) .. index into Grid Map.. +/- searchRadius
>   3.  A* -> store/update path in graph structure (of paths) .. based on IGV's Discovered Environment
>   4.  JSmoke libraries :)
>   5.  (Define Limitations.. apply them to generating a close to optimal path.. maybe use some sampling techniques based on previous turning experience..
 aka: we would have to train the bot by manually driving it... and generate Weights for turns and motion.. etc.. then we come back here and use our collected data...)

## Ideas:

Simulator starts off with a Map of the World:
	Map contains:
		- IGV
		- Obstacles
	Logic contains:
		- Collisions
		- Drawing stuff onto screen


IGV
	Map contains:  
		( generated as exploration continues..
		  IGV update's its location and it's environment
		  in it's own map of the world )
		- IGV
		- Obstacles
		- Waypoints
	Graph contains:
		- Pathing data.. (relative/(and based solely on)/to the Map it has generated..)
	Logic contains:
		- Driving, (updating it's location on the Simulator map..)
		- Update It's own map by discovering Surroundings.
		- Determine Pathing_Data given IGVs Map.. 
		- Determine the likeliness this path is Correct, given Limitations and Error of Data..
		- Make corrections and chose better path -> so the that IGV doesnt crash and burn..
			(better is not more optimal.. it is just Drivable..)

	-> these are things to consider.. 

####Please make changes to Ideas that need be updated. (for: accuracy & feasability)
