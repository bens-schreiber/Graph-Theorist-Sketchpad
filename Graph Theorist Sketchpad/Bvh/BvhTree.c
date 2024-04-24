//
//  BvhTree.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/23/24.
//

#include "BvhTree.h"
#include "Util/LongestAxis.h"
#include <stdlib.h>
#include <assert.h>

static BvhNode *_BvhNode_CreateBvhNode(const Primitive *primitives, size_t size, Rectangle boundingBox)
{
    BvhNode *bvhn = malloc(sizeof(BvhNode));
    bvhn->BoundingBox   = boundingBox;
    bvhn->Left          = NULL;
    bvhn->Right         = NULL;
    bvhn->Size          = size;
    bvhn->Primitives[0] = primitives[0];
    bvhn->Primitives[1] = primitives[1];
    
    return bvhn;
}

/// Expands the a bounding box to enclose both a and b
static Rectangle _ExpandBoundingBox(Rectangle a, Rectangle b)
{
    // Calculate the minimum and maximum x and y coordinates
    int minX = (a.x < b.x) ? a.x : b.x;
    int minY = (a.y < b.y) ? a.y : b.y;
    int maxX = (a.x + a.width > b.x + b.width) ? a.x + a.width : b.x + b.width;
    int maxY = (a.y + a.height > b.y + b.height) ? a.y + a.height : b.y + b.height;
    
    Rectangle result;

    // Calculate the width and height of the smallest enclosing rectangle
    result.x = minX;
    result.y = minY;
    result.width = maxX - minX;
    result.height = maxY - minY;
    
    return result;
}

static BvhNode *_CreateBvhTreeImpl(Primitive *primitives, size_t size, Rectangle boundingBox)
{
    
    if (size < 2)
    {
        return NULL;
    }
    
    BvhNode *bvhn = _BvhNode_CreateBvhNode(primitives, size, boundingBox);
    
    if (size == 2)
    {
        Rectangle a = bvhn->Primitives[0].BoundingBox;
        Rectangle b = bvhn->Primitives[1].BoundingBox;
        bvhn->BoundingBox = _ExpandBoundingBox(a,b);
        return bvhn;
    }
    
    // Sort the primitivess by the longest axis.
    qsort(primitives, size, sizeof(Primitive), LongestAxis_CompareByLongestAxis(boundingBox));
    
    // Find the median of the primitivess.
    size_t median = size / 2;
    Primitive medianPrimitive = primitives[median];
    
    // Calculate the left BoundingBox
    // It should contain all primitivess from 0 to median.
    Rectangle left = medianPrimitive.BoundingBox;
    for (size_t i = 0; i <= median; i++)
    {
        left = _ExpandBoundingBox(left, primitives[i].BoundingBox);
    }
    
    // Calculate the right AABB.
    // It should contain all primitivess from median to primitives_size.
    Rectangle right = medianPrimitive.BoundingBox;
    for (size_t i = median + 1; i < size; i++)
    {
        right = _ExpandBoundingBox(right, primitives[i].BoundingBox);
    }
    
    // Recurse on the left and right AABBs.
    bvhn->Left = _CreateBvhTreeImpl(primitives, median + 1, left);
    bvhn->Right = _CreateBvhTreeImpl(primitives + median, size - median, right);
    
    return bvhn;
    
}

BvhTree *BvhTree_CreateBvhTree(Primitive *primitives, size_t size, Rectangle sceneBoundingBox)
{
    BvhTree *bvht = malloc(sizeof(BvhTree));
    bvht->root = _CreateBvhTreeImpl(primitives, size, sceneBoundingBox);
    return bvht;
}

void BvhNode_FreeBvhNode(BvhNode *bn)
{
    if (bn == NULL)
    {
        return;
    }
    
    BvhNode_FreeBvhNode(bn->Left);
    BvhNode_FreeBvhNode(bn->Right);
    bn->Left = NULL;
    bn->Right = NULL;
    free(bn);
}

void BvhTree_FreeBvhTree(BvhTree *bvht)
{
    assert(bvht != NULL);
    BvhNode_FreeBvhNode(bvht->root);
    bvht->root = NULL;
    free(bvht);
}

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
    return _CheckCollisionImpl(bvht->root, boundingBox);
}

void _Draw(const BvhNode *bvhn)
{
    if (bvhn == NULL) return;
    DrawRectangleLines(
                       bvhn->BoundingBox.x,
                       bvhn->BoundingBox.y,
                       bvhn->BoundingBox.width,
                       bvhn->BoundingBox.height,
                       BLACK);
    
    _Draw(bvhn->Left);
    _Draw(bvhn->Right);
}

void BvhTree_Draw(const BvhTree *bvht)
{
    _Draw(bvht->root);
}
