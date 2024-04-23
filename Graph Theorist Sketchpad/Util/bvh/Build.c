#include <stdlib.h>
#include <math.h>
#include "./util/longest_axis.h"
#include "raylib.h"
#include "../../Primitive/Primitive.h"
#include "Bvh.h"

static void FreeBvhNode(BvhNode *node)
{
    if (node == NULL)
    {
        return;
    }

    FreeBvhNode(node->Left);
    FreeBvhNode(node->Right);
    free(node);
}

void BvhTree_FreeBvhTree(BvhTree *tree)
{
    FreeBvhNode(tree->root);
    free(tree);
}

BvhTree *BvhTree_CreateBvhTree(Primitive *primitives, size_t primitivesSize, Rectangle sceneAabb)
{
    BvhTree *tree = malloc(sizeof(BvhTree));
    tree->root = CreateBvhTree(primitives, primitivesSize, sceneAabb);
    return tree;
}

/// @brief Expands a bounding box to contain another bounding box
/// @return The expanded bounding box containing both a and b
BoundingBox expand_aabb(BoundingBox a, BoundingBox b)
{
    BoundingBox result;

    // For each dimension, the lower bound of the result is the minimum of the lower bounds of a and b.
    result.min.x = fmin(a.min.x, b.min.x);
    result.min.y = fmin(a.min.y, b.min.y);
    result.min.z = fmin(a.min.z, b.min.z);

    // For each dimension, the upper bound of the result is the maximum of the upper bounds of a and b.
    result.max.x = fmax(a.max.x, b.max.x);
    result.max.y = fmax(a.max.y, b.max.y);
    result.max.z = fmax(a.max.z, b.max.z);

    return result;
}

/// @brief Creates a BVH node from the given primitives and bounding box
/// @return A pointer to the new BVH node
static BvhNode *BvhNode_CreateBvhNode(const Primitive *primitives, size_t primitivesSize, Rectangle boundingBox)
{
    BvhNode *newNode = malloc(sizeof(BvhNode));
    newNode->BoundingBox = boundingBox;
    newNode->Left = NULL;
    newNode->Right = NULL;
    newNode->PrimitivesSize = 0;

    if (primitivesSize == 1)
    {
        newNode->Primitives[0] = primitives[0];
        newNode->Primitives[1] = primitives[0];
        newNode->PrimitivesSize = 1;
        return newNode;
    }

    if (primitivesSize == 2)
    {
        newNode->Primitives[0] = primitives[0];
        newNode->Primitives[1] = primitives[1];
        newNode->PrimitivesSize = 2;
        return newNode;
    }

    return newNode;
}

BvhNode *CreateBvhTree(Primitive *primitives, size_t primitivesSize, Rectangle boundingBox)
{

    // If there are less than 2 primitives, the BVH node should be a leaf node, and contain the primitives.
    if (primitivesSize < 2)
    {
        return NULL;
    }

    BvhNode *newNode = BvhNode_CreateBvhNode(primitives, primitivesSize, boundingBox);

    // Sort the primitivess by the longest axis.
    qsort(primitives, primitivesSize, sizeof(Primitive), compare_by_longest_axis(boundingBox));

    // Find the median of the primitivess.
    size_t median = primitivesSize / 2;
    Primitive medianPrimitive = primitives[median];

    // Calculate the left AABB.
    // It should contain all primitivess from 0 to median.
    Rectangle leftBoundingBox = Primitive_GetBoundingBox(&medianPrimitive);
    for (size_t i = 0; i <= median; i++)
    {
        leftBoundingBox = expand_aabb(leftBoundingBox, primitive_get_bounding_box(&primitives[i]));
    }

    // Calculate the right AABB.
    // It should contain all primitivess from median to primitives_size.
    BoundingBox right_aabb = primitive_get_bounding_box(&medianPrimitive);
    for (size_t i = median + 1; i < primitives_size; i++)
    {
        right_aabb = expand_aabb(right_aabb, primitive_get_bounding_box(&primitives[i]));
    }

    // Recurse on the left and right AABBs.
    new_node->left = bvh_tree_create_impl(primitives, median, leftBoundingBox);
    new_node->right = bvh_tree_create_impl(primitives + median, primitives_size - median, right_aabb);

    return new_node;
}
