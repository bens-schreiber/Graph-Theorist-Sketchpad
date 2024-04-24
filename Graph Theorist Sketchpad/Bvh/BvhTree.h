//
//  BvhTree.h
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/23/24.
//

#ifndef BvhTree_h
#define BvhTree_h

#include "Primitive/Primitive.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct BvhNode
{
    Rectangle BoundingBox;
    Primitive Primitives[2];
    size_t Size;
    struct BvhNode *Left;
    struct BvhNode *Right;
} BvhNode;

typedef struct
{
    BvhNode *root;
} BvhTree;

/// Creates a Bvh Tree from the given primitives confined to the scene bounding box
BvhTree *BvhTree_CreateBvhTree(Primitive *primitives, size_t size, Rectangle sceneBoundingBox);

/// Recurisvely frees all memory of the Bvh Tree
void BvhTree_FreeBvhTree(BvhTree *bvht);

/// Checks if a boundingBox collides with any other boundingBox in the Bvh Tree
bool BvhTree_CheckCollision(const BvhTree *bvht, Rectangle boundingBox);

/// Recursively draws the bounding boxes of all BvhNodes
void BvhTree_Draw(const BvhTree *bvht);

#endif /* BvhTree_h */
