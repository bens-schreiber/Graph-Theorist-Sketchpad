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
    Graph_AddVerticesWithSelfLoops_PopulatesIncidenceMatrixAndAdjacencyMatrix();
    Graph_AddVertexAdjacency_VerticesAreAdjacentAndIncident();
    Graph_VertexDegree_ReturnsCorrectDegree();
    Graph_KruskalsAlgorithm_CorrectlyDeterminesMST();
    Graph_KruskalsAlgorithmWithPathGraph_CorrectlyDeterminesMST();
    Graph_KruskalsAlgorithmWithWeights_CorrectlyDeterminesMST();
    Graph_KruskalsAlgorithmWithWeightsAndCycles_CorrectlyDeterminesMST();
    Graph_KruskalsAlgorithmWithNoEdges_NoMST();
    
    
    // Graph Sketch Tests
    GraphSketch_CreateNew_SetsGraphWithNoVerticesAndNullBvhTree();
    GraphSketch_AddVertex_CreatesNewGraphVertexAndBvhTreeAndPrimitiveAndDrawable();
    GraphSketch_BvhTreeCollision_DoesCollideWithItsOwnBoundingBox();
    GraphSketch_BvhTreeCollision_DoesNotCollideOutsideItsOwnBoundingBox();
    
    return 0;
}
