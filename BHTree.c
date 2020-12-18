#include "BHTree.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define EXPAND 1e-5f    /* in order to include every particle inside of the largest quad */
#define THETA 1     /* Tolerance rate */

Particle* create_particle(float x, float y, float vx, float vy){
    Particle *p = malloc(sizeof(Particle));
    p->x = x;
    p->y = y;
    p->vx = vx;
    p->vy = vy;
    return p;
}

int which_child_is(QTNode* pnode, Particle* p){
    
    /* the dividing point */
    float px = pnode->divide_x;
    float py = pnode->divide_y;
    //printf("%d: (%.1f,%.1f)        ", pnode->which_child,px, py);
    float cx = p->x;
    float cy = p->y;
    if (cx > px & cy > py){
        return 0;     /* upper-right */
    } else if (cx < px & cy > py){
        return 1;     /* upper-left */
    } else if (cx < px & cy < py){
        return 2;     /* lower-left */
    } else{
        return 3;     /* lower-right */
    }
}

QTNode* create_node(QTNode* pnode, Particle* p, int w){
    QTNode* cnode = malloc(sizeof(QTNode));
    cnode->particle = p;
    cnode->which_child = w;
    cnode->total_mass = 1;
    if(w == 0){
        cnode->lb = pnode->divide_x;
        cnode->rb = pnode->rb;
        cnode->ub = pnode->ub;
        cnode->db = pnode->divide_y;
    } else if (w == 1){
        cnode->lb = pnode->lb;
        cnode->rb = pnode->divide_x;
        cnode->ub = pnode->ub;
        cnode->db = pnode->divide_y;        
    } else if (w == 2){
        cnode->lb = pnode->lb;
        cnode->rb = pnode->divide_x;
        cnode->ub = pnode->divide_y;
        cnode->db = pnode->db;         
    } else {
        cnode->lb = pnode->divide_x;
        cnode->rb = pnode->rb;
        cnode->ub = pnode->divide_y;
        cnode->db = pnode->db; 
    }
    
    cnode->parent = pnode;
    for(int i=0;i<N;++i){
        cnode->child[i] = NULL;
    }
    return cnode;
}

QTNode* qtree_insert(QTNode* pnode, Particle* p){
    int w, wp;
    if (pnode->total_mass == 1){
        /* Decide the boundray of the child node */
        /* Divide the parent square based on the middle point of the coordinates of the two particles. If one coordinate of the two particles are equal, divide the parent square into equal part in this dimision */
        float px = pnode->particle->x;
        float py = pnode->particle->y;
        float cx = p->x;
        float cy = p->y;
        if(px != cx & py != cy){
            pnode->divide_x = (px+cx)/2;
            pnode->divide_y = (py+cy)/2;
        } else if(px == cx){
            pnode->divide_x = (pnode->lb + pnode->rb)/2;
            pnode->divide_y = (py+cy)/2;
        } else {
            pnode->divide_x = (px+cx)/2;
            pnode->divide_y = (pnode->ub + pnode->db)/2;
        }
        w = which_child_is(pnode,p);
        pnode->child[w] = create_node(pnode,p,w);
        wp = which_child_is(pnode,pnode->particle);
        pnode->child[wp] = create_node(pnode,pnode->particle,wp);
        pnode->particle = NULL;
        ++pnode->total_mass;
    } else {
        w = which_child_is(pnode,p);
        if(pnode->child[w] == NULL){
            pnode->child[w] = create_node(pnode,p,w);
        } else{
            qtree_insert(pnode->child[w],p);
        }
        ++pnode->total_mass;
    }
    return pnode;
}

QTNode* qtree_build(Particle **pset, int n){
    int i;
    QTNode *root, *node;
    /* The boundary of the root. Otherwise I may have to change the size of it each time I add a new particle. */
    float rlb, rrb, rdb, rub;
    rlb = rrb = rdb = rub = 0;
    for(i=0;i<n;i++){
        float x = pset[i]->x;
        float y = pset[i]->y;
        if(x > rrb)
            rrb = x + EXPAND;
        if(x < rlb)
            rlb = x - EXPAND;
        if(y > rub)
            rub = y + EXPAND;
        if(y < rdb)
            rdb = y - EXPAND;
    }
    /* Build the root node */
    root = malloc(sizeof(QTNode));
    root->which_child = -1;  /* Indicating it has no parent */
    root->total_mass = 1;   /* haven't insert the particles */
    root->lb = rlb;
    root->rb = rrb;
    root->db = rdb;
    root->ub = rub;
    root->parent = NULL;
    root->particle = pset[0];
    for(i=0;i<N;i++){
        root->child[i] = NULL;
    }

    /* Place the particle one-by-one */
    node = root;
    for(i=1;i<n;i++){
        node = qtree_insert(node, pset[i]);
    }
    return root;
}

void qtree_ListPrint(QTNode* t){
    if (t != NULL){
        if (t->total_mass == 1){
            printf("(%.3f,%.3f)  ", t->particle->x, t->particle->y);
        }
        else{
            for(int i = 0; i < N; ++i){
                qtree_ListPrint(t->child[i]);
            }
        }  
    }
}

void qtree_summarize(QTNode* t){
    int i;
    if (t->total_mass > 1){
        float tmp_x, tmp_y;
        tmp_x = tmp_y = 0.0;
        for(i=0;i<N;++i){
            if(t->child[i] != NULL){
                qtree_summarize(t->child[i]);
                tmp_x += t->child[i]->center_x * t->child[i]->total_mass;
                tmp_y += t->child[i]->center_y * t->child[i]->total_mass;
            }
        }
        t->center_x = tmp_x / t->total_mass;
        t->center_y = tmp_y / t->total_mass;
        printf("Parent Mass: %d; Coordinates of the center of mass: (%.3f, %.3f)\n", t->total_mass, t->center_x, t->center_y);
        printf("--------------\n");
    }else if (t->total_mass == 1){
        t->center_x = t->particle->x;
        t->center_y = t->particle->y;
        printf("Child %d contains particle (%.3f, %.3f)\n", t->which_child,t->particle->x, t->particle->y);
    } else{
        t->center_x = t->center_y = 0.0;
    }
    return;
}

Particle* instan_speed(Particle *p, QTNode *t, float dt){
    float Fx, Fy;
    Fx = Fy = 0.0;
    if(t != NULL){
        float dx = t->center_x - p->x;
        float dy = t->center_y - p->y;
        if (dx == 0 & dy == 0)
            return p;
        float invDist = 1.0 / sqrtf(dx*dx + dy*dy);
        float invDist3 = invDist*invDist*invDist;
        Fx += dx * invDist3;
        Fy += dy * invDist3;

        if(t->total_mass == 1){
            p->vx += dt * Fx;
            p->vy += dt * Fy;
        } else{
            float crtr = t->total_mass * invDist;
            if (crtr < THETA){
                p->vx += dt * Fx;
                p->vy += dt * Fy;
            } else{
                for(int i = 0; i < N; ++i){
                    p = instan_speed(p, t->child[i], dt);
                }
            }
        }
    }
    return p;
}
Particle** move(QTNode* t, Particle** pset, int n, float dt){
    for(int i = 0; i < n; ++i){
        pset[i] = instan_speed(pset[i],t,dt);
    }
    for(int i = 0; i < n; ++i){
        pset[i]->x += pset[i]->vx * dt;
        pset[i]->y += pset[i]->vy * dt;
    }
    return pset;
}