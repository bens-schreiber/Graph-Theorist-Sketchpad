//
//  main.c
//  Frontend
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#include "raylib.h"
#include <stdio.h>

int main(void)
{
    
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
        {
            
        }
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            
        }
        
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}
