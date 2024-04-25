//
//  SceneController.h
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/25/24.
//

#ifndef SceneController_h
#define SceneController_h

#include "../GraphSketch/GraphSketch.h"

#define SCENE_BOUNDING_BOX ((Rectangle){.x = 0, .y = 0, .width = 800, .height = 450})
#define GRAPH_SKETCH_BOUNDING_BOX ((Rectangle) {.x = 0, .y = 0, .width = 500, .height = SCENE_BOUNDING_BOX.height })
#define GUI_BOUNDING_BOX ((Rectangle) {.x = 500, .y = 0, .width = SCENE_BOUNDING_BOX.width - 500, .height = SCENE_BOUNDING_BOX.height})
#define EDGE_CREATION_BOUNDING_BOX(pos) Primitive_CreatePrimitiveWithSize(pos, 0, 10).BoundingBox;
#define VERTEX_CREATION_BOUNDING_BOX(pos) Primitive_CreatePrimitiveWithSize(pos, 0, GRAPH_VERTEX_RADIUS*3).BoundingBox;

typedef struct
{
    // Scene states
    bool IsInEdgeCreationState;
    VertexIndex EdgeCreationStateOriginVertexIndex;
    
    bool IsInVertexMoveState;
    VertexIndex VertexMoveStateIndex;
    
    // GraphSketch editing modes
    bool IsInVertexCreationMode;
    bool IsInEdgeCreationMode;
    bool IsInVertexMoveMode;
    bool IsInEditWeightMode;
    
    // Options
    bool ShowBvhTree;
    bool ShowAdjMatrix;
    bool ShowIncidenceMatrix;
    bool ShowVertices;
    bool ShowEdges;
    bool ShowDirection;
    
    // Color options
    Color VertexColor;
    
    // Output dumps
    StringBuffer AdjMatrixDumpBuffer;
    StringBuffer IncidenceMatrixDumpBuffer;
    char VertexWeightInputBuffer[3];
    
} SceneController;

/// Creates a new scene controller
SceneController *SceneController_CreateSceneController(void);

/// Frees memory of the scene controller
void SceneController_FreeSceneController(SceneController *sc);

/// Determines if the mouse position is on a vertex, if so, caches the vertex and enters the Edge Creation State, waiting for a
/// following vertex to be selected so an edge can be made.
void SceneController_CreateEdge(SceneController *sc, GraphSketch *gs);

/// Creates a vertex at mouse positiion if not on top of another vertex
void SceneController_CreateVertex(SceneController *sc, GraphSketch *gs);

void SceneController_MoveVertex(SceneController *sc, GraphSketch *gs);

/// Draws the GUI and GraphSketch
void SceneController_DrawScene(SceneController *sc, GraphSketch *gs);

#endif /* SceneController_h */
