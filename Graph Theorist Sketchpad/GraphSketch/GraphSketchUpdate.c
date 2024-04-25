//
//  GraphSketchUpdate.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/24/24.
//

#include "GraphSketch.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void GraphSketch_RefreshBvhTree(GraphSketch *gs, Rectangle sceneBoundingBox)
{
    if (gs->BvhTree != NULL)
    {
        BvhTree_FreeBvhTree(gs->BvhTree);
    }
    
    Primitive primitives[gs->Graph->Vertices];
    memcpy(primitives, gs->IndexToPrimitiveMap, sizeof(primitives));
    gs->BvhTree = BvhTree_CreateBvhTree(primitives, gs->Graph->Vertices, sceneBoundingBox);
}

VertexIndex GraphSketch_AddVertex(GraphSketch *gs, Vector2 position, Color color, Rectangle sceneBoundingBox)
{
    assert(gs != NULL);
    
    // Add a vertex to the graph
    VertexIndex vi = Graph_AddVertex(gs->Graph);
    
    // Add a collideable at the given position
    gs->IndexToPrimitiveMap[vi] = Primitive_CreatePrimitive(position, vi);
    
    // Re-create the Bvh Tree on every graph change
    GraphSketch_RefreshBvhTree(gs, sceneBoundingBox);
    
    // Add a vertex to the display
    char numStr[4];
    sprintf(numStr, "v%u", vi);
    numStr[3] = '\0';
    gs->IndexToDrawableVertexMap[vi] = DrawableVertex_CreateDrawableVertex(numStr, color, vi);
    return vi;
}

void GraphSketch_AddEdge(GraphSketch *gs, VertexIndex v1, VertexIndex v2, short weight)
{
    assert(gs != NULL);
    
    int curvature = 0;
    if (Graph_IsAdjacent(gs->Graph, v1, v2) || Graph_IsAdjacent(gs->Graph, v2, v1))
    {
        unsigned int edgesShared = Graph_EdgesShared(gs->Graph, v1, v2);
        if (edgesShared % 2)
        {
            curvature = edgesShared * 40;
        }
        else
        {
            curvature = (edgesShared - 1) * (-40);
        }
    }
    
    EdgeIndex ei = Graph_AddEdgeWeighted(gs->Graph, v1, v2, weight);
    
    char numStr[4];
    sprintf(numStr, "e%u", ei);
    numStr[3] = '\0';
    gs->DrawableEdgeList[ei] = DrawableEdge_CreateDrawableEdge(numStr, v1, v2, ei, curvature);
    gs->VertexIndexToDegreeMap[v1]++;
    gs->VertexIndexToDegreeMap[v2]++;
}
