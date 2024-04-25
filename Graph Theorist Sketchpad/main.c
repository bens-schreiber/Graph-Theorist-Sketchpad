//
//  main.c
//  Frontend
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "GraphSketch/GraphSketch.h"
#include <stdio.h>

int main(void)
{
    const Rectangle screenBoundingBox = {.x = 0, .y = 0, .width = 800, .height = 450};
    const Rectangle graphSketchBoundingBox = {.x = 0, .y = 0, .width = 500, .height = screenBoundingBox.height };
    const Rectangle guiBoundingBox = {.x = 500, .y = 0, .width = screenBoundingBox.width - 500, .height = screenBoundingBox.height};
    
    GraphSketch *gs = GraphSketch_CreateGraphSketch();
    StringBuffer adjBuffer = "";
    StringBuffer incidenceBuffer = "";
    
    bool edgeCreationMode = false;
    Primitive edgeCreationModeOriginPrim;
    
    bool showBvhTree = false;
    bool showAdjMatrix = false;
    bool showIncidenceMatrix = false;
    bool showVertices = true;
    
    InitWindow(screenBoundingBox.width, screenBoundingBox.height, "raylib [core] example - basic window");
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            Vector2 mousePosition = GetMousePosition();
            if (mousePosition.x < (graphSketchBoundingBox.width - GRAPH_VERTEX_RADIUS))
            {
                GraphSketch_AddVertex(gs, GetMousePosition(), graphSketchBoundingBox);
                Graph_DumpAdjMatrix(gs->Graph, adjBuffer);
            }
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
                    
                    Graph_DumpAdjMatrix(gs->Graph, adjBuffer);
                    Graph_DumpIncidenceMatrix(gs->Graph, incidenceBuffer);
                    edgeCreationMode = false;
                } else
                {
                    edgeCreationMode = true;
                    edgeCreationModeOriginPrim = gs->IndexToPrimitiveMap[vi];
                }
            }
        }
        
        BeginDrawing();
        
        if (showVertices) GraphSketch_DrawVertices(gs);
        
        if (showAdjMatrix) GraphSketch_DrawAdjMatrix(gs, adjBuffer);
        
        if (showIncidenceMatrix) GraphSketch_DrawIncidenceMatrix(gs, incidenceBuffer);
        
        if (showBvhTree) BvhTree_Draw(gs->BvhTree);
        
        DrawRectangleRec(guiBoundingBox, Fade(LIGHTGRAY, 0.3f));
        GuiCheckBox((Rectangle){ 600, 320, 20, 20 }, "Show BVH Tree", &showBvhTree);
        GuiCheckBox((Rectangle){ 600, 350, 20, 20 }, "Show Adjacency Matrix", &showAdjMatrix);
        GuiCheckBox((Rectangle){ 600, 410, 20, 20 }, "Show Incidence Matrix", &showIncidenceMatrix);
        GuiCheckBox((Rectangle){ 600, 380, 20, 20 }, "Show Vertices", &showVertices);
        
        if (edgeCreationMode)
        {
            DrawLineV(edgeCreationModeOriginPrim.Centroid, GetMousePosition(), BLACK);
        }
        
        GraphSketch_DrawEdges(gs);
        
        ClearBackground(RAYWHITE);
        
        EndDrawing();
    }
    
    CloseWindow();
    
    GraphSketch_FreeGraphSketch(gs);
    
    return 0;
}
