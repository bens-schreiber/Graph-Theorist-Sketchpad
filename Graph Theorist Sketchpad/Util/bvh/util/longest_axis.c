#include "raylib.h"
#include "longest_axis.h"
#include "../../primitive/primitive.h"

int compareX(const void *a, const void *b)
{
    Primitive *primitive_a = (Primitive *)a;
    Primitive *primitive_b = (Primitive *)b;

    return primitive_a->centroid.x - primitive_b->centroid.x;
}

int compareY(const void *a, const void *b)
{
    Primitive *primitive_a = (Primitive *)a;
    Primitive *primitive_b = (Primitive *)b;

    return primitive_a->centroid.y - primitive_b->centroid.y;
}

int compareZ(const void *a, const void *b)
{
    Primitive *primitive_a = (Primitive *)a;
    Primitive *primitive_b = (Primitive *)b;

    return primitive_a->centroid.z - primitive_b->centroid.z;
}

qsort_compare compare_by_longest_axis(BoundingBox scene_aabb)
{
    float x_distance = scene_aabb.max.x - scene_aabb.min.x;
    float y_distance = scene_aabb.max.y - scene_aabb.min.y;
    float z_distance = scene_aabb.max.z - scene_aabb.min.z;

    if (x_distance > y_distance && x_distance > z_distance)
    {
        return compareX;
    }
    if (y_distance > x_distance && y_distance > z_distance)
    {
        return compareY;
    }
    return compareZ;
}