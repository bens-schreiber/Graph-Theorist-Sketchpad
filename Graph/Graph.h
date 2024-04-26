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

#define INCIDENCE_MATRIX_NEGATIVE_DIRECTION    (-1)
#define INCIDENCE_MATRIX_NO_VALUE               0
#define INCIDENCE_MATRIX_POSITIVE_DIRECTION     1

typedef char StringBuffer[0xFFF];
typedef unsigned int VertexIndex;
typedef unsigned int EdgeIndex;

typedef struct
{
    unsigned int Edges;
    unsigned int Vertices;
    
    /// Maps Vertex to Vertex returning true if they are adjacent, false if they are not
    bool AdjMatrix[GRAPH_MAX_SIZE][GRAPH_MAX_SIZE];
    
    /// Maps Vertex to Edge returning a weight:
    /// 0 if they do not connect,
    /// greater than 0 if they connect and it is directed outwards,
    /// less than 0 if they connect and is directed inwards
    ///
    /// NOTE: A self loop is denoted by a single entry in a column
    signed int IncidenceMatrix[GRAPH_MAX_SIZE][GRAPH_MAX_SIZE];
} Graph;

/// Returns a new graph with 0 edges, 0 vertices, false values in the adj matrix, and all 0's in the incidence matrix
Graph *Graph_CreateGraph(void);

/// Frees the memory of the graph
void Graph_FreeGraph(Graph *g);

/// Adds a vertex to the adjacency matrix and incidence matrix O(1)
/// - Returns: the index of the vertex created
VertexIndex Graph_AddVertex(Graph *g);

/// Sets v1 to share an edge with v2, ie AdjMatrix[v1][v2] == true
/// - Parameters:
///   - g: The graph
///   - v1: The vertex to be directed towards v2
///   - v2: The vertex to share an edge with v1
/// - Returns: the new edge index
EdgeIndex Graph_AddEdge(Graph *g, VertexIndex v1, VertexIndex v2);

/// Sets v1 to share an edge with v2, ie AdjMatrix[v1][v2] == true
/// - Parameters:
///   - g: The graph
///   - v1: The vertex to be directed towards v2
///   - v2: The vertex to share an edge with v1
///   - weight: the weight of the egde
/// - Returns: the new edge index
EdgeIndex Graph_AddEdgeWeighted(Graph *g, VertexIndex v1, VertexIndex v2, VertexIndex weight);

/// Removes the edge e from the graph
void Graph_RemoveEdge(Graph *g, EdgeIndex e);

/// Queries the incidence matrix
/// - Parameters:
///   - g: The graph
///   - v: the vertex
///   - e: the edge
/// - Returns: if an edge is incident to a vertex
bool Graph_IsIncident(Graph *g, VertexIndex v, EdgeIndex e);

/// Queries the incidence matrix
/// - Parameters:
///   - g: The graph
///   - v: the vertex
///   - e: the edge
/// - Returns: if an edge is not incident to a vertex
bool Graph_IsNotIncident(Graph *g, VertexIndex v, EdgeIndex e);

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

/// - Returns: the amount of edges shared between v1 and v2
unsigned int Graph_EdgesShared(Graph *g, VertexIndex v1, VertexIndex v2);

/// - Returns: The degree of vertex v
unsigned int Graph_VertexDegree(Graph *g, VertexIndex v);

/// Dumps the adj matrix into a string
void Graph_DumpAdjMatrix(Graph *g, StringBuffer buffer);

/// Dumps the incidence matrix into a string
void Graph_DumpIncidenceMatrix(Graph *g, StringBuffer buffer);

#endif /* Graph_h */
