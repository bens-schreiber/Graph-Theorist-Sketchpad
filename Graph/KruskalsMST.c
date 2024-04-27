//
//  KruskalsMST.c
//  Graph
//
//  Created by Benjamin Schreiber on 4/27/24.
//

#include "Graph.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    int parent;
    int rank;
} UnionFind;

int _Find(UnionFind *sets, int i) 
{
    if (sets[i].parent != i)
    {
        sets[i].parent = _Find(sets, sets[i].parent);
    }
    return sets[i].parent;
}

// Union operation in Union Find
void _UnionSets(UnionFind *sets, int x, int y) 
{
    int xRoot = _Find(sets, x);
    int yRoot = _Find(sets, y);
    
    if (sets[xRoot].rank < sets[yRoot].rank)
    {
        sets[xRoot].parent = yRoot;
        return;
    }
    if (sets[xRoot].rank > sets[yRoot].rank)
    {
        sets[yRoot].parent = xRoot;
        return;
    }
    
    sets[yRoot].parent = xRoot;
    sets[xRoot].rank++;
}

typedef struct
{
    int Weight;
    EdgeIndex E;
    signed int V1;
    signed int V2;
} EdgeInformation;

int _CompareEdgeInformation(const void *a, const void *b)
{
    EdgeInformation *eiA = (EdgeInformation*) a;
    EdgeInformation *eiB = (EdgeInformation*) b;
    return eiA->Weight - eiB->Weight;
}

#define NO_VERTEX -1
#define MAX(a, b) ((a) > (b) ? (a) : (b))
void Graph_MinSpanningTree(Graph *g, EdgeIndex edges[GRAPH_MAX_SIZE]) 
{
    assert(g != NULL);
    
    // Initialize Union Find sets
    UnionFind sets[g->Vertices];
    for (int i = 0; i < g->Vertices; i++) 
    {
        sets[i].parent = i;
        sets[i].rank = 0;
    }
    
    // Gather edge list with helpful information
    EdgeInformation edgeIndexToEdgeInformation[g->Edges];
    for (EdgeIndex ei = 0; ei < g->Edges; ei++) 
    {
        // V2 as NO_VERTEX indicates a self loop
        EdgeInformation ef = {.Weight = 0, .E = ei, .V1 = NO_VERTEX, .V2 = NO_VERTEX};
        
        for (VertexIndex vi = 0; vi < g->Vertices; vi++)
        {
            if (g->IncidenceMatrix[vi][ei] == INCIDENCE_MATRIX_NO_VALUE) continue;
            if (ef.V1 == NO_VERTEX) 
            {
                ef.Weight = MAX(ef.Weight, abs(g->IncidenceMatrix[vi][ei]));
                ef.V1 = vi;
            } else if (ef.V2 == NO_VERTEX) {
                ef.Weight = MAX(ef.Weight, abs(g->IncidenceMatrix[vi][ei]));
                ef.V2 = vi;
            }
            if (ef.V1 != NO_VERTEX && ef.V2 != NO_VERTEX) {
                edgeIndexToEdgeInformation[ei] = ef;
                break;
            }
        }
        edgeIndexToEdgeInformation[ei] = ef;
    }
    
    // Sort by weight
    qsort(edgeIndexToEdgeInformation, g->Edges, sizeof(EdgeInformation), _CompareEdgeInformation);
    
    int edgeListIndex = 0;
    for (int i = 0; i < g->Edges; i++) 
    {
        if (edgeListIndex >= g->Vertices - 1) break; // we've reached the MPT
        EdgeInformation ef = edgeIndexToEdgeInformation[i];
        if (ef.V2 == NO_VERTEX) continue; // self loops get us nowhere
        int root1 = _Find(sets, ef.V1);
        int root2 = _Find(sets, ef.V2);
        if (root1 != root2) 
        {
            edges[edgeListIndex++] = ef.E;
            _UnionSets(sets, root1, root2);
        }
    }
    
    edges[edgeListIndex] = MST_NO_EDGE;
}

