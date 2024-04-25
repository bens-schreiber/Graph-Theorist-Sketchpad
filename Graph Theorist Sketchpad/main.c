//
//  main.c
//  Frontend
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#include "raylib.h"
#include "GraphSketch/GraphSketch.h"
#include <stdio.h>

typedef struct
{
    VertexIndex v1;
    VertexIndex v2;
} DrawableEdge;

int main(void)
{
    const Rectangle screenBoundingBox = {.x = 0, .y = 0, .width = 800, .height = 450};
    
    GraphSketch *gs = GraphSketch_CreateGraphSketch();
    StringBuffer buffer;
    bool redrawGraph = true;
    
    bool edgeCreationMode = false;
    Primitive edgeCreationModeOriginPrim;
    
    DrawableEdge edges[GRAPH_MAX_PRIMITIVES];
    int edgesSize = 0;
    
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
        
        if (IsKeyPressed(KEY_W))
        {
            for (int i = 0; i < gs->Graph->Vertices; i++)
            {
                printf("%u %u\n", gs->IndexToPrimitiveMap[i].VertexIndex, gs->IndexToDrawableVertexMap[i].VertexIndex);
            }
            
            printf("\n\n");
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
                    
                    if (!gs->Graph->AdjMatrix[v1][v2])
                    {
                        edges[edgesSize++] = (DrawableEdge) { v1, v2};
                        Graph_SetAdjacent(gs->Graph, v1, v2);
                        redrawGraph = true;
                    }
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
        GraphSketch_DrawAdjMatrix(gs, buffer, redrawGraph);
        
        if (edgeCreationMode)
        {
            DrawLineV(edgeCreationModeOriginPrim.Centroid, GetMousePosition(), BLACK);
        }
        
        for (int i = 0; i < edgesSize; i++)
        {
            DrawLineV(gs->IndexToPrimitiveMap[edges[i].v1].Centroid, gs->IndexToPrimitiveMap[edges[i].v2].Centroid, BLACK);
        }
        
        ClearBackground(RAYWHITE);
        
        EndDrawing();
        redrawGraph = false;
    }
    
    CloseWindow();
    
    GraphSketch_FreeGraphSketch(gs);
    
    return 0;
}
