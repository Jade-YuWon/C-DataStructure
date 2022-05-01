#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX_DIM 3
struct kd_node_t {
    double x[MAX_DIM];
    struct kd_node_t* left, * right;
};

inline double dist(struct kd_node_t* a, struct kd_node_t* b, int dim);
inline void swap(struct kd_node_t* x, struct kd_node_t* y);
struct kd_node_t* find_median(struct kd_node_t* start, struct kd_node_t* end, int idx);
struct kd_node_t* make_tree(struct kd_node_t* t, int len, int i, int dim);
void nearest(struct kd_node_t* root, struct kd_node_t* nd, int i, int dim, struct kd_node_t** best, double* best_dist);
void inorder(struct kd_node_t* T, int dim);
/* 구현 필요 */
bool point_search(struct kd_node_t* root, int dim, kd_node_t* p);
void range_search();
void nearest_neighbor_search();

/* 레벨오더(BFS, 너비우선탐색)를 위한 frunction prototypes */
void printLevelOrder(struct kd_node_t* root, int dim);
struct kd_node_t** createQueue(int*, int*);
void enQueue(struct kd_node_t**, int*, struct kd_node_t*);
struct kd_node_t* deQueue(struct kd_node_t**, int*);

// find distance between two node (a and b)
inline double dist(struct kd_node_t* a, struct kd_node_t* b, int dim)
{
    double t, d = 0;    // t: tmp, d: distance
    while (dim--) {
        t = a->x[dim] - b->x[dim];
        d += t * t;
    }
    return d;
}
inline void swap(struct kd_node_t* x, struct kd_node_t* y) {
    double tmp[MAX_DIM];
    memcpy(tmp, x->x, sizeof(tmp));
    memcpy(x->x, y->x, sizeof(tmp));
    memcpy(y->x, tmp, sizeof(tmp));
}



/* see quickselect method */
struct kd_node_t* find_median(struct kd_node_t* start, struct kd_node_t* end, int idx)
{
    if (end <= start) return NULL;
    if (end == start + 1)
        return start;

    struct kd_node_t* p, * store;
    struct kd_node_t* md = start + (end - start) / 2;
    double pivot;

    while (1) {
        pivot = md->x[idx];

        swap(md, end - 1);
        for (store = p = start; p < end; p++) {
            if (p->x[idx] < pivot) {
                if (p != store)
                    swap(p, store);
                store++;
            }
        }
        swap(store, end - 1);

        /* median has duplicate values */
        if (store->x[idx] == md->x[idx])
            return md;

        if (store > md) end = store;
        else            start = store;
    }
}

/*
호출 방식: root = make_tree(wp, sizeof(wp) / sizeof(wp[1]), 0, 2);
struct kd_node_t wp[] = { {{2, 3}}, {{5, 4}}, {{3, 4}}, {{9, 6}}, {{4, 7}}, {{8, 1}}, {{7, 2}} };
*/
struct kd_node_t* make_tree(struct kd_node_t* t, int len, int i, int dim)
{
    struct kd_node_t* n; // new node

    if (!len) return 0;

    if ((n = find_median(t, t + len, i))) {
        i = (i + 1) % dim;
        n->left = make_tree(t, n - t, i, dim);
        n->right = make_tree(n + 1, t + len - (n + 1), i, dim);
    }
    return n;
}

/* global variable, so sue me */
int visited;

/*
호출방식 nearest(root, &testNode[i], 0, 2, &found, &best_dist);
결과
printf(">> WP tree\nsearching for (%g, %g)\n"
            "found (%g, %g) dist %g\nseen %d nodes\n\n",
            testNode[i].x[0], testNode[i].x[1],
            found->x[0], found->x[1], sqrt(best_dist), visited);
*/
void nearest(struct kd_node_t* root, struct kd_node_t* nd, int i, int dim, struct kd_node_t** best, double* best_dist)
{
    if (!root) return;

    double d = dist(root, nd, dim);

    double dx = root->x[i] - nd->x[i];
    double dx2 = dx * dx;   // dx squared

    visited++;

    if (!*best || d < *best_dist) {
        *best_dist = d;
        *best = root;
    }

    /* if chance of exact match is high */
    if (!*best_dist) return;

    if (++i >= dim) i = 0;

    nearest(dx > 0 ? root->left : root->right, nd, i, dim, best, best_dist);
    if (dx2 >= *best_dist) return;
    nearest(dx > 0 ? root->right : root->left, nd, i, dim, best, best_dist);
}


void inorder(struct kd_node_t* T, int dim) {
    if (T != NULL) {
        inorder(T->left, dim);
        for (int i = 0; i < dim; i++) { printf("%lf ", T->x[i]); }
        printf("\n");
        inorder(T->right, dim);
    }
}

