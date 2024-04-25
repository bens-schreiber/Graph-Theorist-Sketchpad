//
//  main.c
//  Frontend
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#include "raylib.h"
#include "GraphSketch/GraphSketch.h"
#include <stdio.h>

int main(void)
{
    const Rectangle screenBoundingBox = {.x = 0, .y = 0, .width = 800, .height = 450};
    
    GraphSketch *gs = GraphSketch_CreateGraphSketch();
    StringBuffer adjBuffer;
    StringBuffer incidenceBuffer;
    bool remakeMatrices = true;
    
    bool edgeCreationMode = false;
    Primitive edgeCreationModeOriginPrim;
    
    InitWindow(screenBoundingBox.width, screenBoundingBox.height, "raylib [core] example - basic window");
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            GraphSketch_AddVertex(gs, GetMousePosition(), screenBoundingBox);
            remakeMatrices = true;
        }
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gs->BvhTree != NULL)
        {
            Rectangle mouseBoundingBox = Primitive_CreatePrimitiveWithSize(GetMousePosition(), 0, 3).BoundingBox;
            int vi = BvhTree_CheckCollision(gs->BvhTree, mouseBoundingBox);
            if (vi >= 0)
            {
                if (edgeCreationMode)
                {
                    VertexIndex v1 = edgeCreationModeOriginPrim.VertexIndex;
                    VertexIndex v2 = vi;
                    GraphSketch_AddEdge(gs, v1, v2);
                    
                    remakeMatrices = true;
                    edgeCreationMode = false;
                } else
                {
                    edgeCreationMode = true;
                    edgeCreationModeOriginPrim = gs->IndexToPrimitiveMap[vi];
                }
            }
        }
        
        BeginDrawing();
        
        GraphSketch_DrawVertices(gs);
        GraphSketch_DrawAdjMatrix(gs, adjBuffer, remakeMatrices);
        GraphSketch_DrawIncidenceMatrix(gs, incidenceBuffer, remakeMatrices);
        BvhTree_Draw(gs->BvhTree);
        
        if (edgeCreationMode)
        {
            DrawLineV(edgeCreationModeOriginPrim.Centroid, GetMousePosition(), BLACK);
        }
        
        GraphSketch_DrawEdges(gs);
        
        ClearBackground(RAYWHITE);
        
        EndDrawing();
        remakeMatrices = false;
    }
    
    CloseWindow();
    
    GraphSketch_FreeGraphSketch(gs);
    
    return 0;
}
