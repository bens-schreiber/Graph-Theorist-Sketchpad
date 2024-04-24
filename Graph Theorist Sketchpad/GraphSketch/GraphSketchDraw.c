//
//  Draw.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/24/24.
//

#include "GraphSketch.h"
#include <assert.h>

void DrawableVertex_Draw(DrawableVertex *dv, Primitive *p)
{
    assert(dv != NULL);
    assert(p != NULL);
    DrawCircleV(p->Centroid, GRAPH_VERTEX_RADIUS, RED);
}

void GraphSketch_DrawVertices(GraphSketch *gs)
{
    assert(gs != NULL);
    
    for (VertexIndex vi = 0; vi < gs->Graph->Vertices; vi++)
    {
        DrawableVertex_Draw(&gs->IndexToDrawableVertexMap[vi], &gs->IndexToPrimitiveMap[vi]);
    }
}

void GraphSketch_DrawAdjMatrix(GraphSketch *gs, StringBuffer buffer, bool update)
{
    assert(gs != NULL);
    
    if (update)
    {
        Graph_DumpString(gs->Graph, buffer);
    }
    
    DrawText(buffer, 10, 10, 20, BLACK);
}