//
//  Primitive.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/24/24.
//

#include "Primitive.h"
#include "raymath.h"

Primitive Primitive_CreatePrimitiveWithSize(Vector2 position, float boundingBoxSize)
{
    float sub = boundingBoxSize / 2;
    Vector2 corner = { position.x - sub, position.y - sub };
    Rectangle boundingBox =
    {
        .x = corner.x,
        .y = corner.y,
        .width = BOUNDING_BOX_SIZE,
        .height = BOUNDING_BOX_SIZE
    };
    
    return (Primitive) {boundingBox, position};
}

Primitive Primitive_CreatePrimitive(Vector2 position)
{
    return Primitive_CreatePrimitiveWithSize(position, BOUNDING_BOX_SIZE);
}

void Primitive_Draw(const Primitive *p)
{
    DrawRectangleRec(p->BoundingBox, RED);
}
