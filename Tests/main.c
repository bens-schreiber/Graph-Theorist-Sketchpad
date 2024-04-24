//
//  main.c
//  Tests
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#include <stdio.h>
#include "GraphTests.h"
#include "GraphSketchTests.h"

int main(int argc, const char * argv[]) {
    
    // Graph Tests
    Graph_CreateNew_SetsAllValuesToZero();
    Graph_AddMultipleVertices_PopulatesMatrixDiagonal();
    Graph_SetAdjacency_SetsVerticesToAdjacent();
    Graph_RemoveEdge_SetsVerticesToExistsNoAdjacency();
    Graph_RemoveVertex1_RemovesRowAndColumnFromAdjMatrix();
    Graph_RemoveVertexOffset_RemovesRowAndColumnFromAdjMatrix();
    Graph_RemoveVertexWithSelfLoop_RemovesRowAndColumnFromAdjMatrix();
    Digraph_SetAdjacency_GoesOneWay();
    Graph_VertexDegree_ReturnsCorrectDegree();
    Graph_WeightedGraph_ReturnsCorrectWeight();
    
    // Graph Sketch Tests
    GraphSketch_CreateNew_SetsGraphWithNoVerticesAndNullBvhTree();
    GraphSketch_AddVertex_CreatesNewGraphVertexAndBvhTreeAndPrimitiveAndDrawable();
    GraphSketch_BvhTreeCollision_DoesCollideWithItsOwnBoundingBox();
    GraphSketch_BvhTreeCollision_DoesNotCollideOutsideItsOwnBoundingBox();
    
    
    return 0;
}
