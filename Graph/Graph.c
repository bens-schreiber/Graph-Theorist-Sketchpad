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

Graph *Graph_CreateGraph(void)
{
    Graph *g = malloc(sizeof(Graph));
    g->Edges = 0;
    g->Vertices = 0;
    
    for (int i = 0; i < GRAPH_MAX_SIZE; ++i)
    {
        for (int j = 0; j < GRAPH_MAX_SIZE; ++j)
        {
            g->AdjMatrix[i][j] = false;
            g->IncidenceMatrix[i][j] = INCIDENCE_MATRIX_NO_VALUE;
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
    return g->Vertices++;
}

EdgeIndex Graph_AddEdgeWeighted(Graph *g, VertexIndex v1, VertexIndex v2, VertexIndex weight)
{
    assert(g != NULL);
    assert(weight > 0);
    
    int e = g->Edges;
    
    // Self loop
    if (v1 == v2)
    {
        g->IncidenceMatrix[v1][e] = weight;
        g->AdjMatrix[v1][v1] = true;
    } 
    else 
    {
        g->IncidenceMatrix[v1][e] = weight;
        g->IncidenceMatrix[v2][e] = INCIDENCE_MATRIX_NEGATIVE_DIRECTION;
        g->AdjMatrix[v1][v2] = true;
        g->AdjMatrix[v2][v1] = false;
    }
    
    g->Edges++;
    return e;
}

EdgeIndex Graph_AddEdge(Graph *g, VertexIndex v1, VertexIndex v2)
{
    return Graph_AddEdgeWeighted(g, v1, v2, INCIDENCE_MATRIX_POSITIVE_DIRECTION);
}

bool Graph_IsIncident(Graph *g, VertexIndex v, EdgeIndex e)
{
    assert(g != NULL);
    return g->IncidenceMatrix[v][e] != INCIDENCE_MATRIX_NO_VALUE;
}

bool Graph_IsNotIncident(Graph *g, VertexIndex v, EdgeIndex e)
{
    return !Graph_IsIncident(g, v, e);
}

bool Graph_IsAdjacent(Graph *g, VertexIndex v1, VertexIndex v2)
{
    assert(g != NULL);
    return g->AdjMatrix[v1][v2];
}

bool Graph_IsNotAdjacent(Graph *g, VertexIndex v1, VertexIndex v2)
{
    return !Graph_IsAdjacent(g, v1, v2);
}

unsigned int Graph_EdgesShared(Graph *g, VertexIndex v1, VertexIndex v2)
{
    unsigned int edges = 0;
    for (int e = 0; e < g->Edges; e++)
    {
        if (Graph_IsIncident(g, v1, e) && Graph_IsIncident(g, v2, e))
        {
            edges++;
        }
    }
    return edges;
}

unsigned int Graph_VertexDegree(Graph *g, VertexIndex v)
{
    assert(g != NULL);
    
    unsigned int deg = 0;
    for (int e = 0; e < g->Edges; e++)
    {
        if (Graph_IsIncident(g, v, e))
        {
            deg++;
        }
    }
    return deg;
}

void Graph_DumpAdjMatrix(Graph *g, StringBuffer buffer)
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
    strcat(buffer, "\0");
}

void Graph_DumpIncidenceMatrix(Graph *g, StringBuffer buffer)
{
    memset(buffer, '\0', sizeof(StringBuffer));
    char numStr[3];
    for (int i = 0; i < g->Vertices; i++)
    {
        for (int j = 0; j < g->Edges; j++)
        {
            sprintf(numStr, "%d", g->IncidenceMatrix[i][j]);
            strcat(buffer, numStr);
            if (j + 1 < g->Edges)
            {
                strcat(buffer, " ");
            }
        }
        strcat(buffer, "\n");
    }
    strcat(buffer, "\0");
}
