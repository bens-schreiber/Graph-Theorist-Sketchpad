//
//  Graph.h
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#ifndef Graph_h
#define Graph_h

#include <stdbool.h>

#define GRAPH_MAX_SIZE 127

#define WE_DNE          0
#define WE_MIN          1

typedef char StringBuffer[0xFFF];
typedef unsigned int VertexIndex;

/// A value greater than 0 implies the edge exists with weight of the value, a value 0 indicates there is no edge.
typedef unsigned int WeightedEdge;

typedef struct
{
    unsigned int Edges;
    unsigned int Vertices;
    bool IsDirected;
    bool IsWeighted;
    WeightedEdge AdjMatrix[GRAPH_MAX_SIZE][GRAPH_MAX_SIZE];
} Graph;

/// Returns a new graph with 0 edges, 0 vertices and the 0 matrix adj matrix
Graph *Graph_CreateGraph(void);

/// Frees the memory of the graph
void Graph_FreeGraph(Graph *g);

/// Adds a vertex to the adjacency table at index VertexRange O(1)
/// - Returns: the index of the vertex created
VertexIndex Graph_AddVertex(Graph *g);

/// Sets two vertices to be adjacent, ie connected by an edge
/// On a digraph, v1 will be adj to v2 but not vice versa
/// - Parameters:
///   - g: The graph
///   - v1: The vertex to be adjacent to v2
///   - v2: The vertex to be adjacent to v1
void Graph_SetAdjacent(Graph *g, VertexIndex v1, VertexIndex v2);

/// Returns if two vertex are adjacent
/// On a digraph, v1 can be adj to v2 but not neccesarily vice versa
/// - Parameters:
///   - g: The graph
///   - v1: The vertex to be adjacent to v2
///   - v2: The vertex to be adjacent to v1
/// - Returns: 1 if adjacent, 0 otherwise
bool Graph_IsAdjacent(Graph *g, VertexIndex, VertexIndex v2);

/// Returns if two vertex are not adjacent
/// On a digraph, v1 can not be adj to v2 but not neccesarily vice versa
/// - Parameters:
///   - g: The graph
///   - v1: The vertex to not be adjacent to v2
///   - v2: The vertex to not be adjacent to v1
/// - Returns: 1 if adjacent, 0 otherwise
bool Graph_IsNotAdjacent(Graph *g, VertexIndex v1, VertexIndex v2);

/// Removes adjacency between two vertices. O(1)
/// - Parameters:
///   - v1: The vertex to have no adjacency to v2
///   - v2: The vertex to have no adjacency to v1
void Graph_RemoveEdge(Graph *g, VertexIndex v1, VertexIndex v2);

/// Removes a vertex from the adjacency table. O(V) time
/// - Parameters:
///   - v: The vertex to be removed from the table
void Graph_RemoveVertex(Graph *g, VertexIndex v);

/// Adds a self loop to a vertex
void Graph_SetSelfLoop(Graph *g, VertexIndex v);

/// Sets two adjacent vertices weight;
void Graph_SetAdjacencyWeighted(Graph *g, VertexIndex v1, VertexIndex v2, VertexIndex weight);

/// - Returns: The degree of vertex v
unsigned int Graph_VertexDegree(Graph *g, VertexIndex v);

void Graph_Dijkstra(Graph *g, VertexIndex v1, VertexIndex v2, StringBuffer buffer);

void Graph_DumpString(Graph *g, StringBuffer buffer);

#endif /* Graph_h */
