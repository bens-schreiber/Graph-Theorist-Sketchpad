//
//  main.c
//  Frontend
//
//  Created by Benjamin Schreiber on 4/22/24.
//

#include "raylib.h"
#include "Bvh/BvhTree.h"
#include "Bvh/Primitive/Primitive.h"

int main(void)
{
    
    const int screenWidth = 800;
    const int screenHeight = 450;
    int size = 0;
    Primitive p[100] = {};
    
    BvhTree *bvht = NULL;
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        // TODO: Update your variables here
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            p[size++] = Primitive_CreatePrimitive(GetMousePosition());
            if (bvht != NULL)
            {
                BvhTree_FreeBvhTree(bvht);
            }
            
            bvht = BvhTree_CreateBvhTree(p, size, (Rectangle) {0, 0, screenWidth, screenHeight});
        }
        
        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        BvhTree_Draw(bvht);
        for (int i = 0; i < size; i++)
        {
            Primitive_Draw(p + i);
        }
        
        EndDrawing();
        
        continue;
    }
    CloseWindow();
    
    return 0;
}
