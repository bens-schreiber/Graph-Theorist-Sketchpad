//
//  main.c
//  Frontend
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#include "raylib.h"
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
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        // TODO: Update your variables here
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            u_short size = Graph_AddVertex(g);
            p[size] = Primitive_CreatePrimitive(GetMousePosition());
            gv[size] = GraphVertex_CreateGraphVertex(size, "Default Label", RED);
            if (bvht != NULL)
            {
                BvhTree_FreeBvhTree(bvht);
            }
            
            bvht = BvhTree_CreateBvhTree(p, size + 1, (Rectangle) {0, 0, screenWidth, screenHeight});
        }
        
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        BvhTree_Draw(bvht);
        for (int i = 0; i < g->Vertices; i++)
        {
            GraphVertex_Draw(gv + i, p + gv[i].Index);
        }
        
        EndDrawing();
        
        continue;
    }
    CloseWindow();
    
    return 0;
}
