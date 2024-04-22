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
    g->nextVertexIndexToBeInserted = 0;
    g->directed = false;
    
    for (int i = 0; i < GRAPH_MAX_SIZE; ++i)
    {
        for (int j = 0; j < GRAPH_MAX_SIZE; ++j)
        {
            g->AdjMatrix[i][j] = NO_ADJACENCY;
        }
    }
    
    return g;
}

u_short Graph_AddVertex(Graph *g)
{
    assert(g != NULL);
    assert(VERTEX_NOT_EXISTS(g, g->nextVertexIndexToBeInserted));
    assert(g->nextVertexIndexToBeInserted < GRAPH_MAX_SIZE);
    
    g->AdjMatrix[g->nextVertexIndexToBeInserted][g->nextVertexIndexToBeInserted] = EXISTS_WITH_NO_ADJACENCY;
    g->Vertices++;
    return g->nextVertexIndexToBeInserted++;
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

void Graph_RemoveEdge(Graph *g, u_short v1, u_short v2)
{
    assert(g != NULL);
    assert(VERTEX_EXISTS(g, v1));
    assert(VERTEX_EXISTS(g, v2));
    
    g->AdjMatrix[v1][v2] = NO_ADJACENCY;
    g->AdjMatrix[v2][v1] = NO_ADJACENCY;
    g->Edges--;
}

void Graph_RemoveVertex(Graph *g, u_short v)
{
    
    bool skip_i = false;
    for (int i = 0; i < GRAPH_MAX_SIZE; ++i)
    {
        // Remove the edge count
        if (i == v)
        {
            for (int j = 0; j < GRAPH_MAX_SIZE; ++j)
            {
                if (g->AdjMatrix[i][j] == ADJACENCY)
                {
                    g->Edges--;
                }
                if (g->AdjMatrix[i][j] == SELF_LOOP)
                {
                    g->Edges--;
                }
            }
            skip_i = true;
        }
        
        bool skip_j = false;
        for (int j = 0; j < GRAPH_MAX_SIZE; ++j)
        {
            if (i == v)
            {
                skip_j = true;
            }
            
            VertexState newState = NO_ADJACENCY;
            if (i + skip_i < GRAPH_MAX_SIZE && j + skip_j < GRAPH_MAX_SIZE)
            {
                newState = g->AdjMatrix[i + skip_i][j + skip_j];
            }
            
            g->AdjMatrix[i][j] = newState;
            
        }
    }
    g->Vertices--;
}

void Graph_SetSelfLoop(Graph *g, u_short v)
{
    assert(g != NULL);
    assert(VERTEX_EXISTS(g, v));
    
    g->AdjMatrix[v][v] = SELF_LOOP;
    g->Edges++;
}


