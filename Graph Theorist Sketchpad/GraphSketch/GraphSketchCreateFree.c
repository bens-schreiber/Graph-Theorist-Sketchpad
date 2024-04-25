//
//  GraphSketch.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/24/24.
//

#include "GraphSketch.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

DrawableVertex DrawableVertex_CreateDrawableVertex(const char* label, Color color, VertexIndex vi)
{
    DrawableVertex dv = {};
    strcpy(dv.Label, label);
    dv.Color = color;
    dv.VertexIndex = vi;
    return dv;
}

DrawableEdge DrawableEdge_CreateDrawableEdge(VertexIndex v1, VertexIndex v2)
{
    return (DrawableEdge) { v1, v2};
}

GraphSketch *GraphSketch_CreateGraphSketch(void)
{
    GraphSketch *gs = malloc(sizeof(GraphSketch));
    gs->BvhTree = NULL;
    gs->Graph = Graph_CreateGraph();
    gs->DrawableEdgeListSize = 0;
    return gs;
}

void GraphSketch_FreeGraphSketch(GraphSketch *gs)
{
    assert(gs != NULL);
    
    if (gs->BvhTree != NULL)
    {
        BvhTree_FreeBvhTree(gs->BvhTree);
    }
    Graph_FreeGraph(gs->Graph);
    free(gs);
}
