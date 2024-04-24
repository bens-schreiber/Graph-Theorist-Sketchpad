//
//  Primitive.h
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/23/24.
//

#ifndef Primitive_h
#define Primitive_h

#include "raylib.h"
#include "raymath.h"

#define BOUNDING_BOX_SIZE 20.0

typedef struct
{
    Rectangle BoundingBox;
    Vector2 Centroid;
} Primitive;

/// Creates a new primitive at a given position with a bounding box enclosing it
static inline Primitive Primitive_CreatePrimitive(Vector2 position)
{
    Vector2 corner = Vector2SubtractValue(position, BOUNDING_BOX_SIZE / 2);
    Rectangle boundingBox =
    {
        .x = corner.x,
        .y = corner.y,
        .width = BOUNDING_BOX_SIZE,
        .height = BOUNDING_BOX_SIZE
    };
    
    return (Primitive) {boundingBox, position};
}


static inline void Primitive_Draw(const Primitive *p)
{
    DrawRectangleRec(p->BoundingBox, RED);
}


#endif /* Primitive_h */
