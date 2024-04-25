//
//  main.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#include <raylib.h>
#include "SceneController/SceneController.h"

int main(void)
{
    
    SceneController *sc = SceneController_CreateSceneController();
    GraphSketch *gs = GraphSketch_CreateGraphSketch();
    
    InitWindow(
               SCENE_BOUNDING_BOX.width,
               SCENE_BOUNDING_BOX.height,
               "Graph Theorist Sketchpad - Benjamin Schreiber"
               );
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (GetMousePosition().x < GUI_BOUNDING_BOX.x && sc->IsInEditWeightMode)
            {
                sc->IsInEditWeightMode = false;
                continue;
            }
            
            if (sc->IsInEdgeCreationMode)
            {
                SceneController_CreateEdge(sc, gs);
            }
            
            else if (sc->IsInVertexCreationMode)
            {
                SceneController_CreateVertex(sc, gs);
            }
            
            else if (sc->IsInVertexMoveMode)
            {
                SceneController_MoveVertex(sc, gs);
            }
        }
        
        BeginDrawing();
        
        SceneController_DrawScene(sc, gs);
        
        ClearBackground(BLACK);
        
        EndDrawing();
    }
    
    CloseWindow();
    
    SceneController_FreeSceneController(sc);
    GraphSketch_FreeGraphSketch(gs);
    
    return 0;
}
