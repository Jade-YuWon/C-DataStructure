#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

#define MAX_ELE 10000
#define MAX_DIM 3

struct kd_node_t {
    double x[MAX_DIM];
    struct kd_node_t* left, * right;
};
struct distance {
    double dist;
    double x;
    double y;
};

/* given code */
inline double dist(struct kd_node_t* a, struct kd_node_t* b, int dim);
inline void swap(struct kd_node_t* x, struct kd_node_t* y);
struct kd_node_t* find_median(struct kd_node_t* start, struct kd_node_t* end, int idx);
struct kd_node_t* make_tree(struct kd_node_t* t, int len, int i, int dim);

/* code we made */
void inorder(struct kd_node_t* T, int dim); //insert points in order
bool point_search(struct kd_node_t* root, int d, const int dim, struct kd_node_t* p);
void range_search(struct kd_node_t* root, const int len, struct kd_node_t* p);
void near_search(struct kd_node_t* root, const int kd_num, struct kd_node_t* p);
void printLevelOrder(struct kd_node_t* root, int dim);
struct kd_node_t** createQueue(int*, int*);
void enQueue(struct kd_node_t**, int*, struct kd_node_t*);
struct kd_node_t* deQueue(struct kd_node_t**, int*);

// find distance between two node (a and b)
inline double dist(struct kd_node_t* a, struct kd_node_t* b, int dim) {
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
struct kd_node_t* find_median(struct kd_node_t* start, struct kd_node_t* end, int idx) {
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

/*function call
root = make_tree(kd_nodes, sizeof(kd_nodes) / sizeof(kd_nodes[1]), 0, 2);
struct kd_node_t kd_nodes[] = { {{2, 3}}, {{5, 4}}, {{3, 4}}, {{9, 6}}, {{4, 7}}, {{8, 1}}, {{7, 2}} };
*/
struct kd_node_t* make_tree(struct kd_node_t* t, int len, int i, int dim) {
    struct kd_node_t* n; // new node

    if (!len) return 0;

    if ((n = find_median(t, t + len, i))) {
        i = (i + 1) % dim;
        n->left = make_tree(t, n - t, i, dim);
        n->right = make_tree(n + 1, t + len - (n + 1), i, dim);
    }
    return n;
}

void inorder(struct kd_node_t* T, int dim) {  //make Tree in order
    if (T != NULL) {
        inorder(T->left, dim);
        for (int i = 0; i < dim; i++) {
            printf("%lf ", T->x[i]);
        }
        printf("\n");
        inorder(T->right, dim);
    }
}

/* function call
    struct kd_node_t pointSearchNode[] = { {5, 4}, {4, 7}, {10, 5} };
    struct kd_node_t* p = &pointSearchNode[i]; // i in for loop
    point_search(root, 0, 2, p);
*/
bool point_search(struct kd_node_t* root, int d, const int dim, struct kd_node_t* p) {
    if (!root) {
        return false;
    }
    if (d == dim) {
        d %= dim;
    }

    if (root->x[d] == p->x[d]) {
        int tmp = d;
        for (int i = d + 1; i < dim; i++) {
            if (root->x[i] == p->x[i])
                continue;
            else
                point_search(root, tmp, dim, p);
        }
        return true;
    }
    else if (root->x[d] < p->x[d]) {
        // go to R Subtree
        point_search(root->right, ++d, dim, p);
    }
    else {
        // go to L Subtree
        point_search(root->left, ++d, dim, p);
    }
}

/* function call
    struct kd_node_t rangeSearchNode[] = { {6, 3}, {9, 7} };
    len = sizeof(wp) / sizeof(struct kd_node_t);
    range_search(root, 0, 2, len, rangeSearchNode);
*/
void range_search(struct kd_node_t* root, const int kd_num, struct kd_node_t* p) {
    struct kd_node_t* treeArr[MAX_ELE]; // store k-d tree in a linear array
    int rear, front;
    struct kd_node_t** queue = createQueue(&front, &rear);
    int j = 0;

    while (root) {
        treeArr[j++] = root;
        if (j == kd_num) break;
        /*Enqueue left child */
        if (root->left)
            enQueue(queue, &rear, root->left);

        /*Enqueue right child */
        if (root->right)
            enQueue(queue, &rear, root->right);

        if (front == rear) {
            break;
        }
        /*Dequeue node and make it temp_node*/
        root = deQueue(queue, &front);
    }

    for (int i = 0; i < kd_num; i++) {
        if (p[0].x[0] <= treeArr[i]->x[0] && p[0].x[1] <= treeArr[i]->x[1]
            && treeArr[i]->x[0] <= p[1].x[0] && treeArr[i]->x[1] <= p[1].x[1]) {
            printf("Found (%lf, %lf)\n", treeArr[i]->x[0], treeArr[i]->x[1]);
        }
    }

}


void near_search(struct kd_node_t* root, const int kd_num, struct kd_node_t* p) {
    int index = 0;
    int rear, front;
    double dx, dx2, dy, dy2;
    struct distance* tmp = (struct distance*)malloc(sizeof(struct distance));
    struct distance* dis[MAX_ELE];
    //struct distance** dis = (struct distance**)malloc(kd_num * sizeof(struct distance*));
    struct kd_node_t* treeArr[MAX_ELE]; // store k-d tree in a linear array
    struct kd_node_t** queue = createQueue(&front, &rear);

    for (int i = 0; i < kd_num; i++) {
        dis[i] = (struct distance*)malloc(sizeof(struct distance));
    }

    while (root) {
        treeArr[index++] = root;

        if (index == kd_num) break;
        /*Enqueue left child */
        if (root->left)
            enQueue(queue, &rear, root->left);

        /*Enqueue right child */
        if (root->right)
            enQueue(queue, &rear, root->right);

        if (front == rear) {
            break;
        }

        /*Dequeue node and make it temp_node*/
        root = deQueue(queue, &front);
    }

    // Calculates distances of every nodes
    for (int i = 0; i < kd_num; i++) {
        dx = treeArr[i]->x[0] - p[0].x[0];
        dx2 = dx * dx;
        dy = treeArr[i]->x[1] - p[0].x[1];
        dy2 = dy * dy;

        dis[i]->dist = dx2 + dy2;
        dis[i]->x = treeArr[i]->x[0];
        dis[i]->y = treeArr[i]->x[1];
    }

    // rearrange dis[] array in ascending order 
    for (int i = 0; i < kd_num - 1; i++) {
        for (int j = i + 1; j < kd_num; j++) {
            if (dis[i]->dist > dis[j]->dist) {
                tmp = dis[i];
                dis[i] = dis[j];
                dis[j] = tmp;
            }
        }
    }

    for (int i = 1; i < kd_num; i++) {
        printf("point : %lf %lf\tdist^2 : %lf\n", dis[i]->x, dis[i]->y, dis[i]->dist);
    }
}

/* 아래부터는 레벨오더(BFS, 너비우선탐색) 구현용 함수들임 (없어도 됨) */
void printLevelOrder(struct kd_node_t* root, int dim) {
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
struct kd_node_t** createQueue(int* front, int* rear) {
    struct kd_node_t** queue = (struct kd_node_t**)malloc(sizeof(struct kd_node_t*) * MAX_Q_SIZE);

    *front = *rear = 0;
    return queue;
}

void enQueue(struct kd_node_t** queue, int* rear, struct kd_node_t* new_node) {
    queue[*rear] = new_node;
    (*rear)++;
}

struct kd_node_t* deQueue(struct kd_node_t** queue, int* front) {
    (*front)++;
    return queue[*front - 1];
}

#define N 1000000
#define rand1() (rand() / (double)RAND_MAX)
#define rand_pt(v) { v.x[0] = rand1(); v.x[1] = rand1(); v.x[2] = rand1(); }
int main(void) {
    int len;
    int kd_num;
    struct kd_node_t kd_nodes[] = { // K-D Tree Elements
        {{2, 3}}, {{5, 4}}, {{3, 4}}, {{9, 6}}, {{4, 7}}, {{8, 1}}, {{7, 2}}
    };
    struct kd_node_t pointSearchNode[] = { {5, 4}, {4, 7}, {10, 5} }; // search each point
    struct kd_node_t rangeSearchNode[] = { {6, 3}, {9, 7} }; // Bounding Rectangle's starting and end points
    struct kd_node_t nearstSearchNode[] = { {5, 4}, {4, 7} }; // find nearst nodes from each point
    struct kd_node_t* root;

    // Build k-D Tree
    root = make_tree(kd_nodes, sizeof(kd_nodes) / sizeof(kd_nodes[1]), 0, 2);
    kd_num = sizeof(kd_nodes) / sizeof(struct kd_node_t);

    // Print Tree
    printf("Inorder: \n");
    inorder(root, 2);
    printf("\nLevel Order: \n");
    printLevelOrder(root, 2);
    printf("\n");

    // 1. Point search
    len = sizeof(pointSearchNode) / sizeof(struct kd_node_t);  // number of point search nodes
    for (int i = 0; i < len; i++) {
        struct kd_node_t* p = &pointSearchNode[i];
        printf("Search (%lf, %lf):\n", p->x[0], p->x[1]);

        if (point_search(root, 0, 2, p))
            printf("Found\n");
        else 
            printf("None\n");
    }
    printf("\n");

    // 2. Range Search
    printf("Bounding Rectangle\n"
        "- Starting point: (%lf, %lf), End point: (%lf, %lf)\n", rangeSearchNode[0].x[0], rangeSearchNode[0].x[1],
        rangeSearchNode[1].x[0], rangeSearchNode[1].x[1]);
    range_search(root, kd_num, rangeSearchNode);
    printf("\n");

    //3.nearest neighbor
    len = sizeof(nearstSearchNode) / sizeof(struct kd_node_t);
    for (int i = 0; i < len; i++) {
        struct kd_node_t* p = &nearstSearchNode[i];
        printf("Nearset Neighbor Search [%lf, %lf]\n", p->x[0], p->x[1]);
        near_search(root, kd_num, p);
        printf("\n");
    }

    return 0;
}
