#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define QT_NODE_CAPACITY (4)
#define MAX_ARRAY_SIZE (1024)

typedef struct Point {
    float x;
    float y;
} Point;

typedef struct AABB {
    Point* center;
    float halfDimension;
} AABB;

typedef struct QuadTree {
    AABB* boundry;
    Point** points;

    struct QuadTree* NW;
    struct QuadTree* NE;
    struct QuadTree* SW;
    struct QuadTree* SE;

} QuadTree;


Point* Point_new(float x, float y) {
    Point* p = (Point*)malloc(sizeof(Point));
    p->x = x;
    p->y = y;
    return p;
}

Point* Point_origin() {
    Point* p = (Point*)malloc(sizeof(Point));
    p->x = 0.;
    p->y = 0.;
    return p;
}

void Point_print(Point* point) {
    printf("(%2.2f, %2.2f)\n", point->x, point->y);
}

AABB* AABB_new(Point* center, float halfDimension) {
    AABB* aabb = (AABB*)malloc(sizeof(AABB));
    aabb->center = center;
    aabb->halfDimension = halfDimension;
    return aabb;
}

bool AABB_cotains_point(AABB* boundry, Point* point) {
    if (point->x < boundry->center->x - boundry->halfDimension || point->x > boundry->center->x + boundry->halfDimension) {
        return false;
    }

    if (point->y < boundry->center->y - boundry->halfDimension || point->y > boundry->center->y + boundry->halfDimension) {
        return false;
    }

    return true;
}

bool AABB_intersects_AABB(AABB* self, AABB* other) {
    if (self->center->x + self->halfDimension > other->center->x - other->halfDimension) {
        return true;
    }

    if (self->center->x - self->halfDimension < other->center->x + other->halfDimension) {
        return true;
    }

    if (self->center->y + self->halfDimension > other->center->y - other->halfDimension) {
        return true;
    }

    if (self->center->y - self->halfDimension < other->center->y + other->halfDimension) {
        return true;
    }

    return false;
}

void AABB_print(AABB* aabb) {
    printf("\n");
    printf("(%5.2f, %5.2f)-------------------------(%5.2f, %5.2f)\n", aabb->center->x - aabb->halfDimension, aabb->center->y + aabb->halfDimension, aabb->center->x + aabb->halfDimension, aabb->center->y + aabb->halfDimension);
    printf("|                                                   |\n");
    printf("|                                                   |\n");
    printf("|                                                   |\n");
    printf("|                                                   |\n");
    printf("|                                                   |\n");
    printf("|                                                   |\n");
    printf("|                                                   |\n");
    printf("|                                                   |\n");
    printf("(%5.2f, %5.2f)--------------------------(%5.2f, %5.2f)\n", aabb->center->x - aabb->halfDimension, aabb->center->y - aabb->halfDimension, aabb->center->x + aabb->halfDimension, aabb->center->y - aabb->halfDimension);
    printf("\n");
}

QuadTree* QuadTree_new(AABB* boundry) {
    QuadTree* qt = (QuadTree*)malloc(sizeof(QuadTree));
    qt->NE = NULL;
    qt->NW = NULL;
    qt->SE = NULL;
    qt->SW = NULL;

    qt->boundry = boundry;

    qt->points = (Point**)malloc(sizeof(Point*) * QT_NODE_CAPACITY);

    for (size_t i = 0; i < QT_NODE_CAPACITY; i++)
    {
        qt->points[i] = NULL;
    }

    return qt;
}

size_t QuadTree_points_size(Point* points[]) {
    size_t i;
    for (i = 0; i < QT_NODE_CAPACITY; i++)
    {
        if (points[i] == NULL) {
            return i;
        }
    }

    return i;
}

QuadTree* QuadTree_subdivide(QuadTree* root) {
    float halfDim = root->boundry->halfDimension / 2;
    // North West
    Point* nw_p = Point_new(root->boundry->center->x - halfDim, root->boundry->center->y + halfDim);
    root->NW = QuadTree_new(AABB_new(nw_p, halfDim));

    // North East
    Point* ne_p = Point_new(root->boundry->center->x + halfDim, root->boundry->center->y + halfDim);
    root->NE = QuadTree_new(AABB_new(ne_p, halfDim));

    // South West
    Point* sw_p = Point_new(root->boundry->center->x - halfDim, root->boundry->center->y - halfDim);
    root->SW = QuadTree_new(AABB_new(sw_p, halfDim));

    // South East
    Point* se_p = Point_new(root->boundry->center->x + halfDim, root->boundry->center->y - halfDim);
    root->SE = QuadTree_new(AABB_new(se_p, halfDim));

    return root;
}


