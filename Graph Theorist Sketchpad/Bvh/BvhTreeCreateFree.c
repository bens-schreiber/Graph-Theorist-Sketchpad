//
//  BvhTreeCreateFree.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/23/24.
//

#include "BvhTree.h"
#include "Util/LongestAxis.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>

/// Creates a new BvhNode. Requires two primitives in the list.
static BvhNode *_BvhNode_CreateBvhNode(const Primitive *primitives, Rectangle boundingBox)
{
    BvhNode *bvhn = malloc(sizeof(BvhNode));
    bvhn->BoundingBox   = boundingBox;
    bvhn->Left          = NULL;
    bvhn->Right         = NULL;
    bvhn->Size          = 2;
    bvhn->Primitives[0] = primitives[0];
    bvhn->Primitives[1] = primitives[1];
    return bvhn;
}

/// - Returns: An expanded bounding box that encloses both a and b
static Rectangle _ExpandBoundingBox(Rectangle a, Rectangle b)
{
    // Calculate the minimum and maximum x and y coordinates
    float minX = fmin(a.x, b.x);
    float minY = fmin(a.y, b.y);
    int maxX = fmax(a.x + a.width, b.x + b.width);
    int maxY = fmax(a.y + a.height, b.y + b.height);
    
    return (Rectangle) {.x = minX, .y = minY, .width = maxX - minX, .height = maxY - minY};
}

static BvhNode *_CreateBvhTreeImpl(Primitive *primitives, size_t size, Rectangle boundingBox)
{
    if (size < 1) return NULL;
    
    BvhNode *bvhn = _BvhNode_CreateBvhNode(primitives, boundingBox);
    
    if (size < 2)
    {
        bvhn->Size = size;
        return bvhn;
    }
    
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
    
    // Calculate the right BoundingBox
    // It should contain all primitivess from median to primitives_size.
    Rectangle right = medianPrimitive.BoundingBox;
    for (size_t i = median + 1; i < size; i++)
    {
        right = _ExpandBoundingBox(right, primitives[i].BoundingBox);
    }
    
    // Recurse on the left and right primitives
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
