/*
 Modified for 2D, code from https://github.com/bens-schreiber/3D-BVH-Raycasting/tree/main/src/bvh
 */

#ifndef BVH_H
#define BVH_H

#include <stddef.h>

struct Primitive;
struct Rectangle;

/// @brief A node in a BVH tree
/// @field left: the left child of the node
/// @field right: the right child of the node
/// @field bounding_box: the bounding box enclosing the nodes primitives
/// @field primitives: the primitives enclosed by the node
/// @field primitives_size: the amount of primitives enclosed by the node (0 if non leaf node)
typedef struct BvhNode
{
    struct BvhNode *Left;
    struct BvhNode *Right;
    struct Rectangle BoundingBox;
    struct Primitive Primitives[2];
    size_t PrimitivesSize;
} BvhNode;

/// @brief A Bounding Volume Hierarchy Tree, log n collision detection
typedef struct BvhTree
{
    BvhNode *root;
} BvhTree;

/// @brief Builds a BVH tree from a list of primitives and a scene
/// @param primitives All primitives in the scene
/// @param primitives_size The amount of primitives in the scene
/// @param scene_aabb The bounding box enclosing the entire scene
/// @return A pointer to the BVH tree
BvhTree *BvhTree_CreateBvhTree(struct Primitive *primitives, size_t primitives_size, struct Rectangle scene_aabb);

BvhTree *BvhTree_CreateBvhTreeImpl(struct Primitive *primitives, size_t primitives_size, struct Rectangle bounding_box);

/// @brief Frees all the nodes in a BVH tree
/// @param tree the BVH tree to free
void BvhTree_FreeBvhTree(BvhTree *tree);

/// @brief Checks for collisions between a bounding box and a BVH tree
/// @param tree The BVH tree to check collisions with
/// @param bounding_box The BoundingBox to check collisions against the tree
/// @return 1 if there is a collision, 0 otherwise
unsigned char BvhTree_CheckCollision(const BvhTree *tree, struct Rectangle bounding_box);

/// @brief Draws all of the bounding boxes and primitives in a BVH tree
void BvhTree_Draw(const BvhTree *tree);

#endif // BVH_H
