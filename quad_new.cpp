#include <stdio.h>
#include <stdlib.h>

struct POINT {
    float x;
    float y;
};
struct NODE {
    struct POINT range1; //Bounding Rectangle
    struct POINT range2; //Bounding Rectangle
    struct POINT* p;
    struct NODE* c1; //NE
    struct NODE* c2; //NW
    struct NODE* c3; //SW
    struct NODE* c4; //SE
};

NODE* getNewNode(POINT *k) {
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->p = (POINT*)malloc(sizeof(POINT));
    newNode->p = k;
    newNode->c1 = NULL;
    newNode->c2 = NULL;
    newNode->c3 = NULL;
    newNode->c4 = NULL;
    return newNode;
}

void insertTree(NODE* root, POINT* k) {
    float x1 = root->range1.x;
    float x2 = root->range2.x;
    float y1 = root->range1.y;
    float y2 = root->range2.y;

    if (k->x <= (x1 + x2) / 2) {
        if (k->y <= (y1 + y2) / 2) {
            if (root->c3 == NULL)
                root->c3 = getNewNode(k);
            else {
                if (root->c3->p != NULL) {
                    NODE* n = root->c3;
                    root->c3->range1 = { x1, y1 };
                    root->c3->range2 = { (x1 + x2) / 2, (y1 + y2) / 2 };

                    insertTree(root->c3, n->p);
                    root->c3->p = NULL;
                }
                insertTree(root->c3, k);
            }
        }
        else {
            if (root->c2 == NULL)
                root->c2 = getNewNode(k);
            else {
                if (root->c2->p != NULL) {
                    NODE* n = root->c2;
                    root->c2->range1 = { x1, (y1 + y2) / 2 };
                    root->c2->range2 = { (x1 + x2) / 2, y2 };

                    insertTree(root->c2, n->p);
                    root->c2->p = NULL;
                }
                insertTree(root->c2, k);
            }
        }
    }
    else {
        if (k->y <= (y1 + y2) / 2) {
            if (root->c4 == NULL)
                root->c4 = getNewNode(k);
            else {
                if (root->c4->p != NULL) {
                    NODE* n = root->c4;
                    root->c4->range1 = { (x1 + x2) / 2, y1 };
                    root->c4->range2 = { x2, (y1 + y2) / 2 };

                    insertTree(root->c4, n->p);
                    root->c4->p = NULL;
                }
                insertTree(root->c4, k);
            }
        }
        else {
            if (root->c1 == NULL)
                root->c1 = getNewNode(k);
            else {
                if (root->c1->p != NULL) {
                    NODE* n = root->c1;
                    root->c1->range1 = { (x1 + x2) / 2, (y1 + y2) / 2 };
                    root->c1->range2 = { x2, y2 };

                    insertTree(root->c1, n->p);
                    root->c1->p = NULL;
                }
                insertTree(root->c1, k);
            }
        }
    }
}

