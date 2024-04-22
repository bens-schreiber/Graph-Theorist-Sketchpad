//
//  Graph.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#include "Graph.h"
#include <stdlib.h>
#include <assert.h>

#define VERTEX_EXISTS(g, x) ((g)->AdjMatrix[(x)][(x)].Exists)
#define VERTEX_NOT_EXISTS(g,x) (!VERTEX_EXISTS(g,x))

#define DEFAULT_ADJ_MATRIX_VALUE ((AdjacencyMatrixValue) \
{ .State = NO_ADJACENCY, .Exists = false, .Weight = 0 })

static Graph *_Graph_Factory(bool directed)
{
    Graph *g = malloc(sizeof(Graph));
    g->Edges = 0;
    g->Vertices = 0;
    g->NextVertexIndexToBeInserted = 0;
    g->Directed = directed;
    
    for (int i = 0; i < GRAPH_MAX_SIZE; ++i)
    {
        for (int j = 0; j < GRAPH_MAX_SIZE; ++j)
        {
            g->AdjMatrix[i][j] = DEFAULT_ADJ_MATRIX_VALUE;
        }
    }
    
    return g;
}
Graph *Graph_CreateGraph(void)
{
    return _Graph_Factory(false);
}

Graph *Graph_CreateDigraph(void)
{
    return _Graph_Factory(true);
}

u_short Graph_AddVertex(Graph *g)
{
    assert(g != NULL);
    assert(VERTEX_NOT_EXISTS(g, g->NextVertexIndexToBeInserted));
    assert(g->NextVertexIndexToBeInserted < GRAPH_MAX_SIZE);
    
    g->AdjMatrix[g->NextVertexIndexToBeInserted][g->NextVertexIndexToBeInserted]
        = DEFAULT_ADJ_MATRIX_VALUE;
    g->AdjMatrix[g->NextVertexIndexToBeInserted][g->NextVertexIndexToBeInserted]
        .Exists = true;
    
    g->Vertices++;
    return g->NextVertexIndexToBeInserted++;
}

void Graph_SetAdjacency(Graph *g, u_short v1, u_short v2)
{
    assert(g != NULL);
    assert(VERTEX_EXISTS(g, v1));
    assert(VERTEX_EXISTS(g, v2));
    
    g->AdjMatrix[v1][v2].State = ADJACENCY;
    
    if (!g->Directed)
    {
        g->AdjMatrix[v2][v1].State = ADJACENCY;
    }
    
    g->Edges++;
}

bool Graph_IsAdjacent(Graph *g, u_short v1, u_short v2)
{
    assert(g != NULL);
    return g->AdjMatrix[v1][v2].State == ADJACENCY || g->AdjMatrix[v1][v2].State == SELF_LOOP;
}

bool Graph_IsNotAdjacent(Graph *g, u_short v1, u_short v2)
{
    return !Graph_IsAdjacent(g, v1, v2);
}

void Graph_RemoveEdge(Graph *g, u_short v1, u_short v2)
{
    assert(g != NULL);
    assert(VERTEX_EXISTS(g, v1));
    assert(VERTEX_EXISTS(g, v2));
    
    g->AdjMatrix[v1][v2].State = NO_ADJACENCY;
    g->AdjMatrix[v2][v1].State = NO_ADJACENCY;
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
                if (g->AdjMatrix[i][j].State == ADJACENCY)
                {
                    g->Edges--;
                }
                if (g->AdjMatrix[i][j].State == SELF_LOOP)
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
            
            AdjacencyMatrixValue newValue = DEFAULT_ADJ_MATRIX_VALUE;
            if (i + skip_i < GRAPH_MAX_SIZE && j + skip_j < GRAPH_MAX_SIZE)
            {
                newValue = g->AdjMatrix[i + skip_i][j + skip_j];
            }
            
            g->AdjMatrix[i][j] = newValue;
            
        }
    }
    g->Vertices--;
}

void Graph_SetSelfLoop(Graph *g, u_short v)
{
    assert(g != NULL);
    assert(VERTEX_EXISTS(g, v));
    
    g->AdjMatrix[v][v].State = SELF_LOOP;
    g->Edges++;
}


