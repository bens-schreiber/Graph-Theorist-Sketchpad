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
    u_short nextVertexIndexToBeInserted;
    VertexState AdjMatrix[GRAPH_MAX_SIZE][GRAPH_MAX_SIZE];
} Graph;

/// Returns a new graph with 0 edges, 0 vertices and the 0 matrix adj matrix
Graph *Graph_CreateGraph(void);

/// Adds a vertex to the next available spot in the AdjMatrix, with state EXISTS WITH NO ADJACENCY. O(1)
/// - Returns: the index of the vertex created
u_short Graph_AddVertex(Graph *g);

/// Sets two vertices to be adjacent, ie connected by an edge
/// - Parameters:
///   - g: The graph
///   - v1: The vertex to be adjacent to v2
///   - v2: The vertex to be adjacent to v1
void Graph_SetAdjacency(Graph *g, u_short v1, u_short v2);

/// Returns if two vertex are adjacent
/// - Parameters:
///   - g: The graph
///   - v1: The vertex to be adjacent to v2
///   - v2: The vertex to be adjacent to v1
/// - Returns: 1 if adjacent, 0 otherwise
u_short Graph_IsAdjacent(Graph *g, u_short v1, u_short v2);

/// Removes adjacency between two vertices. O(1)
/// - Parameters:
///   - v1: The vertex to have no adjacency to v2
///   - v2: The vertex to have no adjacency to v1
void Graph_RemoveEdge(Graph *g, u_short v1, u_short v2);

/// Removes a vertex from the adjacency table. O(V) time
/// - Parameters:
///   - v: The vertex to be removed from the table
void Graph_RemoveVertex(Graph *g, u_short v);

/// Adds a self loop to a vertex
/// - Parameters:
///   - v: The vertex to be self looped
void Graph_SetSelfLoop(Graph *g, u_short v);

#endif /* Graph_h */
