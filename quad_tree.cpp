/*
* File: Quad_Tree.cpp
*
* Author1: Park Yongwoo
* Author2: Yun Jaesang
* Author3: Park Yuwon
* Author4: Kim Hyekang
*
* Date: 2022.05.16
*
* Course: Data Structures(14461_002)
*
* Summary of File
*   This file build Quad Tree and search points by using Point Search and Range Search
*/
#include <stdio.h>
#include <stdlib.h>

struct POINT {
    float x;
    float y;
};
struct NODE {
    struct POINT range1; // Bounding Rectangle's Left-bottom point
    struct POINT range2; // Bounding Rectangle's Right-top point
    struct POINT* p;
    struct NODE* c1; // North East Quadrant
    struct NODE* c2; // Nort West Quadrant
    struct NODE* c3; // South West Quadrant
    struct NODE* c4; // South East Quadrant
    /*
         _______range2
         |c2│c1|
         |─┼─|
         |c3│c4|
    range1─┴─-
    */
};

NODE* getNewNode(POINT* k);
void insertTree(NODE* root, POINT* k);
bool pointSearch(NODE* root, POINT* k);
bool range_search(NODE* root, POINT* k, POINT start, POINT end);
void printp(POINT p);

/*
* Authors: Park Yongwoo
* NODE * getNewNode(POINT* k)
*
* Summary of getNewNode function:
*   Make new NODE, give point k for newNode's point and Initialize it's c1,c2,c3 and c4
*
* Parameters    : point k to give point value to newNode's point
*
*/
NODE* getNewNode(POINT* k) {
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->p = (POINT*)malloc(sizeof(POINT));
    newNode->p = k;
    newNode->c1 = NULL;
    newNode->c2 = NULL;
    newNode->c3 = NULL;
    newNode->c4 = NULL;
    return newNode;
}

/*
* Authors: Kim Hyekang, Park Yongwoo, Yun Jaesang, Park Yuwon
* void insertTree(NODE* root, POINT* k)
*
* Summary of insertTree function:
*   x1, x2, y1, y2 is range value (x1,y1) ~ (x2,y2) to find location(c1,c2,c3,c4) where we want to save.
*   if location we want to save contains point more than one, using recursive function and modify range and save each point. ex) c1->c1, c2-c3->c4
*
* Parameters    : root NODE for tree root, and POINT k for point value to save.
*/
void insertTree(NODE* root, POINT* k) {
    float x1 = root->range1.x;
    float x2 = root->range2.x;
    float y1 = root->range1.y;
    float y2 = root->range2.y;

    if (k->x <= (x1 + x2) / 2) {    //check location by checking range (x1,y1) to (x2,y2)
        if (k->y <= (y1 + y2) / 2) {    //check location by checking range (x1,y1) to (x2,y2)

            if (root->c3 == NULL)   // it means there are more than one point? if not, make new NODE by using getNewNode
                root->c3 = getNewNode(k);
            else {
                if (root->c3->p != NULL) {  // it means there are more than one point? if it contains more than one point, modify range and do recursion
                    NODE* n = root->c3;
                    root->c3->range1 = { x1, y1 };
                    root->c3->range2 = { (x1 + x2) / 2, (y1 + y2) / 2 };

                    insertTree(root->c3, n->p);
                    root->c3->p = NULL; //if there are more than one point, after recursive function, original point value for NULL.
                }
                insertTree(root->c3, k);
            }
        }
        else {
            if (root->c2 == NULL)   // it means there are more than one point? if not, make new NODE by using getNewNode
                root->c2 = getNewNode(k);
            else {
                if (root->c2->p != NULL) {  // it means there are more than one point? if it contains more than one point, modify range and do recursion
                    NODE* n = root->c2;
                    root->c2->range1 = { x1, (y1 + y2) / 2 };
                    root->c2->range2 = { (x1 + x2) / 2, y2 };

                    insertTree(root->c2, n->p);
                    root->c2->p = NULL; //if there are more than one point, after recursive function, original point value for NULL.
                }
                insertTree(root->c2, k);
            }
        }
    }
    else {
        if (k->y <= (y1 + y2) / 2) {
            if (root->c4 == NULL)   // it means there are more than one point? if not, make new NODE by using getNewNode
                root->c4 = getNewNode(k);
            else {
                if (root->c4->p != NULL) {  // it means there are more than one point? if it contains more than one point, modify range and do recursion
                    NODE* n = root->c4;
                    root->c4->range1 = { (x1 + x2) / 2, y1 };
                    root->c4->range2 = { x2, (y1 + y2) / 2 };

                    insertTree(root->c4, n->p);
                    root->c4->p = NULL; //if there are more than one point, after recursive function, original point value for NULL.
                }
                insertTree(root->c4, k);
            }
        }
        else {
            if (root->c1 == NULL)   // it means there are more than one point? if not, make new NODE by using getNewNode
                root->c1 = getNewNode(k);
            else {
                if (root->c1->p != NULL) {  // it means there are more than one point? if it contains more than one point, modify range and do recursion
                    NODE* n = root->c1;
                    root->c1->range1 = { (x1 + x2) / 2, (y1 + y2) / 2 };
                    root->c1->range2 = { x2, y2 };

                    insertTree(root->c1, n->p);
                    root->c1->p = NULL; //if there are more than one point, after recursive function, original point value for NULL.
                }
                insertTree(root->c1, k);
            }
        }
    }
}

