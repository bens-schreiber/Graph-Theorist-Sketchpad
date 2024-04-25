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

DrawableEdge DrawableEdge_CreateDrawableEdge(Label label, VertexIndex v1, VertexIndex v2, EdgeIndex e, int curvature)
{
    DrawableEdge de = {};
    strcpy(de.Label, label);
    de.V1 = v1;
    de.V2 = v2;
    de.E = 1;
    de.Curvature = curvature;
    return de;
}

GraphSketch *GraphSketch_CreateGraphSketch(void)
{
    GraphSketch *gs = malloc(sizeof(GraphSketch));
    memset(gs->VertexIndexToDegreeMap, 0, GRAPH_MAX_SIZE);
    gs->BvhTree = NULL;
    gs->Graph = Graph_CreateGraph();
    gs->ShowDirection = true;
    gs->ShowWeight = true;
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
