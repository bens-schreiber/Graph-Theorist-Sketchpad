//
//  GraphSketchUpdate.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/24/24.
//

#include "GraphSketch.h"
#include <assert.h>

VertexIndex GraphSketch_AddVertex(GraphSketch *gs, Vector2 position, Rectangle sceneBoundingBox)
{
    assert(gs != NULL);
    
    // Add a vertex to the graph
    VertexIndex vi = Graph_AddVertex(gs->Graph);
    
    // Add a collideable at the given position
    gs->IndexToPrimitiveMap[vi] = Primitive_CreatePrimitive(position);
    
    // Re-create the Bvh Tree on every graph change
    if (gs->BvhTree != NULL)
    {
        BvhTree_FreeBvhTree(gs->BvhTree);
        gs->BvhTree = BvhTree_CreateBvhTree(gs->IndexToPrimitiveMap, vi, sceneBoundingBox);
    }
    
    // Add a vertex to the display
    gs->IndexToDrawableVertexMap[vi] = DrawableVertex_CreateDrawableVertex("", RED, vi);
    
    return vi;
}
