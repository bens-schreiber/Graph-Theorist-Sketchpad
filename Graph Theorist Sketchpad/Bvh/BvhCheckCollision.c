//
//  BvhCheckCollision.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/23/24.
//

#include "BvhTree.h"

#define IsLeaf(node) (node->Left == NULL && node->Right == NULL)

// DFS, check each bounding box and primitives if they exist
bool _CheckCollisionImpl(const BvhNode *bvhn, Rectangle boundingBox)
{
    if (bvhn == NULL)
    {
        return false;
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
                    return true;
                }
            }
        }
        return _CheckCollisionImpl(bvhn->Left, boundingBox) || _CheckCollisionImpl(bvhn->Right, boundingBox);
    }
    return 0;
}

bool BvhTree_CheckCollision(const BvhTree *bvht, Rectangle boundingBox)
{
    if (bvht == NULL) return false;
    return _CheckCollisionImpl(bvht->root, boundingBox);
}
