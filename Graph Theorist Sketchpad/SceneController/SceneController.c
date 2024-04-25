//
//  SceneController.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/25/24.
//

#include "SceneController.h"
#include <raylib.h>
#include <assert.h>
#include <stdlib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#define HAS_COLLISION(ret) (ret >= 0)

SceneController *SceneController_CreateSceneController(void)
{
    SceneController *sc = malloc(sizeof(SceneController));
    
    sc->AdjMatrixDumpBuffer[0] = '\0';
    sc->IncidenceMatrixDumpBuffer[0] = '\0';
    
    sc->IsInEdgeCreationState = false;
    sc->IsInVertexMoveState = false;
    
    sc->IsInVertexCreationMode = true;
    sc->IsInEdgeCreationMode = false;
    sc->IsInVertexMoveMode = false;
    
    sc->ShowBvhTree = false;
    sc->ShowAdjMatrix = false;
    sc->ShowIncidenceMatrix = false;
    sc->ShowVertices = true;
    sc->ShowEdges = true;
    sc->ShowDirection = true;
    
    sc->VertexColor = RAYWHITE;
    
    return sc;
}

void SceneController_FreeSceneController(SceneController *sc)
{
    free(sc);
}

static Rectangle _MouseBoundingBox(SceneController *sc, Vector2 mousePosition)
{
    Rectangle mouseBoundingBox = {};
    if (sc->IsInEdgeCreationMode) mouseBoundingBox = EDGE_CREATION_BOUNDING_BOX(mousePosition);
    if (sc->IsInVertexCreationMode) mouseBoundingBox = VERTEX_CREATION_BOUNDING_BOX(mousePosition);
    if (sc->IsInVertexMoveMode) mouseBoundingBox = EDGE_CREATION_BOUNDING_BOX(mousePosition);
    return mouseBoundingBox;
}

static int _CheckMouseCollision(SceneController *sc, GraphSketch *gs)
{
    if (gs->BvhTree == NULL) return -1;
    Rectangle mouseBoundingBox = _MouseBoundingBox(sc, GetMousePosition());
    int vi = BvhTree_CheckCollision(gs->BvhTree, mouseBoundingBox);
    return vi;
}

void SceneController_CreateEdge(SceneController *sc, GraphSketch *gs)
{
    assert(sc != NULL);
    assert(gs != NULL);
    assert(sc->IsInEdgeCreationMode);
    if (gs->BvhTree == NULL) return;
    if (GetMousePosition().x >= GUI_BOUNDING_BOX.x) return;
    
    int vi = _CheckMouseCollision(sc, gs);
    if (!HAS_COLLISION(vi))
    {
        sc->IsInEdgeCreationState = false;
        GuiUnlock();
        return;
    }
    
    // Enter the edge creation state, where we are waiting for a second edge to be selected
    if (!sc->IsInEdgeCreationState)
    {
        sc->IsInEdgeCreationState = true;
        GuiLock();
        sc->EdgeCreationStateOriginVertexIndex = vi;
        return;
    }
    
    // A second edge has been seleected at vi
    VertexIndex v1 = sc->EdgeCreationStateOriginVertexIndex;
    VertexIndex v2 = vi;
    GraphSketch_AddEdge(gs, v1, v2);
    
    Graph_DumpAdjMatrix(gs->Graph, sc->AdjMatrixDumpBuffer);
    Graph_DumpIncidenceMatrix(gs->Graph, sc->IncidenceMatrixDumpBuffer);
    sc->IsInEdgeCreationState = false;
    GuiUnlock();
}

void SceneController_CreateVertex(SceneController *sc, GraphSketch *gs)
{
    assert(sc != NULL);
    assert(gs != NULL);
    assert(sc->IsInVertexCreationMode);
    
    int vi = _CheckMouseCollision(sc, gs);
    
    // No vertices on top of each other
    if (HAS_COLLISION(vi)) return;
    
    Vector2 mousePosition = GetMousePosition();
    if (mousePosition.x < (GRAPH_SKETCH_BOUNDING_BOX.width - GRAPH_VERTEX_RADIUS))
    {
        GraphSketch_AddVertex(gs, mousePosition, sc->VertexColor, GRAPH_SKETCH_BOUNDING_BOX);
        Graph_DumpAdjMatrix(gs->Graph, sc->AdjMatrixDumpBuffer);
        Graph_DumpIncidenceMatrix(gs->Graph, sc->IncidenceMatrixDumpBuffer);
    }
}

