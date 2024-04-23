//
//  main.c
//  Frontend
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#include "raylib.h"
#include "Bvh/Primitive.h"

int main(void)
{
    
    const int screenWidth = 800;
    const int screenHeight = 450;
    Primitive p;
    int isPSet = 0;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        // TODO: Update your variables here
        
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            isPSet = 1;
            p = Primitive_CreatePrimitive(GetMousePosition());
        }
        
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        if (isPSet)
        {
            Primitive_Draw(&p);
        }
        
        EndDrawing();
    }
    CloseWindow();
    
    return 0;
}
