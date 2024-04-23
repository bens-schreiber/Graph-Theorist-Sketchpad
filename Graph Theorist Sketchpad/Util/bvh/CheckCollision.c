#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"
#include "../../Primitive/Primitive.h"
#include "Bvh.h"

#define IsLeaf(node) (node->left == NULL && node->right == NULL)

// DFS, check each bounding box and primitives if they exist
static unsigned char CheckCollision(const BvhNode *node, Rectangle boundingBox)
{
    if (node == NULL)
    {
        return 0;
    }

    // If the bounding boxes intersect, this node is a candidate for collision
    if (CheckCollisionRecs(node->BoundingBox, boundingBox))
    {
        // Only a leaf will have primitives to check
        if (IsLeaf(<#node#>))
        {
            // Check each primitive in the leaf node
            for (size_t i = 0; i < node->PrimitivesSize; i++)
            {
                // If the primitive intersects the bounding box, there is a collision
                if (CheckCollisionRecs(Primitive_GetBoundingBox(&node->Primitives[i]), boundingBox))
                {
                    return 1;
                }
            }
        }
        return CheckCollision(node->Left, boundingBox) || CheckCollision(node->Right, boundingBox);
    }
    return 0;
}

unsigned char BvhTree_CheckCollision(const BvhTree *tree, Rectangle boundingBox)
{
    return CheckCollision(tree->root, boundingBox);
}
