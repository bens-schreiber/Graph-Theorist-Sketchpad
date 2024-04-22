//
//  Graph.h
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#ifndef Graph_h
#define Graph_h

#include <sys/types.h>

#define GRAPH_MAX_SIZE 100

typedef enum
{
    NO_ADJACENCY,
    EXISTS_WITH_NO_ADJACENCY,
    ADJACENCY,
    SELF_LOOP
} VertexState;

typedef struct
{
    u_int Edges;
    u_int Vertices;
    VertexState AdjMatrix[GRAPH_MAX_SIZE][GRAPH_MAX_SIZE];
} Graph;

/// Returns a new graph with 0 edges, 0 vertices and the 0 matrix adj matrix
Graph *Graph_CreateGraph(void);

/// Adds a vertex to the next available spot in the AdjMatrix, with state EXISTS WITH NO ADJACENCY
/// - Parameter g: The graph to add the vertex to
/// - Returns: the index of the vertex created
u_short Graph_AddVertex(Graph *g);

/// Sets two vertices to be adjacent, ie connected by an edge
/// - Parameters:
///   - v1: The vertex to be adjacent to v2
///   - v2: The vertex to be adjacent to v1
void Graph_SetAdjacency(Graph *g, u_short v1, u_short v2);

/// Returns if two vertex are adjacent
/// - Parameters:
///   - v1: The vertex to be adjacent to v2
///   - v2: The vertex to be adjacent to v1
/// - Returns: 1 if adjacent, 0 otherwise
u_short Graph_IsAdjacent(Graph *g, u_short v1, u_short v2);

#endif /* Graph_h */
