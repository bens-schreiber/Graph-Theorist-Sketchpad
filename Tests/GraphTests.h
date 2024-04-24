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
            assert(g->AdjMatrix[i][j] == WE_DNE);
        }
    }
}
GRAPH_TEST_CASE(Graph_CreateNew_SetsAllValuesToZero)


TEST _Graph_AddMultipleVertices_PopulatesMatrixDiagonal(Graph *g)
{
    // Act
    Graph_AddVertex(g);
    Graph_AddVertex(g);
    Graph_AddVertex(g);
    
    // Assert
    assert(g->Vertices == 3);
    assert(g->AdjMatrix[0][0] == WE_DNE);
    assert(g->AdjMatrix[1][1] == WE_DNE);
    assert(g->AdjMatrix[2][2] == WE_DNE);
}
GRAPH_TEST_CASE(Graph_AddMultipleVertices_PopulatesMatrixDiagonal)


TEST _Graph_SetAdjacency_SetsVerticesToAdjacent(Graph *g)
{
    // Arrange
    u_short v1 = Graph_AddVertex(g);
    u_short v2 = Graph_AddVertex(g);
    
    // Act
    Graph_SetAdjacent(g, v1, v2);
    
    // Assert
    assert(g->Edges == 1);
    assert(Graph_IsAdjacent(g, v1, v2));
    assert(Graph_IsAdjacent(g, v2, v1));
}
GRAPH_TEST_CASE(Graph_SetAdjacency_SetsVerticesToAdjacent)


TEST _Graph_RemoveEdge_SetsVerticesToExistsNoAdjacency(Graph *g)
{
    // Arrange
    u_short v1 = Graph_AddVertex(g);
    u_short v2 = Graph_AddVertex(g);
    Graph_SetAdjacent(g, v1, v2);
    
    // Act
    Graph_RemoveEdge(g, v1, v2);
    
    // Assert
    assert(g->Edges == 0);
    assert(!Graph_IsAdjacent(g, v1, v2));
    assert(!Graph_IsAdjacent(g, v2, v1));
}
GRAPH_TEST_CASE(Graph_RemoveEdge_SetsVerticesToExistsNoAdjacency)


TEST _Graph_RemoveVertex1_RemovesRowAndColumnFromAdjMatrix(Graph *g)
{
    // Arrange
    u_short v1 = Graph_AddVertex(g);
    Graph_SetSelfLoop(g, v1);
    Graph_AddVertex(g);
    Graph_AddVertex(g);
    Graph_AddVertex(g);
    
    // Act
    Graph_RemoveVertex(g, v1);
    
    // Assert
    assert(g->Vertices == 3);
    assert(g->AdjMatrix[0][0] == WE_DNE);
    assert(Graph_IsNotAdjacent(g, 3, 3));
}
GRAPH_TEST_CASE(Graph_RemoveVertex1_RemovesRowAndColumnFromAdjMatrix)


TEST _Graph_RemoveVertexOffset_RemovesRowAndColumnFromAdjMatrix(Graph *g)
{
    // Arrange
    Graph_AddVertex(g);
    u_short v2 = Graph_AddVertex(g);
    Graph_SetSelfLoop(g, v2);
    Graph_AddVertex(g);
    Graph_AddVertex(g);
    
    // Act
    Graph_RemoveVertex(g, v2);
    
    // Assert
    assert(g->Vertices == 3);
    assert(g->AdjMatrix[0][0] == WE_DNE);
    assert(g->AdjMatrix[1][1] == WE_DNE);
    assert(Graph_IsNotAdjacent(g, 3, 3));
}
GRAPH_TEST_CASE(Graph_RemoveVertexOffset_RemovesRowAndColumnFromAdjMatrix)


TEST _Graph_RemoveVertexWithSelfLoop_RemovesRowAndColumnFromAdjMatrix(Graph *g)
{
    // Arrange
    Graph_AddVertex(g);
    u_short v2 = Graph_AddVertex(g);
    Graph_AddVertex(g);
    Graph_AddVertex(g);
    Graph_SetSelfLoop(g, v2);
    
    // Act
    Graph_RemoveVertex(g, v2);
    
    // Assert
    assert(g->Vertices == 3);
    assert(g->Edges == 0);
    assert(g->AdjMatrix[0][0] == WE_DNE);
    assert(Graph_IsNotAdjacent(g, 3, 3));
}
GRAPH_TEST_CASE(Graph_RemoveVertexWithSelfLoop_RemovesRowAndColumnFromAdjMatrix)


TEST _Graph_DigraphSetAdjacency_GoesOneWay(Graph *g)
{
    // Arrange
    g->IsDirected = true;
    u_short v1 = Graph_AddVertex(g);
    u_short v2 = Graph_AddVertex(g);
    
    // Act
    Graph_SetAdjacent(g, v1, v2);
    
    // Assert
    assert(Graph_IsAdjacent(g, v1, v2));
    assert(Graph_IsNotAdjacent(g, v2, v1));
}
GRAPH_TEST_CASE(Graph_DigraphSetAdjacency_GoesOneWay)


TEST _Graph_VertexDegree_ReturnsCorrectDegree(Graph *g)
{
    // Arrange
    u_short v1 = Graph_AddVertex(g);
    u_short v2 = Graph_AddVertex(g);
    u_short v3 = Graph_AddVertex(g);
    u_short v4 = Graph_AddVertex(g);
    
    Graph_SetSelfLoop(g, v1);
    Graph_SetAdjacent(g, v1, v2);
    Graph_SetAdjacent(g, v1, v3);
    
    // Act
    u_short deg1 = Graph_VertexDegree(g, v1);
    u_short deg2 = Graph_VertexDegree(g, v2);
    u_short deg3 = Graph_VertexDegree(g, v3);
    u_short deg4 = Graph_VertexDegree(g, v4);
    
    // Assert
    assert(deg1 == 3);
    assert(deg2 == 1);
    assert(deg3 == 1);
    assert(deg4 == 0);
}
GRAPH_TEST_CASE(Graph_VertexDegree_ReturnsCorrectDegree)


TEST _Graph_WeightedGraph_ReturnsCorrectWeight(Graph *g)
{
    // Arrange
    u_short v1 = Graph_AddVertex(g);
    u_short v2 = Graph_AddVertex(g);
    u_short v3 = Graph_AddVertex(g);
    
    // Act
    int weight = 100;
    Graph_SetAdjacencyWeighted(g, v1, v1, weight);
    Graph_SetSelfLoop(g, v3);
    
    // Assert
    assert(g->AdjMatrix[v1][v1] == weight);
    assert(g->AdjMatrix[v2][v2] == WE_DNE);
    assert(g->AdjMatrix[v3][v3] == WE_MIN);
}
GRAPH_TEST_CASE(Graph_WeightedGraph_ReturnsCorrectWeight)

#endif /* GraphTests_h */
