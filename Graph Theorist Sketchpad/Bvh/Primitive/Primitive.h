//
//  Primitive.h
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/23/24.
//

#ifndef Primitive_h
#define Primitive_h

#include "raylib.h"

#define BOUNDING_BOX_SIZE 27.0

typedef unsigned int VertexIndex;

typedef struct
{
    /// Box that contains the entire geometry
    Rectangle BoundingBox;
    
    /// Center most point of the geometry
    Vector2 Centroid;
    VertexIndex VertexIndex;
} Primitive;

/// Creates a new primitive with a given bounding box size, centered at a position.
Primitive Primitive_CreatePrimitiveWithSize(Vector2 position, VertexIndex vi, float boundingBoxSize);

/// Creates a new primitive centered at a given position with a bounding box enclosing it
Primitive Primitive_CreatePrimitive(Vector2 position, VertexIndex vi);

void Primitive_Draw(const Primitive *p);

#endif /* Primitive_h */
