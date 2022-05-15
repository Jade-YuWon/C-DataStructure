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

NODE* getNewNode(float x, float y)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->p = (POINT*)malloc(sizeof(POINT));
    newNode->p->x = x;
    newNode->p->y = y;
    newNode->c1 = NULL;
    newNode->c2 = NULL;
    newNode->c3 = NULL;
    newNode->c4 = NULL;
    return newNode;
}


bool exit1(NODE* node)
{
    if (node->c1 == NULL)
        return true;
    else
        return false;
}


bool exit2(NODE* node)
{
    if (node->c2 == NULL)
        return true;
    else
        return false;
}

bool exit3(NODE* node)
{
    if (node->c3 == NULL)
        return true;
    else
        return false;
}

bool exit4(NODE* node)
{
    if (node->c4 == NULL)
        return true;
    else
        return false;
}


void insertTree(NODE* root, POINT* k)
{

    if (k->x <= (root->range2.x + root->range1.x) / 2)
    {
        if (k->y <= (root->range2.y + root->range1.y) / 2)
        {
            if (exit3(root) == true)
            {
                root->c3 = getNewNode(k->x, k->y);
            }
            else
            {
                if (root->c3->p != NULL) {
                    NODE* n = root->c3;
                    // root->c3->p = (POINT*)malloc(sizeof(POINT));
                   /*  root->c3->p->x = NULL;
                     root->c3->p->y = NULL;*/
                     /* root->c3->p->x = 0;
                      root->c3->p->y = 0;*/
                      //oot->c3 = (struct NODE*)malloc(sizeof(struct NODE));

                    root->c3->range1.x = root->range1.x;
                    root->c3->range1.y = root->range1.y;
                    root->c3->range2.x = (root->range1.x + root->range2.x) / 2;
                    root->c3->range2.y = (root->range1.y + root->range2.y) / 2;

                    // root->range2.x = (root->range1.x + root->range2.x)/2;

                    insertTree(root->c3, n->p);
                    root->c3->p = NULL;
                }
                insertTree(root->c3, k);
            }
        }

        else
        {

            if (exit2(root) == true)
                root->c2 = getNewNode(k->x, k->y);
            else
            {
                if (root->c2->p != NULL)
                {
                    NODE* n = root->c2;
                    // root->c2->p = (POINT*)malloc(sizeof(POINT));
                     /*
                     root->c2->p->x = NULL;
                     root->c2->p->y = NULL;*/
                     /*  root->c2->p->x = 0;
                       root->c2->p->y = 0;
                       root->c2 = (struct NODE*)malloc(sizeof(struct NODE));*/
                    root->c2->range1.x = root->range1.x;
                    root->c2->range1.y = (root->range1.y + root->range2.y) / 2;
                    root->c2->range2.x = (root->range1.x + root->range2.x) / 2;
                    root->c2->range2.y = root->range2.y;

                    insertTree(root->c2, n->p);
                    root->c2->p = NULL;
                }
                insertTree(root->c2, k);
            }
        }
    }

    else
    {
        if (k->y <= (root->range2.y + root->range1.y) / 2)
        {
            if (exit4(root) == true)
                root->c4 = getNewNode(k->x, k->y);
            else
            {
                if (root->c4->p != NULL)
                {

                    NODE* n = root->c4;
                    //root->c4->p = (POINT*)malloc(sizeof(POINT));
                /*    root->c4->p->x = NULL;
                    root->c4->p->y = NULL;*/
                    /*   root->c4->p->x = 0;
                       root->c4->p->y = 0;
                       root->c4 = (struct NODE*)malloc(sizeof(struct NODE));*/
                    root->c4->range1.x = (root->range1.x + root->range2.x) / 2;
                    root->c4->range1.y = root->range1.y;
                    root->c4->range2.x = root->range2.x;
                    root->c4->range2.y = (root->range1.y + root->range2.y) / 2;
                    insertTree(root->c4, n->p);
                    root->c4->p = NULL;
                }
                insertTree(root->c4, k);
            }
        }

        else
        {
            if (exit1(root) == true)
                root->c1 = getNewNode(k->x, k->y);
            else
            {
                if (root->c1->p != NULL)
                {

                    NODE* n = root->c1;
                    // root->c1->p = (POINT*)malloc(sizeof(POINT));
                  /*   root->c1->p->x = NULL;
                     root->c1->p->y = NULL;*/
                     /*      root->c1->p->x = 0;
                           root->c1->p->y = 0;*/
                           // root->c1 = (struct NODE*)malloc(sizeof(struct NODE));
                    root->c1->range1.x = (root->range1.x + root->range2.x) / 2;
                    root->c1->range1.y = (root->range1.y + root->range2.y) / 2;
                    root->c1->range2.x = root->range2.x;
                    root->c1->range2.y = root->range2.y;

                    insertTree(root->c1, n->p);
                    root->c1->p = NULL;
                }
                insertTree(root->c1, k);
            }
        }
    }

}


