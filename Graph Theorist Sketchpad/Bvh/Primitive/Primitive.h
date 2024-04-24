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

#define BOUNDING_BOX_SIZE 25.0

typedef struct
{
    /// Box that contains the entire geometry
    Rectangle BoundingBox;
    
    /// Center most point of the geometry
    Vector2 Centroid;
} Primitive;

/// Creates a new primitive with a given bounding box size, centered at a position.
static inline Primitive Primitive_CreatePrimitiveWithSize(Vector2 position, float boundingBoxSize)
{
    Vector2 corner = Vector2SubtractValue(position, boundingBoxSize / 2);
    Rectangle boundingBox =
    {
        .x = corner.x,
        .y = corner.y,
        .width = BOUNDING_BOX_SIZE,
        .height = BOUNDING_BOX_SIZE
    };
    
    return (Primitive) {boundingBox, position};
}

/// Creates a new primitive centered at a given position with a bounding box enclosing it
static inline Primitive Primitive_CreatePrimitive(Vector2 position)
{
    return Primitive_CreatePrimitiveWithSize(position, BOUNDING_BOX_SIZE);
}

static inline void Primitive_Draw(const Primitive *p)
{
    DrawRectangleRec(p->BoundingBox, RED);
}

#endif /* Primitive_h */
