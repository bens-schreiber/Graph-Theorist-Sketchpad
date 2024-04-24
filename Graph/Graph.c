//
//  Graph.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#include "Graph.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#define VERTEX_EXISTS(g, x) (x <= g->Vertices)
#define VERTEX_NOT_EXISTS(g,x) (!VERTEX_EXISTS(g,x))

Graph *Graph_CreateGraph(void)
{
    Graph *g = malloc(sizeof(Graph));
    g->Edges = 0;
    g->Vertices = 0;
    g->IsDirected = false;
    g->IsWeighted = false;
    
    for (int i = 0; i < GRAPH_MAX_SIZE; ++i)
    {
        for (int j = 0; j < GRAPH_MAX_SIZE; ++j)
        {
            g->AdjMatrix[i][j] = WE_DNE;
        }
    }
    
    return g;
}

void Graph_FreeGraph(Graph *g)
{
    free(g);
}

VertexIndex Graph_AddVertex(Graph *g)
{
    assert(g != NULL);
    VertexIndex nextVertexIndex = g->Vertices + 1;
    assert(VERTEX_NOT_EXISTS(g, nextVertexIndex));
    assert(nextVertexIndex < GRAPH_MAX_SIZE);
    
    g->AdjMatrix[nextVertexIndex][nextVertexIndex]
    = WE_DNE;
    
    return g->Vertices++;
}

void Graph_SetAdjacencyWeighted(Graph *g, VertexIndex v1, VertexIndex v2, VertexIndex weight)
{
    assert(g != NULL);
    assert(VERTEX_EXISTS(g, v1));
    assert(VERTEX_EXISTS(g, v2));
    
    g->AdjMatrix[v1][v2] = weight;
    
    if (!g->IsDirected)
    {
        g->AdjMatrix[v2][v1] = weight;
    }
    
    g->Edges++;
}

void Graph_SetAdjacent(Graph *g, VertexIndex v1, VertexIndex v2)
{
    Graph_SetAdjacencyWeighted(g, v1, v2, WE_MIN);
}

bool Graph_IsAdjacent(Graph *g, VertexIndex v1, VertexIndex v2)
{
    assert(g != NULL);
    return g->AdjMatrix[v1][v2] > 0;
}

bool Graph_IsNotAdjacent(Graph *g, VertexIndex v1, VertexIndex v2)
{
    return !Graph_IsAdjacent(g, v1, v2);
}

void Graph_RemoveEdge(Graph *g, VertexIndex v1, VertexIndex v2)
{
    assert(g != NULL);
    assert(VERTEX_EXISTS(g, v1));
    assert(VERTEX_EXISTS(g, v2));
    
    g->AdjMatrix[v1][v2] = WE_DNE;
    g->AdjMatrix[v2][v1] = WE_DNE;
    g->Edges--;
}

void Graph_RemoveVertex(Graph *g, VertexIndex v)
{
    assert(g != NULL);
    assert(VERTEX_EXISTS(g, v));
    
    bool skip_i = false;
    for (int i = 0; i < GRAPH_MAX_SIZE; ++i)
    {
        // Remove the edge count
        if (i == v)
        {
            for (int j = 0; j < GRAPH_MAX_SIZE; ++j)
            {
                if (Graph_IsAdjacent(g, i, j))
                {
                    g->Edges -= g->AdjMatrix[i][j];
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
            
            WeightedEdge we = WE_DNE;
            if (i + skip_i < GRAPH_MAX_SIZE && j + skip_j < GRAPH_MAX_SIZE)
            {
                we = g->AdjMatrix[i + skip_i][j + skip_j];
            }
            
            g->AdjMatrix[i][j] = we;
            
        }
    }
    g->Vertices--;
}

void Graph_SetSelfLoop(Graph *g, VertexIndex v)
{
    assert(g != NULL);
    assert(VERTEX_EXISTS(g, v));
    
    g->AdjMatrix[v][v] = WE_MIN;
    g->Edges++;
}

unsigned int Graph_VertexDegree(Graph *g, VertexIndex v)
{
    assert(g != NULL);
    assert(VERTEX_EXISTS(g, v));
    
    unsigned int deg = 0;
    for (int i = 0; i < GRAPH_MAX_SIZE; i++)
    {
        if (Graph_IsAdjacent(g, v, i))
        {
            deg++;
        }
    }
    return deg;
}

void Graph_Dijkstra(Graph *g, VertexIndex v1, VertexIndex v2, StringBuffer buffer)
{
    
}

void Graph_DumpString(Graph *g, StringBuffer buffer)
{
    memset(buffer, '\0', sizeof(StringBuffer));
    char numStr[3];
    for (int i = 0; i < g->Vertices; i++)
    {
        for (int j = 0; j < g->Vertices; j++)
        {
            sprintf(numStr, "%u", g->AdjMatrix[i][j]);
            strcat(buffer, numStr);
            if (j + 1 < g->Vertices)
            {
                strcat(buffer, " ");
            }
        }
        strcat(buffer, "\n");
    }
}
