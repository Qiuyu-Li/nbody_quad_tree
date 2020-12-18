#include "BHTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int main(int argc, char** argv){
    srand(time(NULL));
    const float dt = 0.01;  //time step
    int nParticles = 6;
    int t_move = 10;

    float x,y,vx,vy;
    vx = vy = 0.0;    /* Assume all the particles to be static at time 0 */

    /* Initialize the particles */
    Particle **p = malloc(nParticles*sizeof(Particle*));
    
    for(int i = 0; i < nParticles; ++i){
        x = (rand()/(float)RAND_MAX) * 2 - 1;  // create random points in (-1,1)
        y = (rand()/(float)RAND_MAX) * 2 - 1;
        p[i] = create_particle(x,y,vx,vy);
    }

    /* 
    //Just for testing
    p[0] = create_particle(1,1,0,0);
    p[1] = create_particle(-1,1,0,0);
    p[2] = create_particle(-1,-1,0,0);
    p[3] = create_particle(1,-1,0,0);
    p[4] = create_particle(0.25,0.25,0,0);
    p[5] = create_particle(0.75,0.75,0,0);
    */

    printf("Original particle list:\n");
    for(int i = 0; i < nParticles; ++i){
        printf("(%.3f,%.3f)   ",p[i]->x,p[i]->y);
    }
    printf("\n");
    QTNode* t = qtree_build(p, nParticles);
    printf("\nPrint the particles counterclockwise from upper-rigt.\n");
    qtree_ListPrint(t);
    printf("\n-----------------\n");
    qtree_summarize(t);

    /* Particle movement */
    printf("Particle moves:\n");
    for (int i = 0; i <= t_move; ++i){
        QTNode* newtree = qtree_build(p, nParticles);
        printf("Time %d:  ", i);
        qtree_ListPrint(t);
        p = move(newtree,p,nParticles,dt);
        printf("\n");
    }
}