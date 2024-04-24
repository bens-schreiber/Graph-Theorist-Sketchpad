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
    const int size = 3;
    Primitive p[size] = {};
    p[0] = Primitive_CreatePrimitive((Vector2) {30,100});
    p[1] = Primitive_CreatePrimitive((Vector2) {100,100});
    p[2] = Primitive_CreatePrimitive((Vector2) {150, 150});
//    p[3] = Primitive_CreatePrimitive((Vector2) {280, 280});
//    p[4] = Primitive_CreatePrimitive((Vector2) {400, 400});
    
    BvhTree *bvht = BvhTree_CreateBvhTree(p, size, (Rectangle) {10,10,200,200});
    
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    
    SetTargetFPS(60);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        // TODO: Update your variables here
        
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
