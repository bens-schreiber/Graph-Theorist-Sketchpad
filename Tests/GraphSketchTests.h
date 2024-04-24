//
//  GraphSketchTests.h
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/24/24.
//

#ifndef GraphSketchTests_h
#define GraphSketchTests_h

#include <assert.h>
#include "../Graph Theorist Sketchpad/GraphSketch/GraphSketch.h"

#define SCENE_BOUNDING_BOX ((Rectangle) {.x = 0, .y = 0, .width = 800, .height = 450})

#define TEST static inline void
#define GRAPH_SKETCH_TEST_CASE(name) TEST name(void) { _Setup_GraphSketch_Tests(_##name); }

static unsigned int _checkCollisionRecsCallCount = 0;
bool CheckCollisionRecs(Rectangle a, Rectangle b)
{
    _checkCollisionRecsCallCount++;
    return a.x < b.x + b.width &&
    a.x + a.width > b.x &&
    a.y < b.y + b.height &&
    a.y + a.height > b.y;
}

void DrawRectangleRec(Rectangle _, Color __) {}

static void _Setup_GraphSketch_Tests(void (*test)(GraphSketch*))
{
    GraphSketch *gs = GraphSketch_CreateGraphSketch();
    assert(gs != NULL);
    test(gs);
    GraphSketch_FreeGraphSketch(gs);
    _checkCollisionRecsCallCount = 0;
}

TEST _GraphSketch_CreateNew_SetsGraphWithNoVerticesAndNullBvhTree(GraphSketch *gs)
{
    // Assert
    assert(gs->BvhTree == NULL);
    assert(gs->Graph != NULL);
    assert(gs->Graph->Vertices == 0);
}
GRAPH_SKETCH_TEST_CASE(GraphSketch_CreateNew_SetsGraphWithNoVerticesAndNullBvhTree)


TEST _GraphSketch_AddVertex_CreatesNewGraphVertexAndBvhTreeAndPrimitiveAndDrawable(GraphSketch *gs)
{
    // Arrange
    const Vector2 pos = {0,0};
    
    // Act
    VertexIndex vi = GraphSketch_AddVertex(gs, pos, SCENE_BOUNDING_BOX);
    Vector2 centroid = gs->IndexToPrimitiveMap[vi].Centroid;
    
    // Assert
    assert(gs->Graph->Vertices == 1);
    assert(gs->BvhTree != NULL);
    assert(centroid.x == pos.x && centroid.y == pos.y);
    assert(gs->IndexToDrawableVertexMap[vi].VertexIndex == vi);
}
GRAPH_SKETCH_TEST_CASE(GraphSketch_AddVertex_CreatesNewGraphVertexAndBvhTreeAndPrimitiveAndDrawable)


TEST _GraphSketch_BvhTreeCollision_DoesCollideWithItsOwnBoundingBox(GraphSketch *gs)
{
    // Arrange
    const Vector2 pos = {100,100};
    VertexIndex vi = GraphSketch_AddVertex(gs, pos, SCENE_BOUNDING_BOX);
    
    // Act
    Primitive *collision = BvhTree_CheckCollision(gs->BvhTree, gs->IndexToPrimitiveMap[vi].BoundingBox);
    
    // Assert
    assert(collision != NULL);
    assert(_checkCollisionRecsCallCount == 2);
}
GRAPH_SKETCH_TEST_CASE(GraphSketch_BvhTreeCollision_DoesCollideWithItsOwnBoundingBox)


TEST _GraphSketch_BvhTreeCollision_DoesNotCollideOutsideItsOwnBoundingBox(GraphSketch *gs)
{
    // Arrange
    const Vector2 pos = {100,100};
    VertexIndex vi = GraphSketch_AddVertex(gs, pos, SCENE_BOUNDING_BOX);
    
    // Act
    Rectangle boundingBox = gs->IndexToPrimitiveMap[vi].BoundingBox;
    Rectangle noCollisionBox = { .x = boundingBox.x - 2, .y = boundingBox.y - 2, .width = 1, .height = 1 };
    Primitive *collision = BvhTree_CheckCollision(gs->BvhTree, noCollisionBox);
    
    // Assert
    assert(collision == NULL);
    assert(_checkCollisionRecsCallCount == 2);
}
GRAPH_SKETCH_TEST_CASE(GraphSketch_BvhTreeCollision_DoesNotCollideOutsideItsOwnBoundingBox)


TEST _GraphSketch_BvhTreeCollision_DoesNotCollideOutsideScene(GraphSketch *gs)
{
    // Arrange
    const Vector2 pos = {100,100};
    GraphSketch_AddVertex(gs, pos, SCENE_BOUNDING_BOX);
    
    // Act
    Rectangle noCollisionBox = (Rectangle) {.x = SCENE_BOUNDING_BOX.x - 2, .y = SCENE_BOUNDING_BOX.y - 2, .width = 1, .height = 1};
    Primitive *collision = BvhTree_CheckCollision(gs->BvhTree, noCollisionBox);
    
    // Assert
    assert(collision == NULL);
    assert(_checkCollisionRecsCallCount == 1);
}
GRAPH_SKETCH_TEST_CASE(GraphSketch_BvhTreeCollision_DoesNotCollideOutsideScene)

#endif /* GraphSketchTests_h */
