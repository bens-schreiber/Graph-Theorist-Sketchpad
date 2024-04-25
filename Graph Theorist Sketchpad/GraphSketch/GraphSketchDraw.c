//
//  Draw.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/24/24.
//

#include "GraphSketch.h"
#include <assert.h>
#include <stdio.h>

void DrawableVertex_Draw(const DrawableVertex *dv, const Primitive *p)
{
    assert(dv != NULL);
    assert(p != NULL);
    DrawCircleV(p->Centroid, GRAPH_VERTEX_RADIUS, RED);
    // TODO: bug drawing text, numbers shift randomly
    DrawText(dv->Label, p->Centroid.x, p->Centroid.y + GRAPH_VERTEX_RADIUS + 10, 10, BLACK);
}

void DrawableEdge_Draw(const GraphSketch *gs, DrawableEdge de)
{
    DrawLineV(gs->IndexToPrimitiveMap[de.V1].Centroid, gs->IndexToPrimitiveMap[de.V2].Centroid, BLACK);
}

void GraphSketch_DrawVertices(const GraphSketch *gs)
{
    assert(gs != NULL);
    
    for (VertexIndex vi = 0; vi < gs->Graph->Vertices; vi++)
    {
        DrawableVertex_Draw(&gs->IndexToDrawableVertexMap[vi], &gs->IndexToPrimitiveMap[vi]);
    }
}

void GraphSketch_DrawAdjMatrix(const GraphSketch *gs, StringBuffer buffer, bool update)
{
    assert(gs != NULL);
    
    if (update)
    {
        Graph_DumpString(gs->Graph, buffer);
    }
    
    DrawText(buffer, 10, 10, 20, BLACK);
}

void GraphSketch_DrawEdges(const GraphSketch *gs)
{
    assert(gs != NULL);
    
    for (int i = 0; i < gs->DrawableEdgeListSize; i++)
    {
        DrawableEdge_Draw(gs, gs->DrawableEdgeList[i]);
    }
}