bool QuadTree_insert(QuadTree* root, Point* point) {
    if (!AABB_cotains_point(root->boundry, point)) {
        return false;
    }

    size_t points_size = QuadTree_points_size(root->points);

    if (points_size < QT_NODE_CAPACITY && root->NW == NULL) {
        root->points[points_size] = point;
        return true;
    }

    if (root->NW == NULL) {
        QuadTree_subdivide(root);
    }

    if (QuadTree_insert(root->NW, point)) return true;
    if (QuadTree_insert(root->NE, point)) return true;
    if (QuadTree_insert(root->SW, point)) return true;
    if (QuadTree_insert(root->SE, point)) return true;

    return false;
}

Point** QuadTree_query_range(QuadTree* root, AABB* range) {
    Point** result;
    result = (Point**)malloc(sizeof(Point*) * MAX_ARRAY_SIZE);

    size_t index = 0;
    for (size_t i = 0; i < MAX_ARRAY_SIZE; i++) {
        result[i] = NULL;
    }

    if (!AABB_intersects_AABB(root->boundry, range)) {
        return result;
    }

    size_t points_size = QuadTree_points_size(root->points);
    for (size_t i = 0; i < points_size; i++)
    {
        if (AABB_cotains_point(range, root->points[i])) {
            result[index++] = root->points[i];
        }
    }

    if (root->NW == NULL) {
        return result;
    }

    size_t i;

    i = 0;
    Point** nw_r = QuadTree_query_range(root->NW, range);
    while (nw_r[i] != NULL && i < MAX_ARRAY_SIZE) {
        result[index++] = nw_r[i];
        i++;
    }

    i = 0;
    Point** ne_r = QuadTree_query_range(root->NE, range);
    while (ne_r[i] != NULL && i < MAX_ARRAY_SIZE) {
        result[index++] = ne_r[i];
        i++;
    }

    i = 0;
    Point** sw_r = QuadTree_query_range(root->SW, range);
    while (sw_r[i] != NULL && i < MAX_ARRAY_SIZE) {
        result[index++] = sw_r[i];
        i++;
    }

    i = 0;
    Point** se_r = QuadTree_query_range(root->SE, range);
    while (se_r[i] != NULL && i < MAX_ARRAY_SIZE) {
        result[index++] = se_r[i];
        i++;
    }

    return result;
}




int main(int argc, char const* argv[])
{
    printf("\033[1m\033[37mQuad Tree\033[0m\n\n");

    printf("Specify Inital Axis Aligned Bounding Box \n");
    printf("Center: \n");
    float x = 10, y = 10;
    printf("X: 10\n");
    printf("Y: 10\n");

    float hd;
    printf("Half Dimension: 10\n\n");
    hd = 10;

    Point* center = Point_new(x, y);
    AABB* boundry = AABB_new(center, hd);
    printf("Quad Tree Boundry\n");
    AABB_print(boundry);

    QuadTree* qt = QuadTree_new(boundry);

    int count = 20;
    printf("Insert 20 nodes\n\n");
    int i = 0;
    Point point_arr[20] = { {7,7}, {8,2}, {11,6}, {2,13}, {14,6}, 
                            {3,1}, {9,11}, {19,4}, {16,12}, {17,7}, 
                            {12,18}, {18,17}, {6,16}, {1,9}, {4,19}, 
                            {13,14}, {12,3}, {2,2}, {4,3}, {1,4}
                          };
    while (count-- > 0) {
        printf("X: %f\t", point_arr[i].x);
        printf("Y: %f\t", point_arr[i].y);
        Point* p = Point_new(point_arr[i].x, point_arr[i].y);
        i++;

        printf("\nPoint: ");
        Point_print(p);

        if (!QuadTree_insert(qt, p)) {
            printf("Point Outside boundry. Not Inserted\n\n");
        }
        else {
            printf("Point inserted successfully\n\n");
        }
    }


    printf("Specify Axis Aligned Bounding Box for Range Query\n");
    printf("Center: \n");
    float x_r, y_r;
    printf("X: ");
    scanf("%e", &x_r);
    printf("Y: ");
    scanf("%e", &y_r);

    float hd_r;
    printf("Half Dimension: ");
    scanf("%e", &hd_r);

    Point* center_r = Point_new(x_r, y_r);
    AABB* boundry_r = AABB_new(center_r, hd_r);
    printf("Range Search Boundry\n");
    AABB_print(boundry_r);
    Point** res = QuadTree_query_range(qt, boundry_r);
    printf("Result\n");
    size_t j = 0;
    while (res[j] != NULL && j < MAX_ARRAY_SIZE) {
        Point_print(res[j]);
        j++;
    }
    return 0;
}