/*
* Authors: Park Yongwoo, Park Yuwon, Kim Hyekang
* bool pointSearch(NODE* root, POINT *k)
*
* Summary of pointSearch function:
*   get point value and check if that value is in  tree
*
* Parameters    : get tree(root) and find k point value in root
*/
bool pointSearch(NODE* root, POINT* k) {
    float x1 = root->range1.x;
    float x2 = root->range2.x;
    float y1 = root->range1.y;
    float y2 = root->range2.y;
    if (k->x <= (x1 + x2) / 2) {
        if (k->y <= (y1 + y2) / 2) {
            if (root->c3->p == NULL) {  //if point value is NULL modify it's range and execute recursion
                root->c3->range1 = { x1, y1 };
                root->c3->range2 = { (x1 + x2) / 2, (y1 + y2) / 2 };
                pointSearch(root->c3, k);
            }
            else
                return (root->c3->p->x == k->x && root->c3->p->y == k->y);
        }
        else {
            if (root->c2->p == NULL) {  //if point value is NULL modify it's range and execute recursion
                root->c2->range1 = { x1, (y1 + y2) / 2 };
                root->c2->range2 = { (x1 + x2) / 2, y2 };
                pointSearch(root->c2, k);
            }
            else
                return (root->c2->p->x == k->x && root->c2->p->y == k->y);
        }
    }
    else {
        if (k->y <= (y1 + y2) / 2) {
            if (root->c4->p == NULL) {  //if point value is NULL modify it's range and execute recursion
                root->c4->range1 = { (x1 + x2) / 2, y1 };
                root->c4->range2 = { x2, (y1 + y2) / 2 };
                pointSearch(root->c4, k);
            }
            else
                return (root->c4->p->x == k->x && root->c4->p->y == k->y);
        }
        else {
            if (root->c1->p == NULL) {  //if point value is NULL modify it's range and execute recursion
                root->c1->range1 = { (x1 + x2) / 2, (y1 + y2) / 2 };
                root->c1->range2 = { x2, y2 };
                pointSearch(root->c1, k);
            }
            else
                return (root->c1->p->x == k->x && root->c1->p->y == k->y);
        }
    }
}

