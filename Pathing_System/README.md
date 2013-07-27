IGV Pathing
=======

Simple Pathing that overlays the Simple Grid System..

####TODO:		
>fix the coordinate system.. haha
>each grid points to a "GridSquare".. should point to our tree structure..
>(each sub layer performs the same as the last layer..
>(where the fractional part of the vector is used to interact with the next layer..
>(Please keep considering alternatives.. as this can easily change..

Usage
-----

$ make  
$ igv_sim

Click anywhere in the window to add new points.

Mouse
----
- Left Button   Move IGV.  (TODO: Select IGV Destination)
- Right Button  Add obstacle to grid.

Keys
----

- 'c'  Create randomized obstacles
- 'g'  Start Simulation
- 'r'  Remove Obstacles
- 'f'  Fill Grid With Obstacles..
- 't'  call update() directly..

- '!'  Show/Hide Grid lines
- '@'  Show/Hide Real Map
- '#'  Show/Hide IGV's generated Map based exploration of Real map.

