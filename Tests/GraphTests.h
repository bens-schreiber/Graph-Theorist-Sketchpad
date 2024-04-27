//
//  GraphTests.h
//  Tests
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#ifndef GraphTests_h
#define GraphTests_h

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <stdbool.h>
#include "Graph.h"

#define TEST static inline void
#define GRAPH_TEST_CASE(name) TEST name(void) { _Setup_Graph_Tests(_##name); }

static void _Setup_Graph_Tests(void (*test)(Graph*))
{
    Graph *g = Graph_CreateGraph();
    assert(g != NULL);
    test(g);
    Graph_FreeGraph(g);
}

TEST _Graph_CreateNew_SetsAllValuesToZero(Graph *g)
{
    // Assert
    assert(g->Edges == 0);
    assert(g->Vertices == 0);
    
    for (int i = 0; i < GRAPH_MAX_SIZE; ++i) {
        for (int j = 0; j < GRAPH_MAX_SIZE; ++j) {
            assert(g->AdjMatrix[i][j] == false);
            assert(g->IncidenceMatrix[i][j] == INCIDENCE_MATRIX_NO_VALUE);
        }
    }
}
GRAPH_TEST_CASE(Graph_CreateNew_SetsAllValuesToZero)


TEST _Graph_AddVerticesWithSelfLoops_PopulatesIncidenceMatrixAndAdjacencyMatrix(Graph *g)
{
    // Arrange
    VertexIndex v1 = Graph_AddVertex(g);
    VertexIndex v2 = Graph_AddVertex(g);
    VertexIndex v3 = Graph_AddVertex(g);
    
    // Act
    EdgeIndex e1 = Graph_AddEdge(g, v1, v1);
    EdgeIndex e2 = Graph_AddEdge(g, v2, v2);
    EdgeIndex e3 = Graph_AddEdge(g, v3, v3);
    
    // Assert
    assert(g->Vertices == 3);
    assert(g->Edges == 3);
    assert(g->AdjMatrix[v1][v1]);
    assert(g->AdjMatrix[v2][v2]);
    assert(g->AdjMatrix[v3][v3]);
    assert(g->IncidenceMatrix[v1][e1]);
    assert(g->IncidenceMatrix[v2][e2]);
    assert(g->IncidenceMatrix[v3][e3]);
}
GRAPH_TEST_CASE(Graph_AddVerticesWithSelfLoops_PopulatesIncidenceMatrixAndAdjacencyMatrix)


TEST _Graph_AddVertexAdjacency_VerticesAreAdjacentAndIncident(Graph *g)
{
    // Arrange
    VertexIndex v1 = Graph_AddVertex(g);
    VertexIndex v2 = Graph_AddVertex(g);
    
    // Act
    EdgeIndex e1 = Graph_AddEdge(g, v1, v2);
    
    // Assert
    assert(g->Edges == 1);
    assert(Graph_IsIncident(g, v1, e1));
    assert(Graph_IsIncident(g, v2, e1));
    assert(Graph_IsAdjacent(g, v1, v2));
    assert(Graph_IsNotAdjacent(g, v2, v1));
}
GRAPH_TEST_CASE(Graph_AddVertexAdjacency_VerticesAreAdjacentAndIncident)

TEST _Graph_VertexDegree_ReturnsCorrectDegree(Graph *g)
{
    // Arrange
    VertexIndex v1 = Graph_AddVertex(g);
    VertexIndex v2 = Graph_AddVertex(g);
    VertexIndex v3 = Graph_AddVertex(g);
    VertexIndex v4 = Graph_AddVertex(g);
    
    Graph_AddEdge(g, v1, v2);
    Graph_AddEdge(g, v1, v2);
    Graph_AddEdge(g, v1, v2);
    Graph_AddEdge(g, v1, v1);
    
    Graph_AddEdge(g, v2, v3);
    Graph_AddEdge(g, v2, v4);
    
    // Act
    unsigned int degV1 = Graph_VertexDegree(g, v1);
    unsigned int degV2 = Graph_VertexDegree(g, v2);
    unsigned int degV3 = Graph_VertexDegree(g, v3);
    unsigned int degV4 = Graph_VertexDegree(g, v4);
    
    // Assert
    assert(g->Edges == 6);
    assert(degV1 == 4);
    assert(degV2 == 5);
    assert(degV3 == 1);
    assert(degV4 == 1);
}
GRAPH_TEST_CASE(Graph_VertexDegree_ReturnsCorrectDegree)


TEST _Graph_KruskalsAlgorithm_CorrectlyDeterminesMST(Graph *g)
{
    // Arrange
    VertexIndex v1 = Graph_AddVertex(g);
    VertexIndex v2 = Graph_AddVertex(g);
    VertexIndex v3 = Graph_AddVertex(g);
    VertexIndex v4 = Graph_AddVertex(g);
    VertexIndex v5 = Graph_AddVertex(g);
    
    EdgeIndex e1 = Graph_AddEdge(g, v1, v2);
    Graph_AddEdge(g, v2, v3);
    Graph_AddEdge(g, v3, v4);
    EdgeIndex e4 = Graph_AddEdge(g, v4, v5);
    
    EdgeIndex edges[g->Vertices - 1];
    
    // Act
    Graph_MinSpanningTree(g, edges);
    
    // Assert
    assert(edges[0] == e1);
    assert(edges[3] == e4);
    
}
GRAPH_TEST_CASE(Graph_KruskalsAlgorithm_CorrectlyDeterminesMST)


TEST _Graph_KruskalsAlgorithmWithWeights_CorrectlyDeterminesMST(Graph *g)
{
    // Arrange
    VertexIndex v1 = Graph_AddVertex(g);
    VertexIndex v2 = Graph_AddVertex(g);
    VertexIndex v3 = Graph_AddVertex(g);
    VertexIndex v4 = Graph_AddVertex(g);
    VertexIndex v5 = Graph_AddVertex(g);
    
    Graph_AddEdgeWeighted(g, v1, v2, 30);
    EdgeIndex e1 = Graph_AddEdgeWeighted(g, v1, v2, 1);
    
    Graph_AddEdgeWeighted(g, v2, v3, 50);
    EdgeIndex e2 = Graph_AddEdgeWeighted(g, v2, v3, 49);
    
    Graph_AddEdgeWeighted(g, v3, v4, 100);
    EdgeIndex e3 = Graph_AddEdgeWeighted(g, v3, v4, 50);
    
    Graph_AddEdgeWeighted(g, v4, v4, 10);   // self loop
    EdgeIndex e4 = Graph_AddEdgeWeighted(g, v4, v5, 51);
    
    EdgeIndex edges[g->Vertices - 1];
    
    // Act
    Graph_MinSpanningTree(g, edges);
    
    // Assert
    assert(edges[0] == e1);
    assert(edges[1] == e2);
    assert(edges[2] == e3);
    assert(edges[3] == e4);
    
}
GRAPH_TEST_CASE(Graph_KruskalsAlgorithmWithWeights_CorrectlyDeterminesMST)


#endif /* GraphTests_h */
