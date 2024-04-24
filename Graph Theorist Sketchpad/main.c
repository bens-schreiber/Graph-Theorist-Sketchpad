//
//  main.c
//  Frontend
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#include "raylib.h"
#include <stdio.h>
#include "Bvh/BvhTree.h"
#include "Bvh/Primitive/Primitive.h"
#include "../Graph/Graph.h"
#include "Graph/GraphVertex.h"

int main(void)
{
    
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    Primitive p[100] = {};
    GraphVertex gv[100] = {};
    BvhTree *bvht = NULL;
    Graph *g = Graph_CreateGraph();
    
    char buffer[0xFFF] = "";
    
    u_int graphHash = g->Vertices;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            u_short index = Graph_AddVertex(g);
            p[index] = Primitive_CreatePrimitive(GetMousePosition());
            gv[index] = GraphVertex_CreateGraphVertex(index, "Default Label", RED);
            if (bvht != NULL)
            {
                BvhTree_FreeBvhTree(bvht);
            }
            
            bvht = BvhTree_CreateBvhTree(p, index + 1, (Rectangle) {0, 0, screenWidth, screenHeight});
        }
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Primitive p = Primitive_CreatePrimitiveWithSize(GetMousePosition(), 3);
            if (BvhTree_CheckCollision(bvht, p.BoundingBox))
            {
                printf("COLLISION!!!");
            }
        }
        
        if (graphHash != g->Vertices)
        {
            Graph_DumpString(g, buffer);
            graphHash = g->Vertices;
        }
        
        DrawText(buffer, 10, 10, 20, BLACK);
        
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        // TODO: option to show Bvh tree
        BvhTree_Draw(bvht);
        for (int i = 0; i < g->Vertices; i++)
        {
            GraphVertex_Draw(gv + i, p + gv[i].Index);
        }
        
        EndDrawing();
    }
    CloseWindow();
    
    return 0;
}