bool pointSearch(NODE* root, POINT* k) {
    float x1 = root->range1.x;
    float x2 = root->range2.x;
    float y1 = root->range1.y;
    float y2 = root->range2.y;
    if (k->x <= (x1 + x2) / 2) {
        if (k->y <= (y1 + y2) / 2) {
            if (root->c3->p == NULL) {
                root->c3->range1 = { x1, y1 };
                root->c3->range2 = { (x1 + x2) / 2, (y1 + y2) / 2 };
                pointSearch(root->c3, k);
            }
            else
                return (root->c3->p->x == k->x && root->c3->p->y == k->y);
        }
        else {
            if (root->c2->p == NULL) {
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
            if (root->c4->p == NULL) {
                root->c4->range1 = { (x1 + x2) / 2, y1 };
                root->c4->range2 = { x2, (y1 + y2) / 2 };
                pointSearch(root->c4, k);
            }
            else
                return (root->c4->p->x == k->x && root->c4->p->y == k->y);
        }
        else {
            if (root->c1->p == NULL) {
                root->c1->range1 = { (x1 + x2) / 2, (y1 + y2) / 2 };
                root->c1->range2 = { x2, y2 };
                pointSearch(root->c1, k);
            }
            else
                return (root->c1->p->x == k->x && root->c1->p->y == k->y);
        }
    }
}
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
            if (root->c3->p == NULL) {
                root->c3->range1 = { x1, y1 };
                root->c3->range2 = { (x1 + x2) / 2, (y1 + y2) / 2 };
                range_search(root->c3, k, start, end);
            }
            else {
                if (root->c3->p->x >= s_x1 && root->c3->p->x <= e_x2 && root->c3->p->y >= s_y1 && root->c3->p->y <= e_y2)
                {
                    printf("(%f,%f) is in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);
                    return true;
                }
                else
                {
                    //printf("(%f,%f) is not in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);

                    return false;
                }
            }
        }

        else
        {
            if (root->c2->p == NULL) {
                root->c2->range1 = { x1, (y1 + y2) / 2 };
                root->c2->range2 = { (x1 + x2) / 2, y2 };
                range_search(root->c2, k, start, end);
            }
            else {
                if (root->c2->p->x >= s_x1 && root->c2->p->x <= e_x2 && root->c2->p->y >= s_y1 && root->c2->p->y <= e_y2)
                {
                    printf("(%f,%f) is in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);
                    return true;
                }
                else
                {
                    //printf("(%f,%f) is not in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);
                    return false;
                }
            }
        }

    }

    else
    {
        if (k->y <= (y1 + y2) / 2)
        {
            if (root->c4->p == NULL) {
                root->c4->range1 = { (x1 + x2) / 2, y1 };
                root->c4->range2 = { x2, (y1 + y2) / 2 };
                range_search(root->c4, k, start, end);
            }
            else {
                if (root->c4->p->x >= s_x1 && root->c4->p->x <= e_x2 && root->c4->p->y >= s_y1 && root->c4->p->y <= e_y2)
                {
                    printf("(%f,%f) is in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);
                    return true;
                }
                else
                {
                    //printf("(%f,%f) is not in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);

                    return false;
                }
            }
        }


        else
        {
            if (root->c1->p == NULL) {
                root->c1->range1 = { (x1 + x2) / 2, (y1 + y2) / 2 };
                root->c1->range2 = { x2, y2 };
                range_search(root->c1, k, start, end);
            }
            else {
                if (root->c1->p->x >= s_x1 && root->c1->p->x <= e_x2 && root->c1->p->y >= s_y1 && root->c1->p->y <= e_y2)
                {
                    printf("(%f,%f) is in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);
                    return true;
                }
                else
                {
                    //printf("(%f,%f) is not in (%f,%f) to (%f,%f) range\n", k->x, k->y, s_x1, s_y1, e_x2, e_y2);

                    return false;
                }
            }
        }
    }
}




void printp(POINT p) {
    printf("(%f, %f)", p.x, p.y);
}

int main() {

    int len_points;
    int len_point_search;
    int len_range_search;

    struct NODE* root = (struct NODE*)malloc(sizeof(struct NODE));

    root->range1 = { 0,0 };
    root->range2 = { 20, 20 };
    root->c1 = NULL;
    root->c2 = NULL;
    root->c3 = NULL;
    root->c4 = NULL;

    struct POINT point_arr[] = { {7,7}, {8,2}, {11,6}, {2,13}, {14,6},
                      {3,1}, {9,11}, {19,4}, {16,12}, {17,7},
                      {12,18}, {18,17}, {6,16}, {1,9}, {4,19},
                      {13,14}, {12,3}, {2,2}, {4,3}, {1,4}
    };
    len_points = sizeof(point_arr) / sizeof(struct POINT);

    struct POINT point_search_point[] = { {7,7}, {8,4}, {3,2}, {13,18} };
    len_point_search = sizeof(point_search_point) / sizeof(struct POINT);

    struct POINT point_range_point[][2] = { {{7,7}, {8,4}}, {{3,2}, {13,18}}, {{0,0}, {20,20}} };
    len_range_search = sizeof(point_range_point) / sizeof(struct POINT[2]);

    for (int i = 0; i < len_points; i++) {
        insertTree(root, &point_arr[i]);
    }

    for (int i = 0; i < len_point_search; i++) {
        if (pointSearch(root, &point_search_point[i])) {
            printf("Find ");
            printp(point_search_point[i]);
            printf("\n");
        }
        else {
            printf("Fail to find ");
            printp(point_search_point[i]);
            printf("\n");
        }
    }

    for (int i = 0; i < len_range_search; i++) {
        printf("Searching range: ");
        printp(point_range_point[i][0]);
        printp(point_range_point[i][1]);
        printf("\n");
        for (int j = 0; j < len_points; j++) {
            if (range_search(root, &point_arr[j], point_range_point[i][0], point_range_point[i][1])) {
                //printf("(%f,%f) is in (%f,%f) to (%f,%f) range\n", k->x, k->y, x1, y1, x2, y2);
            }
        }
        printf("\n");
    }

    return 0;
}
