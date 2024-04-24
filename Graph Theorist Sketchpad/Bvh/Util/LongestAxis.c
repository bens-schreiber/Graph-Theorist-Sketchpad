//
//  LongestAxis.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/23/24.
//

#include "LongestAxis.h"
#include "raylib.h"
#include "../Primitive/Primitive.h"

int LongestAxis_CompareX(const void *a, const void *b)
{
    const Primitive *primitiveA = (const Primitive *)a;
    const Primitive *primitiveB = (const Primitive *)b;

    return primitiveA->Centroid.x - primitiveB->Centroid.x;
}

int LongestAxis_CompareY(const void *a, const void *b)
{
    const Primitive *primitiveA = (const Primitive *)a;
    const Primitive *primitiveB = (const Primitive *)b;

    return primitiveA->Centroid.y - primitiveB->Centroid.y;
}

QSortCompare LongestAxis_CompareByLongestAxis(Rectangle boundingBox)
{
    Vector2 boundingBoxMin = {boundingBox.x, boundingBox.y};
    Vector2 boundingBoxMax = {boundingBox.x + boundingBox.width, boundingBox.y +boundingBox.height };
    float xDistance = boundingBoxMax.x - boundingBoxMin.x;
    float yDistance = boundingBoxMax.y - boundingBoxMin.y;

    if (xDistance > yDistance)
    {
        return LongestAxis_CompareX;
    }
    
    return LongestAxis_CompareY;
}
