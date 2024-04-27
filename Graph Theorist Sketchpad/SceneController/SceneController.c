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
    sc->VertexWeightInputBuffer[0] = '1';
    sc->VertexWeightInputBuffer[1] = '\0';
    
    sc->IsInEdgeCreationState = false;
    sc->IsInVertexMoveState = false;
    
    sc->IsInVertexCreationMode = true;
    sc->IsInEdgeCreationMode = false;
    sc->IsInVertexMoveMode = false;
    sc->IsInEditWeightMode = false;
    
    sc->ShowBvhTree = false;
    sc->ShowAdjMatrix = false;
    sc->ShowIncidenceMatrix = false;
    sc->ShowVertices = true;
    sc->ShowEdges = true;
    sc->ShowDirection = true;
    sc->ShowDegrees = false;
    sc->ShowMST = false;
    
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
    
    // A second edge has been selected at vi
    VertexIndex v1 = sc->EdgeCreationStateOriginVertexIndex;
    VertexIndex v2 = vi;
    int weight = TextToInteger(sc->VertexWeightInputBuffer);
    GraphSketch_AddEdge(gs, v1, v2, weight == 0 ? 1 : weight);
    
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
    assert(sc != NULL);
    assert(gs != NULL);
    
    const Vector2 mousePosition = GetMousePosition();
    
    if (sc->ShowMST)
    {
        GraphSketch_DrawMST(gs);
    }
    else
    {
        
        if (sc->ShowEdges) GraphSketch_DrawEdges(gs);
        
        if (sc->ShowVertices) GraphSketch_DrawVertices(gs);
        
    }
    
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
    
    if (sc->ShowDegrees) GraphSketch_DrawDegrees(gs);
    
    char text[25] = "";
    sprintf(text, "|V| = %u   |E| = %u", gs->Graph->Vertices, gs->Graph->Edges);
    DrawText(text, GUI_BOUNDING_BOX.x - MeasureText(text, 15) - 10, 10, 15, RAYWHITE);
    
    DrawRectangleRec(GUI_BOUNDING_BOX, Fade(LIGHTGRAY, 0.3f));
    GuiCheckBox((Rectangle){ 630, 15, 20, 20 }, "Show BVH Tree", &sc->ShowBvhTree);
    GuiCheckBox((Rectangle){ 630, 45, 20, 20 }, "Show Adjacency Matrix", &sc->ShowAdjMatrix);
    GuiCheckBox((Rectangle){ 630, 75, 20, 20 }, "Show Vertices", &sc->ShowVertices);
    GuiCheckBox((Rectangle){ 630, 105, 20, 20 }, "Show Incidence Matrix", &sc->ShowIncidenceMatrix);
    GuiCheckBox((Rectangle){ 630, 135, 20, 20 }, "Show Edges", &sc->ShowEdges);
    GuiCheckBox((Rectangle){ 630, 165, 20, 20 }, "Show Degrees", &sc->ShowDegrees);
    GuiCheckBox((Rectangle){ 630, 195, 20, 20 }, "Show MST", &sc->ShowMST);
    
    GuiColorPicker((Rectangle){ 630, 230, 100, 50 }, "", &sc->VertexColor);
    
    
    GuiGroupBox((Rectangle){ 630, 290, 140, 30 }, "Weight");
    if (GuiTextBox((Rectangle){ 635, 295, 130, 20 }, sc->VertexWeightInputBuffer, 3, sc->IsInEditWeightMode))
    {
        sc->IsInEditWeightMode = true;
    }
    
    if (GuiButton((Rectangle){ 630, 330, 140, 20 }, "Vertex Mode"))
    {
        sc->IsInVertexCreationMode = true;
        sc->IsInEdgeCreationMode = false;
        sc->IsInVertexMoveMode = false;
    }
    
    if (GuiButton((Rectangle){ 630, 360, 140, 20 }, "Edge Mode"))
    {
        sc->IsInEdgeCreationMode = true;
        sc->IsInVertexMoveMode = false;
        sc->IsInVertexCreationMode = false;
    }
    
    if (GuiButton((Rectangle){ 630, 390, 140, 20 }, "Move Mode"))
    {
        sc->IsInEdgeCreationMode = false;
        sc->IsInVertexCreationMode = false;
        sc->IsInVertexMoveMode = true;
    }
    
    if (GuiButton((Rectangle){ 630, 420, 140, 20 }, "Clear All"))
    {
        SceneController_ClearAll(sc, gs);
        return;
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

void SceneController_ClearAll(SceneController *sc, GraphSketch *gs)
{
    assert(sc != NULL);
    assert(gs != NULL);
    GraphSketch_Reset(gs);
    sc->AdjMatrixDumpBuffer[0] = '\0';
    sc->IncidenceMatrixDumpBuffer[0] = '\0';
}
