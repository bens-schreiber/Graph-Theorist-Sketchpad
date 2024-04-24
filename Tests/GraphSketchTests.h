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

// --- Mocks ---
void DrawRectangleRec(Rectangle _, Color __) {}

static unsigned int _checkCollisionRecsCallCount = 0;
bool CheckCollisionRecs(Rectangle a, Rectangle b)
{
    _checkCollisionRecsCallCount++;
    return a.x < b.x + b.width &&
    a.x + a.width > b.x &&
    a.y < b.y + b.height &&
    a.y + a.height > b.y;
}
// --- Mocks ---


void GraphSketch_CreateNew_SetsGraphWithNoVerticesAndNullBvhTree(void)
{
    // Act
    GraphSketch *gs = GraphSketch_CreateGraphSketch();
    
    // Assert
    assert(gs->BvhTree == NULL);
    assert(gs->Graph != NULL);
    assert(gs->Graph->Vertices == 0);
    
    // Cleanup
    GraphSketch_FreeGraphSketch(gs);
}

void GraphSketch_AddVertex_CreatesNewGraphVertexAndBvhTreeAndPrimitiveAndDrawable(void)
{
    // Arrange
    GraphSketch *gs = GraphSketch_CreateGraphSketch();
    const Vector2 pos = {0,0};
    
    // Act
    VertexIndex vi = GraphSketch_AddVertex(gs, pos, SCENE_BOUNDING_BOX);
    Vector2 centroid = gs->IndexToPrimitiveMap[vi].Centroid;
    
    // Assert
    assert(gs->Graph->Vertices == 1);
    assert(gs->BvhTree != NULL);
    assert(centroid.x == pos.x && centroid.y == pos.y);
    assert(gs->IndexToDrawableVertexMap[vi].VertexIndex == vi);
    
    // Cleanup
    GraphSketch_FreeGraphSketch(gs);
}

void GraphSketch_BvhTreeCollision_DoesCollideWithItsOwnBoundingBox(void)
{
    // Arrange
    _checkCollisionRecsCallCount = 0;
    GraphSketch *gs = GraphSketch_CreateGraphSketch();
    const Vector2 pos = {100,100};
    VertexIndex vi = GraphSketch_AddVertex(gs, pos, SCENE_BOUNDING_BOX);
    
    // Act
    bool collision = BvhTree_CheckCollision(gs->BvhTree, gs->IndexToPrimitiveMap[vi].BoundingBox);
    
    // Assert
    assert(collision);
    assert(_checkCollisionRecsCallCount == 2);
    
    // Cleanup
    GraphSketch_FreeGraphSketch(gs);
    _checkCollisionRecsCallCount = 0;
}

void GraphSketch_BvhTreeCollision_DoesNotCollideOutsideItsOwnBoundingBox(void)
{
    // Arrange
    GraphSketch *gs = GraphSketch_CreateGraphSketch();
    const Vector2 pos = {100,100};
    VertexIndex vi = GraphSketch_AddVertex(gs, pos, SCENE_BOUNDING_BOX);
    
    // Act
    Rectangle boundingBox = gs->IndexToPrimitiveMap[vi].BoundingBox;
    Rectangle noCollisionBox = { .x = boundingBox.x - 2, .y = boundingBox.y - 2, .width = 1, .height = 1 };
    bool collision = BvhTree_CheckCollision(gs->BvhTree, noCollisionBox);
    
    // Assert
    assert(!collision);
    assert(_checkCollisionRecsCallCount == 2);
    
    // Cleanup
    GraphSketch_FreeGraphSketch(gs);
    _checkCollisionRecsCallCount = 0;
}

void GraphSketch_BvhTreeCollision_DoesNotCollideOutsideScene(void)
{
    // Arrange
    GraphSketch *gs = GraphSketch_CreateGraphSketch();
    const Vector2 pos = {100,100};
    GraphSketch_AddVertex(gs, pos, SCENE_BOUNDING_BOX);
    
    // Act
    Rectangle noCollisionBox = (Rectangle) {.x = SCENE_BOUNDING_BOX.x - 2, .y = SCENE_BOUNDING_BOX.y - 2, .width = 1, .height = 1};
    bool collision = BvhTree_CheckCollision(gs->BvhTree, noCollisionBox);
    
    // Assert
    assert(!collision);
    assert(_checkCollisionRecsCallCount == 1);
    
    // Cleanup
    GraphSketch_FreeGraphSketch(gs);
    _checkCollisionRecsCallCount = 0;
}

#endif /* GraphSketchTests_h */
