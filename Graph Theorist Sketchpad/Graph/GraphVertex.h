//
//  GraphVertex.h
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/23/24.
//

#ifndef GraphVertex_h
#define GraphVertex_h

#include "raylib.h"
#include <sys/types.h>
#include "../Bvh/Primitive/Primitive.h"

#define GRAPH_VERTEX_RADIUS 15

typedef char StringBuffer[100];

typedef struct
{
    u_short Index;
    StringBuffer Label;
    Color Color;
} GraphVertex;

GraphVertex GraphVertex_CreateGraphVertex(u_short index, const char* label, Color color);

void GraphVertex_Draw(GraphVertex *gv, Primitive *p);
#endif /* GraphVertex_h */