bool pointSearch(NODE* root, POINT* k)
{
    if (k->x <= (root->range2.x + root->range1.x) / 2)
    {
        if (k->y <= (root->range2.y + root->range1.y) / 2)
        {
            if (root->c3->p == NULL) {
                root->c3->range1.x = root->range1.x;
                root->c3->range1.y = root->range1.y;
                root->c3->range2.x = (root->range1.x + root->range2.x) / 2;
                root->c3->range2.y = (root->range1.y + root->range2.y) / 2;
                pointSearch(root->c3, k);
            }
            else {
                if (root->c3->p->x == k->x && root->c3->p->y == k->y)
                {
                    printf("find %f %f\n", k->x, k->y);
                    return true;
                }
                else
                {

                    //NODE* n = root->c3;


                    root->c3->range1.x = root->range1.x;
                    root->c3->range1.y = root->range1.y;
                    root->c3->range2.x = (root->range1.x + root->range2.x) / 2;
                    root->c3->range2.y = (root->range1.y + root->range2.y) / 2;

                    return false;

                    pointSearch(root->c3, k);
                    // root->c3->p = NULL;


                //pointSearch(root->c3, k);
                }
            }
        }

        else
        {
            if (root->c2->p == NULL) {
                root->c2->range1.x = root->range1.x;
                root->c2->range1.y = (root->range1.y + root->range2.y) / 2;
                root->c2->range2.x = (root->range1.x + root->range2.x) / 2;
                root->c2->range2.y = root->range2.y;
                pointSearch(root->c2, k);
            }
            else {
                if (root->c2->p->x == k->x && root->c2->p->y == k->y)
                {
                    printf("find %f %f\n", k->x, k->y);
                    return true;
                }
                else
                {

                    //NODE* n = root->c3;

                    root->c2->range1.x = root->range1.x;
                    root->c2->range1.y = (root->range1.y + root->range2.y) / 2;
                    root->c2->range2.x = (root->range1.x + root->range2.x) / 2;
                    root->c2->range2.y = root->range2.y;
                    return false;


                    pointSearch(root->c2, k);
                    // root->c3->p = NULL;


                //pointSearch(root->c3, k);
                }
            }
        }

    }

    else
    {
        if (k->y <= (root->range2.y + root->range1.y) / 2)
        {
            if (root->c4->p == NULL) {
                root->c4->range1.x = (root->range1.x + root->range2.x) / 2;
                root->c4->range1.y = root->range1.y;
                root->c4->range2.x = root->range2.x;
                root->c4->range2.y = (root->range1.y + root->range2.y) / 2;
                pointSearch(root->c4, k);
            }
            else {
                if (root->c4->p->x == k->x && root->c4->p->y == k->y)
                {
                    printf("find %f %f\n", k->x, k->y);
                    return true;
                }
                else
                {

                    //NODE* n = root->c3;


                    root->c4->range1.x = (root->range1.x + root->range2.x) / 2;
                    root->c4->range1.y = root->range1.y;
                    root->c4->range2.x = root->range2.x;
                    root->c4->range2.y = (root->range1.y + root->range2.y) / 2;
                    return false;


                    pointSearch(root->c4, k);
                    // root->c3->p = NULL;

                }
                //pointSearch(root->c3, k);
            }
        }


        else
        {
            if (root->c1->p == NULL) {
                root->c1->range1.x = (root->range1.x + root->range2.x) / 2;
                root->c1->range1.y = (root->range1.y + root->range2.y) / 2;
                root->c1->range2.x = root->range2.x;
                root->c1->range2.y = root->range2.y;
                pointSearch(root->c1, k);
            }
            else {
                if (root->c1->p->x == k->x && root->c1->p->y == k->y)
                {
                    printf("find %f %f\n", k->x, k->y);
                    return true;
                }
                else
                {

                    //NODE* n = root->c3;


                    root->c1->range1.x = (root->range1.x + root->range2.x) / 2;
                    root->c1->range1.y = (root->range1.y + root->range2.y) / 2;
                    root->c1->range2.x = root->range2.x;
                    root->c1->range2.y = root->range2.y;
                    printf("Fail\n");
                    return false;


                    pointSearch(root->c1, k);
                    // root->c3->p = NULL;

                }
                //pointSearch(root->c3, k);
            }
        }
    }
}

