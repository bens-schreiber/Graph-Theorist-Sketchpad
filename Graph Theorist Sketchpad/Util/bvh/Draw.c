#include <stdlib.h>
#include "raylib.h"
#include "../../Primitive/Primitive.h"
#include "Bvh.h"

static void Draw(const BvhNode *node)
{
    if (node == NULL)
    {
        return;
    }

    DrawRectangleRec(node->BoundingBox, BLACK);

    for (size_t i = 0; i < node->PrimitivesSize; i++)
    {
        Rectangle rec = Primitive_GetBoundingBox(&node->Primitives[i]);
        DrawRectangleRec(rec, BLACK);
        
    }

    Draw(node->Left);
    Draw(node->Right);
}

void BvhTree_Draw(const BvhTree *tree)
{
    Draw(tree->root);
}
