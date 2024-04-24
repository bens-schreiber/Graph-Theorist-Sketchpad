//
//  GraphVertex.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/23/24.
//

#include <stdlib.h>
#include <string.h>
#include "GraphVertex.h"

GraphVertex GraphVertex_CreateGraphVertex(u_short index, const char* label, Color color)
{
    GraphVertex gv = {};
    strcpy(gv.Label, label);
    gv.Index = index;
    gv.Color = color;
    return gv;
}

void GraphVertex_Draw(GraphVertex *gv, Primitive *p)
{
    DrawCircleV(p->Centroid, GRAPH_VERTEX_RADIUS, RED);
}
