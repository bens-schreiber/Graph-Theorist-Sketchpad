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
    StringBuffer buffer;
    bool redrawGraph = true;
    
    InitWindow(screenBoundingBox.width, screenBoundingBox.height, "raylib [core] example - basic window");
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            GraphSketch_AddVertex(gs, GetMousePosition(), screenBoundingBox);
            redrawGraph = true;
        }
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && gs->BvhTree != NULL)
        {
            Rectangle mouseBoundingBox = Primitive_CreatePrimitiveWithSize(GetMousePosition(), 0, 3).BoundingBox;
            Primitive *p = BvhTree_CheckCollision(gs->BvhTree, mouseBoundingBox);
            if (p != NULL)
            {
                printf("%s\n", gs->IndexToDrawableVertexMap[p->VertexIndex].Label);
            }
        }
        
        BeginDrawing();
        
        GraphSketch_DrawVertices(gs);
        GraphSketch_DrawAdjMatrix(gs, buffer, redrawGraph);
        
        ClearBackground(RAYWHITE);
        
        EndDrawing();
        redrawGraph = false;
    }
    
    CloseWindow();
    
    GraphSketch_FreeGraphSketch(gs);
    
    return 0;
}
