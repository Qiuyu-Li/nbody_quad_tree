#define N 4     /* Quadratic tree */

typedef struct {
    float x,y,vx,vy;
}Particle;

typedef struct qtnode_{
    Particle *particle;
    int which_child;
    float divide_x, divide_y;   /* Dividing point of this node (if it contains two or more particles*/
    float center_x, center_y;   /* Coordinates of the center of mass */
    int total_mass;
    float lb, rb, db, ub;
    struct qtnode_* parent;
    struct qtnode_* child[N];
}QTNode;

Particle* create_particle(float x, float y, float vx, float vy);
int which_child_is(QTNode* pnode, Particle* p);
QTNode* create_node(QTNode* pnode, Particle* p, int w);
QTNode* qtree_insert(QTNode* pnode, Particle* p);
QTNode* qtree_build(Particle **pset, int n);
void qtree_ListPrint(QTNode* t);
void qtree_summarize(QTNode* t);
Particle* instan_speed(Particle *p, QTNode *t, float dt);
Particle** move(QTNode* t, Particle** pset, int n, float dt);