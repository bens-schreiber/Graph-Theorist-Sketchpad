//
//  BvhCheckCollision.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/23/24.
//

#include "BvhTree.h"

#define IsLeaf(node) (node->Left == NULL && node->Right == NULL)

// DFS, check each bounding box and primitives if they exist
Primitive *_CheckCollisionImpl(BvhNode *bvhn, Rectangle boundingBox)
{
    if (bvhn == NULL)
    {
        return NULL;
    }
    
    // If the bounding boxes intersect, this node is a candidate for collision
    if (CheckCollisionRecs(bvhn->BoundingBox, boundingBox))
    {
        // Only a leaf will have primitives to check
        if (IsLeaf(bvhn))
        {
            // Check each primitive in the leaf node
            for (size_t i = 0; i < bvhn->Size; i++)
            {
                // If the primitive intersects the bounding box, there is a collision
                if (CheckCollisionRecs(bvhn->Primitives[i].BoundingBox, boundingBox))
                {
                    return &bvhn->Primitives[i];
                }
            }
        }
        Primitive *left = _CheckCollisionImpl(bvhn->Left, boundingBox);
        if (left != NULL)
        {
            return left;
        }
        
        Primitive *right = _CheckCollisionImpl(bvhn->Right, boundingBox);
        if (right != NULL)
        {
            return right;
        }
        
    }
    return NULL;
}

Primitive *BvhTree_CheckCollision(BvhTree *bvht, Rectangle boundingBox)
{
    if (bvht == NULL) return NULL;
    return _CheckCollisionImpl(bvht->root, boundingBox);
}
