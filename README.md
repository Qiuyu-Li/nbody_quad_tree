# NBody - a quad-tree version

## Table of Contents

- [Introduction](#introduction)
- [Files](#files)
- [How to run](#how-to-run)
- [Sample output](#sample-output)

## Introduction

A quadtree is built to implement a serial, two-dimensional version of the Barnes-Hut n-body algorithm. Specifically:
Step 1 is to build/add particles to the quadtree; 
Step 2 is to "summarize" the leaf nodes -- i.e., compute the center of mass at each parent; 
Step 3 is to scan the quadtree depth first left to right using the distance threshold to calculate the forces. 

## Files

BHTree.c and BHtree.h are for declaring the quadratic tree structre and related functions;
The BHNbody.c creates a set of particles (default number is 6) with random coordinates and initial speed of 0;
Then, a quadratic tree is built to insert the particles;
Next, I print out the list of the coordinates of the particles; and the summary of the quadratic tree;
Finally, I calculate the position of each of the particles after t_move(default=10) times of movement with a time step of dt(default=0.01); and print the list of the particles' positions after each movement;

## How to run

```
$make
```

```
$./BHNbody
```

## Sample output

```
Original particle list:
(-0.732,-0.699)   (-0.429,-0.387)   (-0.178,-0.631)   (0.861,0.819)   (0.182,-0.335)   (0.708,-0.790)

Print the particles counterclockwise from upper-rigt.
(0.861,0.819)  (0.182,-0.335)  (-0.429,-0.387)  (-0.732,-0.699)  (-0.178,-0.631)  (0.708,-0.790)
-----------------
Child 0 contains particle (0.861, 0.819)
Child 0 contains particle (0.182, -0.335)
Child 2 contains particle (-0.429, -0.387)
Parent Mass: 2; Coordinates of the center of mass: (-0.124, -0.361)
--------------
Parent Mass: 3; Coordinates of the center of mass: (0.205, 0.033)
--------------
Child 2 contains particle (-0.732, -0.699)
Child 1 contains particle (-0.178, -0.631)
Child 3 contains particle (0.708, -0.790)
Parent Mass: 2; Coordinates of the center of mass: (0.265, -0.711)
--------------
Parent Mass: 6; Coordinates of the center of mass: (0.069, -0.337)
--------------
Particle moves:
Time 0:  (0.861,0.819)  (0.182,-0.335)  (-0.429,-0.387)  (-0.732,-0.699)  (-0.178,-0.631)  (0.708,-0.790)
Time 1:  (0.861,0.819)  (0.180,-0.331)  (-0.428,-0.385)  (-0.732,-0.699)  (-0.177,-0.630)  (0.708,-0.789)
Time 2:  (0.860,0.818)  (0.176,-0.324)  (-0.425,-0.383)  (-0.731,-0.698)  (-0.176,-0.627)  (0.707,-0.789)
Time 3:  (0.859,0.817)  (0.170,-0.312)  (-0.421,-0.379)  (-0.729,-0.697)  (-0.175,-0.623)  (0.706,-0.787)
Time 4:  (0.858,0.816)  (0.161,-0.297)  (-0.416,-0.374)  (-0.728,-0.695)  (-0.174,-0.618)  (0.704,-0.786)
Time 5:  (0.856,0.815)  (0.150,-0.277)  (-0.409,-0.368)  (-0.726,-0.693)  (-0.172,-0.611)  (0.703,-0.784)
Time 6:  (0.855,0.813)  (0.137,-0.252)  (-0.401,-0.361)  (-0.723,-0.691)  (-0.169,-0.603)  (0.700,-0.781)
Time 7:  (0.852,0.811)  (0.119,-0.220)  (-0.391,-0.352)  (-0.720,-0.688)  (-0.167,-0.593)  (0.698,-0.779)
Time 8:  (0.850,0.808)  (0.098,-0.180)  (-0.379,-0.342)  (-0.717,-0.685)  (-0.164,-0.582)  (0.695,-0.775)
Time 9:  (0.847,0.806)  (0.069,-0.127)  (-0.366,-0.330)  (-0.713,-0.681)  (-0.160,-0.569)  (0.692,-0.772)
Time 10:  (0.844,0.803)  (0.026,-0.049)  (-0.351,-0.316)  (-0.708,-0.677)  (-0.156,-0.555)  (0.688,-0.768)
```