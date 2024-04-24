//
//  GraphSketch.h
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/24/24.
//

#ifndef GraphSketch_h
#define GraphSketch_h

#include "../Bvh/BvhTree.h"
#include "../Bvh/Primitive/Primitive.h"
#include "../../Graph/Graph.h"

#define GRAPH_VERTEX_RADIUS 15
#define GRAPH_MAX_PRIMITIVES (GRAPH_MAX_SIZE*2)

typedef char Label[25];

/// A collection of information that can be associated with a paticular vertex of a graph at some index
typedef struct
{
    Label Label;
    Color Color;
    VertexIndex VertexIndex;
} DrawableVertex;

/// Creates a new drawable vertex
DrawableVertex DrawableVertex_CreateDrawableVertex(const char* label, Color color, VertexIndex vi);

/// Draws a vertex around a primitives centroid
void DrawableVertex_Draw(DrawableVertex *dv, Primitive *p);

/// The displaying graph on the screen
typedef struct
{
    /// A map of vertex indices to their collision primitive
    Primitive IndexToPrimitiveMap[GRAPH_MAX_PRIMITIVES];
    
    /// A map of vertex indices to drawing information for a vertex
    DrawableVertex IndexToDrawableVertexMap[GRAPH_MAX_SIZE];
    
    /// A bounding volume hierarchy tree used for collision detection on primitives
    BvhTree *BvhTree;
    
    /// The mathematical representation of the graph
    Graph *Graph;
    
} GraphSketch;

/// Creates a new GraphSketch with no primitives, drawables, vertices in the Graph, and a null BvhTree
GraphSketch *GraphSketch_CreateGraphSketch(void);

/// Frees the memory of the graph sketch
void GraphSketch_FreeGraphSketch(GraphSketch *gs);

/// Creates a collideable vertex centered around the given position within the scene
/// - Returns: The index of the added vertex
VertexIndex GraphSketch_AddVertex(GraphSketch *gs, Vector2 position, Rectangle sceneBoundingBox);

/// Draws the drawable vertices
void GraphSketch_DrawVertices(GraphSketch *gs);

/// Draws the graphs adjacency matrix
/// - Parameters:
///    - gs: the graph sketch
///    - buffer: the string buffer to be used for the drawing
///    - update: whether or not to fetch the new adjacency table
void GraphSketch_DrawAdjMatrix(GraphSketch *gs, StringBuffer buffer, bool update);

#endif /* GraphSketch_h */