/*
* Authors: Park Yongwoo, Park Yuwon, Yun Jaesang
* bool range_search(NODE* root, POINT* K, POINT start, POINT end)
*
* Summary of the del function:
*   check if point value is in range(start to end)
*
* Parameters    : get Tree(root) and get point k in root if k is in the range
*/
bool range_search(NODE* root, POINT* k, POINT start, POINT end) {
    float s_x1 = start.x;
    float e_x2 = end.x;
    float s_y1 = start.y;
    float e_y2 = end.y;
    float x1 = root->range1.x;
    float x2 = root->range2.x;
    float y1 = root->range1.y;
    float y2 = root->range2.y;
    if (k->x <= (x1 + x2) / 2) {
        if (k->y <= (y1 + y2) / 2) {
            if (root->c3->p == NULL) {  // if p is NULL, modify range
                root->c3->range1 = { x1, y1 };
                root->c3->range2 = { (x1 + x2) / 2, (y1 + y2) / 2 };
                range_search(root->c3, k, start, end);
            }
            else {
                // checking range 
                if (root->c3->p->x >= s_x1 && root->c3->p->x <= e_x2 
                    && root->c3->p->y >= s_y1 && root->c3->p->y <= e_y2) {
                    printf("(%f,%f) is in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);
                    return true;
                }
                else {
                    //printf("(%f,%f) is not in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);
                    return false;
                }
            }
        }
        else {
            if (root->c2->p == NULL) {  //if p is NULL, modify range
                root->c2->range1 = { x1, (y1 + y2) / 2 };
                root->c2->range2 = { (x1 + x2) / 2, y2 };
                range_search(root->c2, k, start, end);
            }
            else {
                // checking range 
                if (root->c2->p->x >= s_x1 && root->c2->p->x <= e_x2 
                    && root->c2->p->y >= s_y1 && root->c2->p->y <= e_y2) {
                    printf("(%f,%f) is in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);
                    return true;
                }
                else {
                    //printf("(%f,%f) is not in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);
                    return false;
                }
            }
        }
    }
    else {
        if (k->y <= (y1 + y2) / 2) {
            if (root->c4->p == NULL) {  //if p is NUL,L modify range
                root->c4->range1 = { (x1 + x2) / 2, y1 };
                root->c4->range2 = { x2, (y1 + y2) / 2 };
                range_search(root->c4, k, start, end);
            }
            else {
                // checking range
                if (root->c4->p->x >= s_x1 && root->c4->p->x <= e_x2 
                    && root->c4->p->y >= s_y1 && root->c4->p->y <= e_y2) {
                    printf("(%f,%f) is in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);
                    return true;
                }
                else {
                    //printf("(%f,%f) is not in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);
                    return false;
                }
            }
        }
        else {
            if (root->c1->p == NULL) {  //if p is NULL modify range
                root->c1->range1 = { (x1 + x2) / 2, (y1 + y2) / 2 };
                root->c1->range2 = { x2, y2 };
                range_search(root->c1, k, start, end);
            }
            else {
                // checking range 
                if (root->c1->p->x >= s_x1 && root->c1->p->x <= e_x2 
                    && root->c1->p->y >= s_y1 && root->c1->p->y <= e_y2) {
                    printf("(%f,%f) is in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);
                    return true;
                }
                else {
                    //printf("(%f,%f) is not in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);
                    return false;
                }
            }
        }
    }
}


/*
* Author: Park Yuwon
* void printp(POINT p)
*
* Summary of the del function:
*   print p, x-coordinate and point y-coordinate
*
* Parameters    : p has point x-coordinate and point y-coordinate
*/
void printp(POINT p) {
    printf("(%f, %f)", p.x, p.y);
}

// Authors: Park Yuwon, Park Yongwoo, Yun Jaesang, Kim Hyekang
int main() {
    // Set root node
    struct NODE* root = (struct NODE*)malloc(sizeof(struct NODE));
    root->range1 = { 0,0 };
    root->range2 = { 20, 20 };
    root->c1 = NULL;
    root->c2 = NULL;
    root->c3 = NULL;
    root->c4 = NULL;

    // Set points, range to insert or search and find their length
    int len_points;
    int len_point_search;
    int len_range_search;

    struct POINT points[] = { {7,7}, {8,2}, {11,6}, {2,13}, {14,6},
                      {3,1}, {9,11}, {19,4}, {16,12}, {17,7},
                      {12,18}, {18,17}, {6,16}, {1,9}, {4,19},
                      {13,14}, {12,3}, {2,2}, {4,3}, {1,4},
                      {19, 14}, {14, 11}, {18, 8}
    };
    len_points = sizeof(points) / sizeof(struct POINT);

    struct POINT point_search_points[] = { {7,7}, {8,4}, {17,7}, {3, 2}, { 13,18 }, { 8,2 } }; // point search samples
    len_point_search = sizeof(point_search_points) / sizeof(struct POINT);

    struct POINT range_search_rect[][2] = { {{6,6}, {15,15}},  // range search bounding rectangle 1
        {{3,1}, {12,18}}, // range search bounding rectangle 2
        {{1,4}, {16,12}}, // range search bounding rectangle 3...
        {{0,0}, {20,20}}
    };
    len_range_search = sizeof(range_search_rect) / sizeof(struct POINT[2]);


    printf("1. Build Quad Tree\n");
    for (int i = 0; i < len_points; i++) {
        insertTree(root, &points[i]);
    }
    printf("Build Tree Finished\n");

    printf("\n\n2. Point Search\n");
    for (int i = 0; i < len_point_search; i++) {
        if (pointSearch(root, &point_search_points[i])) {
            printf("Find ");
            printp(point_search_points[i]);
            printf("\n");
        }
        else {
            printf("Fail to find ");
            printp(point_search_points[i]);
            printf("\n");
        }
    }

    printf("\n\n3. Range Search\n");
    for (int i = 0; i < len_range_search; i++) {
        printf("Searching range: ");
        printp(range_search_rect[i][0]);
        printp(range_search_rect[i][1]);
        printf("\n");
        for (int j = 0; j < len_points; j++) {
            range_search(root, &points[j], range_search_rect[i][0], range_search_rect[i][1]);
        }
        printf("\n");
    }

    return 0;
}
