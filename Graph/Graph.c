//
//  Graph.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#include "Graph.h"
#include <stdlib.h>
#include <assert.h>

#define VERTEX_EXISTS(g, x) ((g)->AdjMatrix[(x)][(x)] == EXISTS_WITH_NO_ADJACENCY)
#define VERTEX_NOT_EXISTS(g,x) (!VERTEX_EXISTS(g,x))

Graph *Graph_CreateGraph(void)
{
    Graph *g = malloc(sizeof(Graph));
    g->Edges = 0;
    g->Vertices = 0;
    
    for (int i = 0; i < GRAPH_MAX_SIZE; ++i) {
        for (int j = 0; j < GRAPH_MAX_SIZE; ++j) {
            g->AdjMatrix[i][j] = NO_ADJACENCY;
        }
    }
    
    return g;
}

u_short Graph_AddVertex(Graph *g)
{
    static u_short lastInsertedVertexIndex = 0;
    assert(g != NULL);
    assert(VERTEX_NOT_EXISTS(g, lastInsertedVertexIndex));
    assert(lastInsertedVertexIndex < GRAPH_MAX_SIZE);
    
    g->AdjMatrix[lastInsertedVertexIndex][lastInsertedVertexIndex] = EXISTS_WITH_NO_ADJACENCY;
    g->Vertices++;
    return lastInsertedVertexIndex++;
}

void Graph_SetAdjacency(Graph *g, u_short v1, u_short v2)
{
    assert(g != NULL);
    assert(VERTEX_EXISTS(g, v1));
    assert(VERTEX_EXISTS(g, v2));
    
    g->AdjMatrix[v1][v2] = ADJACENCY;
    g->AdjMatrix[v2][v1] = ADJACENCY;
    g->Edges++;
}

u_short Graph_IsAdjacent(Graph *g, u_short v1, u_short v2)
{
    assert(g != NULL);
    assert(VERTEX_EXISTS(g, v1));
    assert(VERTEX_EXISTS(g, v2));
    
    return g->AdjMatrix[v1][v2] == ADJACENCY;
}


