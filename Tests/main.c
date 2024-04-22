//
//  main.c
//  Tests
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#include <stdio.h>
#include "GraphTests.h"

int main(int argc, const char * argv[]) {
    
    // Graph Tests
    Graph_CreateNew_SetsAllValuesToZero();
    Graph_AddMultipleVertices_SetsPopulatesMatrix();
    Graph_SetAdjacency_SetsAdjMatrix();
    
    return 0;
}
