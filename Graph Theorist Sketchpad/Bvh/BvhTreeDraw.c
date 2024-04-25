//
//  BvhTree.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/23/24.
//

#include "BvhTree.h"

void _Draw(const BvhNode *bvhn)
{
    if (bvhn == NULL) return;
    
    // Draw a border around the bounding volume
    DrawRectangleLines(
                       bvhn->BoundingBox.x,
                       bvhn->BoundingBox.y,
                       bvhn->BoundingBox.width,
                       bvhn->BoundingBox.height,
                       RED);
    
    for (int i = 0; i < bvhn->Size; i++)
    {
        Primitive_Draw(&bvhn->Primitives[i]);
    }
    
    // Recurse
    _Draw(bvhn->Left);
    _Draw(bvhn->Right);
}

void BvhTree_Draw(const BvhTree *bvht)
{
    if (bvht == NULL) return;
    _Draw(bvht->root);
}
