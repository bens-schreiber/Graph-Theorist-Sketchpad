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

GraphSketch *GraphSketch_CreateGraphSketch(void)
{
    GraphSketch *gs = malloc(sizeof(GraphSketch));
    gs->BvhTree = NULL;
    gs->Graph = Graph_CreateGraph();
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