void SceneController_MoveVertex(SceneController *sc, GraphSketch *gs)
{
    assert(sc != NULL);
    assert(gs != NULL);
    assert(sc->IsInVertexMoveMode);
    
    if (GetMousePosition().x + GRAPH_VERTEX_RADIUS >= GUI_BOUNDING_BOX.x)
    {
        return;
    }
    
    if (sc->IsInVertexMoveState)
    {
        
        // Reset bounding box position
        Primitive p = gs->IndexToPrimitiveMap[sc->VertexMoveStateIndex];
        gs->IndexToPrimitiveMap[sc->VertexMoveStateIndex] = Primitive_CreatePrimitive(p.Centroid, p.VertexIndex);
        
        // Reset BVH tree with new pos
        GraphSketch_RefreshBvhTree(gs, SCENE_BOUNDING_BOX);
        
        // Unlock GUI
        sc->IsInVertexMoveState = false;
        GuiUnlock();
        return;
    }
    
    int vi = _CheckMouseCollision(sc, gs);
    if (!HAS_COLLISION(vi)) return;
    
    sc->VertexMoveStateIndex = vi;
    sc->IsInVertexMoveState = true;
    GuiLock();
}

void SceneController_DrawScene(SceneController *sc, GraphSketch *gs)
{
    const Vector2 mousePosition = GetMousePosition();
    
    if (sc->ShowEdges) GraphSketch_DrawEdges(gs);
    
    if (sc->ShowVertices) GraphSketch_DrawVertices(gs);
    
    if (sc->ShowBvhTree)
    {
        BvhTree_Draw(gs->BvhTree);
        
        if (mousePosition.x < GUI_BOUNDING_BOX.x)
        {
            Rectangle mouseBoundingBox = _MouseBoundingBox(sc, mousePosition);
            
            int vi = BvhTree_CheckCollision(gs->BvhTree, mouseBoundingBox);
            DrawRectangleRec(mouseBoundingBox, HAS_COLLISION(vi) ? GREEN : RAYWHITE);
        }
    }
    
    if (sc->ShowAdjMatrix) GraphSketch_DrawAdjMatrix(gs, sc->AdjMatrixDumpBuffer);
    
    if (sc->ShowIncidenceMatrix) GraphSketch_DrawIncidenceMatrix(gs, sc->IncidenceMatrixDumpBuffer);
    
    DrawRectangleRec(GUI_BOUNDING_BOX, Fade(LIGHTGRAY, 0.3f));
    GuiCheckBox((Rectangle){ 530, 30, 20, 20 }, "Show BVH Tree", &sc->ShowBvhTree);
    GuiCheckBox((Rectangle){ 530, 60, 20, 20 }, "Show Adjacency Matrix", &sc->ShowAdjMatrix);
    GuiCheckBox((Rectangle){ 530, 90, 20, 20 }, "Show Vertices", &sc->ShowVertices);
    GuiCheckBox((Rectangle){ 530, 120, 20, 20 }, "Show Incidence Matrix", &sc->ShowIncidenceMatrix);
    GuiCheckBox((Rectangle){ 530, 150, 20, 20 }, "Show Edges", &sc->ShowEdges);
    
    GuiColorPicker((Rectangle){ 530, 210, 90, 90 }, "", &sc->VertexColor);
    
    if (GuiButton((Rectangle){ 530, 310, 140, 20 }, "Vertex Mode"))
    {
        sc->IsInVertexCreationMode = true;
        sc->IsInEdgeCreationMode = false;
        sc->IsInVertexMoveMode = false;
    }
    
    if (GuiButton((Rectangle){ 530, 340, 140, 20 }, "Edge Mode"))
    {
        sc->IsInEdgeCreationMode = true;
        sc->IsInVertexMoveMode = false;
        sc->IsInVertexCreationMode = false;
    }
    
    if (GuiButton((Rectangle){ 530, 370, 140, 20 }, "Move Mode"))
    {
        sc->IsInEdgeCreationMode = false;
        sc->IsInVertexCreationMode = false;
        sc->IsInVertexMoveMode = true;
    }
    
    if (sc->IsInVertexCreationMode)
    {
        if (mousePosition.x < GUI_BOUNDING_BOX.x)
        {
            DrawText("V+", mousePosition.x, mousePosition.y - 20, 20, GREEN);
        }
    }
    
    if (sc->IsInEdgeCreationMode)
    {
        if (mousePosition.x < GUI_BOUNDING_BOX.x)
        {
            DrawText("E+", mousePosition.x, mousePosition.y - 20, 20, GREEN);
        }
    }
    
    if (sc->IsInVertexMoveMode)
    {
        if (mousePosition.x < GUI_BOUNDING_BOX.x)
        {
            DrawText("M", mousePosition.x, mousePosition.y - 20, 20, BLUE);
        }
    }
    
    
    if (sc->IsInEdgeCreationState)
    {
        if (mousePosition.x < GUI_BOUNDING_BOX.x)
        {
            DrawLineEx(gs->IndexToPrimitiveMap[sc->EdgeCreationStateOriginVertexIndex].Centroid, mousePosition, 2, RAYWHITE);
        }
    }
    
    if (sc->IsInVertexMoveState)
    {
        if (mousePosition.x + GRAPH_VERTEX_RADIUS < GUI_BOUNDING_BOX.x)
        {
            gs->IndexToPrimitiveMap[sc->VertexMoveStateIndex].Centroid = GetMousePosition();
        }
    }
}