/* 호출 방식 
    struct kd_node_t pointSearchNode[] = { {5, 4}, {4, 7}, {10, 5} };
    struct kd_node_t* p = &pointSearchNode[i]; // i in for loop
    point_search(p);
*/
bool point_search(struct kd_node_t* root, int dim, kd_node_t* p) {
    if (!root) {
        return false;
    }
    int d = 0;
    if (root->x[d] == p->x[d]) {
        d = (++d) % dim;
        if (root->x[d] == p->x[d]) {
            // It should be recursively called "dim" time ...
            // var visited [parameter]
            // var(optional) nearest_point and distance
            return true;
        }
        else {
            // d--; or d = 0;
            // It should be recursively called ...
        }
    }
    else if (root->x[d] < p->x[d]) {
        // go to R Subtree
        // It should be recursively called ...
    }
    else {
        // go to L Subtree
        // It should be recursively called ...
    }

    // Conditions
    // Case #1. 같은 차원에서 값이 모두 고유할 때
    // Case #2. 같은 차원에서 중복되는 값이 있을 때 (i.e., 자식 노드와 값이 같은 경우가 있을 때)


    return false;
}

void range_search() {

}

void nearest_neighbor_search() {

}

/* 아래부터는 레벨오더(BFS, 너비우선탐색) 구현용 함수들임 (없어도 됨) */
void printLevelOrder(struct kd_node_t* root, int dim)
{
    int rear, front;
    struct kd_node_t** queue = createQueue(&front, &rear);
    struct kd_node_t* temp_node = root;

    while (temp_node) {
        for (int i = 0; i < dim; i++) { printf("%lf ", temp_node->x[i]); }
        printf("\n");
        /*Enqueue left child */
        if (temp_node->left)
            enQueue(queue, &rear, temp_node->left);

        /*Enqueue right child */
        if (temp_node->right)
            enQueue(queue, &rear, temp_node->right);

        if (front == rear) {
            break;
        }
        /*Dequeue node and make it temp_node*/
        temp_node = deQueue(queue, &front);
    }
}

#define MAX_Q_SIZE 100

/*UTILITY FUNCTIONS*/
struct kd_node_t** createQueue(int* front, int* rear)
{
    struct kd_node_t** queue = (struct kd_node_t**)malloc(sizeof(struct kd_node_t*) * MAX_Q_SIZE);

    *front = *rear = 0;
    return queue;
}

void enQueue(struct kd_node_t** queue, int* rear, struct kd_node_t* new_node)
{
    queue[*rear] = new_node;
    (*rear)++;
}

struct kd_node_t* deQueue(struct kd_node_t** queue, int* front)
{
    (*front)++;
    return queue[*front - 1];
}



#define N 1000000
#define rand1() (rand() / (double)RAND_MAX)
#define rand_pt(v) { v.x[0] = rand1(); v.x[1] = rand1(); v.x[2] = rand1(); }
int main(void)
{
    int i;
    int len;
    struct kd_node_t wp[] = { // WP Tree
        {{2, 3}}, {{5, 4}}, {{3, 4}}, {{9, 6}}, {{4, 7}}, {{8, 1}}, {{7, 2}}
    };
    struct kd_node_t pointSearchNode[] = { {5, 4}, {4, 7}, {10, 5} };
    struct kd_node_t testNode[] = { {5, 4}, {4, 7} };
    struct kd_node_t* root, * found, * million;
    double best_dist = 10*sqrt(2); // 최대값으로 초기화

    // Build k-D Tree
    root = make_tree(wp, sizeof(wp) / sizeof(wp[1]), 0, 2);

    // Print Tree
    printf("Inorder: \n");
    inorder(root, 2);
    printf("\nLevel Order: \n");
    printLevelOrder(root, 2);
    printf("\n");

    // Point search
    
    len = sizeof(pointSearchNode) / sizeof(struct kd_node_t);
    for (int i = 0; i < len; i++) {
        visited = 0; // global variable init
        found = 0;

        struct kd_node_t* p = &pointSearchNode[i];

        point_search(root, 2, p);
        printf(">> WP tree\nsearching for (%g, %g)\n"
            "found (%g, %g) dist %g\nseen %d nodes\n\n",
            testNode[i].x[0], testNode[i].x[1],
            found->x[0], found->x[1], sqrt(best_dist), visited);
    }
    
    // Nearest neighbor search
    len = sizeof(testNode) / sizeof(struct kd_node_t);
    for (int i = 0; i < len; i++) {
        visited = 0; // global variable init
        found = 0;

        nearest(root, &testNode[i], 0, 2, &found, &best_dist);
        printf(">> WP tree\nsearching for (%g, %g)\n"
            "found (%g, %g) dist %g\nseen %d nodes\n\n",
            testNode[i].x[0], testNode[i].x[1],
            found->x[0], found->x[1], sqrt(best_dist), visited);
    }
    
    return 0;
}
