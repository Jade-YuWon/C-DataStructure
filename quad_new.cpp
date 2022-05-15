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
    bool empty = true; // true: p and c1~c4 are NULL pointers
    bool sub; // true: need to be subdivided (=> pass emptiness(divisable?) check when insert)
};

NODE* getNewNode(POINT* k, float x1, float y1, float x2, float y2)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->range1 = { x1, y1 };
    newNode->range2 = { x2, y2 };
    newNode->p = (POINT*)malloc(sizeof(POINT));
    newNode->p = k; // empty = false;
    newNode->c1 = NULL;
    newNode->c2 = NULL;
    newNode->c3 = NULL;
    newNode->c4 = NULL;
    newNode->empty = false;
    newNode->sub = false;
    return newNode;
}


void insertTree(NODE* root, POINT* k)
{
    if (root->sub == false) {
        root = getNewNode(k, root->range1.x, root->range1.y, root->range2.x, root->range2.y);
        //return;
    }
    else {
        if (k->x <= (root->range2.x + root->range1.x) / 2)
        {
            if (k->y <= (root->range2.y + root->range1.y) / 2)
            {
                float c3x1 = root->range1.x;
                float c3y1 = root->range1.y;
                float c3x2 = (root->range1.x + root->range2.x) / 2;
                float c3y2 = (root->range1.y + root->range2.y) / 2;
                //if (exit3(root) == true)
                if (!root->c3)
                    root->c3 = getNewNode(k, c3x1, c3y1, c3x2, c3y2);
                else
                {
                    POINT* new_k = root->c3->p;
                    free(root->c3->p);
                    root->c3->empty = true;
                    root->c3->sub = true;
                    insertTree(root->c3, new_k);
                    insertTree(root->c3, k);
                }
            }

            else
            {
                float c2x1 = root->range1.x;
                float c2y1 = (root->range1.y + root->range2.y) / 2;
                float c2x2 = (root->range1.x + root->range2.x) / 2;
                float c2y2 = root->range2.y;
                if (!root->c2)
                    root->c2 = getNewNode(k, c2x1, c2y1, c2x2, c2y2);
                else
                {
                    POINT* new_k = root->c2->p;
                    free(root->c2->p);
                    root->c2->empty = true;
                    root->c2->sub = true;
                    insertTree(root->c2, new_k);
                    insertTree(root->c2, k);
                }
            }
        }

        else
        {
            if (k->y <= (root->range2.y + root->range1.y) / 2)
            {
                float c4x1 = (root->range1.x + root->range2.x) / 2;
                float c4y1 = root->range1.y;
                float c4x2 = root->range2.x;
                float c4y2 = (root->range1.y + root->range2.y) / 2;
                if (!root->c4)
                    root->c4 = getNewNode(k, c4x1, c4y1, c4x2, c4y2);
                else
                {
                    POINT* new_k = root->c4->p;
                    free(root->c4->p);
                    root->c4->empty = true;
                    root->c4->sub = true;
                    insertTree(root->c4, new_k);
                    insertTree(root->c4, k);
                }
            }

            else
            {
                float c1x1 = (root->range1.x + root->range2.x) / 2;
                float c1y1 = (root->range1.y + root->range2.y) / 2;
                float c1x2 = root->range2.x;
                float c1y2 = root->range2.y;
                if (!root->c1)
                    root->c1 = getNewNode(k, c1x1, c1y1, c1x2, c1y2);
                else
                {
                    POINT* new_k = root->c1->p;
                    free(root->c1->p);
                    root->c1->empty = true;
                    root->c1->sub = true;
                    insertTree(root->c1, new_k);
                    insertTree(root->c1, k);
                }
            }
        }
    }
}
void printTree(struct NODE* root) {
        if (!root->p)
            printf("%f, %f\n", root->p->x, root->p->y);
        else {
            printTree(root->c1);
            printTree(root->c2);
            printTree(root->c3);
            printTree(root->c4);
        }
    //printf("%d\n", root->empty);
    //printf("%d\n", root->sub);
}

int main() {
    struct POINT point_arr[20] = { {7,7}, {8,2}, {11,6}, {2,13}, {14,6},
                      {3,1}, {9,11}, {19,4}, {16,12}, {17,7},
                      {12,18}, {18,17}, {6,16}, {1,9}, {4,19},
                      {13,14}, {12,3}, {2,2}, {4,3}, {1,4}
    };
    struct NODE* root = (struct NODE*)malloc(sizeof(struct NODE));



    root->range1 = { 0,0 };
    root->range2 = { 20, 20 };
    root->p = NULL;
    root->c1 = NULL;
    root->c2 = NULL;
    root->c3 = NULL;
    root->c4 = NULL;
    root->empty = true;
    root->sub = false;

    for (int i = 0; i < 20; i++)
    {
        insertTree(root, &point_arr[i]);
    }
    printTree(root);


    return 0;
}
