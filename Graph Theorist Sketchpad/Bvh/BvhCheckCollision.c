//
//  BvhCheckCollision.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/23/24.
//

#include "BvhTree.h"

#define IsLeaf(node) (node->Left == NULL && node->Right == NULL)
#define NO_COLLISION -1

// DFS, check each bounding box and primitives if they exist
int _CheckCollisionImpl(BvhNode *bvhn, Rectangle boundingBox)
{
    if (bvhn == NULL)
    {
        return NO_COLLISION;
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
                    return bvhn->Primitives[i].VertexIndex;
                }
            }
        }
        int left = _CheckCollisionImpl(bvhn->Left, boundingBox);
        if (left != NO_COLLISION)
        {
            return left;
        }
        
        unsigned int right = _CheckCollisionImpl(bvhn->Right, boundingBox);
        if (right != NO_COLLISION)
        {
            return right;
        }
        
    }
    return NO_COLLISION;
}

int BvhTree_CheckCollision(const BvhTree *bvht, Rectangle boundingBox)
{
    if (bvht == NULL) return -1;
    return _CheckCollisionImpl(bvht->root, boundingBox);
}
