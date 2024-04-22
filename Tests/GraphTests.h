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

void Graph_CreateNew_SetsAllValuesToZero(void)
{
    // Act
    Graph *g = Graph_CreateGraph();
    
    // Assert
    assert(g != NULL);
    assert(g->Edges == 0);
    assert(g->Vertices == 0);
    assert(g->NextVertexIndexToBeInserted == 0);
    
    for (int i = 0; i < GRAPH_MAX_SIZE; ++i) {
        for (int j = 0; j < GRAPH_MAX_SIZE; ++j) {
            assert(g->AdjMatrix[i][j].State == NO_ADJACENCY);
        }
    }
    
    // Cleanup
    free(g);
}

void Graph_AddMultipleVertices_PopulatesMatrixDiagonal(void)
{
    // Arrange
    Graph *g = Graph_CreateGraph();
    
    // Act
    Graph_AddVertex(g);
    Graph_AddVertex(g);
    Graph_AddVertex(g);
    
    // Assert
    assert(g->Vertices == 3);
    assert(g->AdjMatrix[0][0].Exists);
    assert(g->AdjMatrix[1][1].Exists);
    assert(g->AdjMatrix[2][2].Exists);
    assert(g->NextVertexIndexToBeInserted == 3);
    
    // Cleanup
    free(g);
}

void Graph_SetAdjacency_SetsVerticesToAdjacent(void)
{
    // Arrange
    Graph *g = Graph_CreateGraph();
    u_short v1 = Graph_AddVertex(g);
    u_short v2 = Graph_AddVertex(g);
    
    // Act
    Graph_SetAdjacency(g, v1, v2);
    
    // Assert
    assert(g->Edges == 1);
    assert(Graph_IsAdjacent(g, v1, v2));
    assert(Graph_IsAdjacent(g, v2, v1));
    
    // Cleanup
    free(g);
}

void Graph_RemoveEdge_SetsVerticesToExistsNoAdjacency(void)
{
    // Arrange
    Graph *g = Graph_CreateGraph();
    u_short v1 = Graph_AddVertex(g);
    u_short v2 = Graph_AddVertex(g);
    Graph_SetAdjacency(g, v1, v2);
    
    // Act
    Graph_RemoveEdge(g, v1, v2);
    
    // Assert
    assert(g->Edges == 0);
    assert(!Graph_IsAdjacent(g, v1, v2));
    assert(!Graph_IsAdjacent(g, v2, v1));
    
    // Cleanup
    free(g);
}

void Graph_RemoveVertex1_RemovesRowAndColumnFromAdjMatrix(void)
{
    // Arrange
    Graph *g = Graph_CreateGraph();
    u_short v1 = Graph_AddVertex(g);
    Graph_AddVertex(g);
    Graph_AddVertex(g);
    Graph_AddVertex(g);
    
    
    // Act
    Graph_RemoveVertex(g, v1);
    
    // Assert
    assert(g->Vertices == 3);
    assert(g->AdjMatrix[0][0].Exists);
    assert(Graph_IsNotAdjacent(g, 3, 3));
    
    // Cleanup
    free(g);
}

void Graph_RemoveVertexOffset_RemovesRowAndColumnFromAdjMatrix(void)
{
    // Arrange
    Graph *g = Graph_CreateGraph();
    Graph_AddVertex(g);
    u_short v2 = Graph_AddVertex(g);
    Graph_AddVertex(g);
    Graph_AddVertex(g);
    
    
    // Act
    Graph_RemoveVertex(g, v2);
    
    // Assert
    assert(g->Vertices == 3);
    assert(g->AdjMatrix[0][0].Exists);
    assert(Graph_IsNotAdjacent(g, 3, 3));
    
    // Cleanup
    free(g);
}

void Graph_RemoveVertexWithSelfLoop_RemovesRowAndColumnFromAdjMatrix(void)
{
    // Arrange
    Graph *g = Graph_CreateGraph();
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
    assert(g->AdjMatrix[0][0].Exists);
    assert(Graph_IsNotAdjacent(g, 3, 3));
    
    // Cleanup
    free(g);
}

void Digraph_SetAdjacency_GoesOneWay(void)
{
    // Arrange
    Graph *g = Graph_CreateDiGraph();
    u_short v1 = Graph_AddVertex(g);
    u_short v2 = Graph_AddVertex(g);
    
    // Act
    Graph_SetAdjacency(g, v1, v2);
    
    // Assert
    assert(Graph_IsAdjacent(g, v1, v2));
    assert(Graph_IsNotAdjacent(g, v2, v1));
    
    // Cleanup
    free(g);
}


#endif /* GraphTests_h */