bool range_search(NODE* root, POINT* k, float x1, float x2, float y1, float y2)
{
    if (k->x <= (root->range2.x + root->range1.x) / 2)
    {
        if (k->y <= (root->range2.y + root->range1.y) / 2)
        {
            if (root->c3->p == NULL) {
                root->c3->range1.x = root->range1.x;
                root->c3->range1.y = root->range1.y;
                root->c3->range2.x = (root->range1.x + root->range2.x) / 2;
                root->c3->range2.y = (root->range1.y + root->range2.y) / 2;
                range_search(root->c3, k, x1, x2, y1, y2);
            }
            else {
                if (root->c3->p->x >= x1 && root->c3->p->x <= x2 && root->c3->p->y >= y1 && root->c3->p->y <= y2)
                {
                    printf("(%f,%f) is in (%f,%f) to (%f,%f) range\n", k->x, k->y, x1, y1, x2, y2);
                    return true;
                }
                else
                {

                    //NODE* n = root->c3;


                    root->c3->range1.x = root->range1.x;
                    root->c3->range1.y = root->range1.y;
                    root->c3->range2.x = (root->range1.x + root->range2.x) / 2;
                    root->c3->range2.y = (root->range1.y + root->range2.y) / 2;
                    printf("(%f,%f) is not in (%f,%f) to (%f,%f) range\n", k->x, k->y, x1, y1, x2, y2);

                    return false;

                    range_search(root->c3, k, x1, x2, y1, y2);
                    // root->c3->p = NULL;


                //pointSearch(root->c3, k);
                }
            }
        }

        else
        {
            if (root->c2->p == NULL) {
                root->c2->range1.x = root->range1.x;
                root->c2->range1.y = (root->range1.y + root->range2.y) / 2;
                root->c2->range2.x = (root->range1.x + root->range2.x) / 2;
                root->c2->range2.y = root->range2.y;
                range_search(root->c2, k, x1, x2, y1, y2);
            }
            else {
                if (root->c2->p->x >= x1 && root->c2->p->x <= x2 && root->c2->p->y >= y1 && root->c2->p->y <= y2)
                {
                    printf("(%f,%f) is in (%f,%f) to (%f,%f) range\n", k->x, k->y, x1, y1, x2, y2);
                    return true;
                }
                else
                {

                    //NODE* n = root->c3;

                    root->c2->range1.x = root->range1.x;
                    root->c2->range1.y = (root->range1.y + root->range2.y) / 2;
                    root->c2->range2.x = (root->range1.x + root->range2.x) / 2;
                    root->c2->range2.y = root->range2.y;
                    printf("(%f,%f) is not in (%f,%f) to (%f,%f) range\n", k->x, k->y, x1, y1, x2, y2);
                    return false;


                    range_search(root->c2, k, x1, x2, y1, y2);
                    // root->c3->p = NULL;


                //pointSearch(root->c3, k);
                }
            }
        }

    }

    else
    {
        if (k->y <= (root->range2.y + root->range1.y) / 2)
        {
            if (root->c4->p == NULL) {
                root->c4->range1.x = (root->range1.x + root->range2.x) / 2;
                root->c4->range1.y = root->range1.y;
                root->c4->range2.x = root->range2.x;
                root->c4->range2.y = (root->range1.y + root->range2.y) / 2;
                range_search(root->c4, k, x1, x2, y1, y2);
            }
            else {
                if (root->c4->p->x >= x1 && root->c4->p->x <= x2 && root->c4->p->y >= y1 && root->c4->p->y <= y2)
                {
                    printf("(%f,%f) is in (%f,%f) to (%f,%f) range\n", k->x, k->y, x1, y1, x2, y2);
                    return true;
                }
                else
                {

                    //NODE* n = root->c3;


                    root->c4->range1.x = (root->range1.x + root->range2.x) / 2;
                    root->c4->range1.y = root->range1.y;
                    root->c4->range2.x = root->range2.x;
                    root->c4->range2.y = (root->range1.y + root->range2.y) / 2;
                    printf("(%f,%f) is not in (%f,%f) to (%f,%f) range\n", k->x, k->y, x1, y1, x2, y2);

                    return false;


                    range_search(root->c4, k, x1, x2, y1, y2);
                    // root->c3->p = NULL;

                }
                //pointSearch(root->c3, k);
            }
        }


        else
        {
            if (root->c1->p == NULL) {
                root->c1->range1.x = (root->range1.x + root->range2.x) / 2;
                root->c1->range1.y = (root->range1.y + root->range2.y) / 2;
                root->c1->range2.x = root->range2.x;
                root->c1->range2.y = root->range2.y;
                range_search(root->c1, k, x1, x2, y1, y2);
            }
            else {
                if (root->c1->p->x >= x1 && root->c1->p->x <= x2 && root->c1->p->y >= y1 && root->c1->p->y <= y2)
                {
                    printf("(%f,%f) is in (%f,%f) to (%f,%f) range\n", k->x, k->y, x1, y1, x2, y2);
                    return true;
                }
                else
                {

                    //NODE* n = root->c3;


                    root->c1->range1.x = (root->range1.x + root->range2.x) / 2;
                    root->c1->range1.y = (root->range1.y + root->range2.y) / 2;
                    root->c1->range2.x = root->range2.x;
                    root->c1->range2.y = root->range2.y;
                    printf("(%f,%f) is not in (%f,%f) to (%f,%f) range\n", k->x, k->y, x1, y1, x2, y2);

                    return false;


                    range_search(root->c1, k, x1, x2, y1, y2);
                    // root->c3->p = NULL;

                }
                //pointSearch(root->c3, k);
            }
        }
    }
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
    root->c1 = NULL;
    root->c2 = NULL;
    root->c3 = NULL;
    root->c4 = NULL;

    for (int i = 0; i < 20; i++)
    {
        insertTree(root, &point_arr[i]);
        //  printf("%d success", i);
    }

    //for (int i = 0; i < 20; i++)
    //{
    //    pointSearch(root, &point_arr[i]);
    //}

    for (int i = 0; i < 20; i++)
    {
        range_search(root, &point_arr[i], 0, 20, 0, 20);
    }


    //root->range2.x = (root->range1.x + root->range2.x) / 2;
    //root->range2.y = (root->range1.y + root->range2.y) / 2;
    printf("test");
    return 0;
}
