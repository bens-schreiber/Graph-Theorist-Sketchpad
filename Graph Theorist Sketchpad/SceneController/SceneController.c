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
    
    sc->IsInVertexCreationMode = true;
    sc->IsInEdgeCreationMode = false;
    
    sc->ShowBvhTree = false;
    sc->ShowAdjMatrix = false;
    sc->ShowIncidenceMatrix = false;
    sc->ShowVertices = true;
    sc->ShowEdges = true;
    
    sc->VertexColor = RAYWHITE;
    
    return sc;
}

void SceneController_FreeSceneController(SceneController *sc)
{
    free(sc);
}

static Rectangle _MouseBoundingBox(Vector2 mousePosition, bool isInEdgeCreationMode, bool isInVertexCreationMode)
{
    Rectangle mouseBoundingBox = {};
    if (isInEdgeCreationMode) mouseBoundingBox = EDGE_CREATION_BOUNDING_BOX(mousePosition);
    if (isInVertexCreationMode) mouseBoundingBox = VERTEX_CREATION_BOUNDING_BOX(mousePosition);
    return mouseBoundingBox;
}

static int _CheckMouseCollision(GraphSketch *gs, bool isInEdgeCreationMode, bool isInVertexCreationMode)
{
    Rectangle mouseBoundingBox = _MouseBoundingBox(GetMousePosition(), isInEdgeCreationMode, isInVertexCreationMode);
    int vi = BvhTree_CheckCollision(gs->BvhTree, mouseBoundingBox);
    return vi;
}

void SceneController_CreateEdge(SceneController *sc, GraphSketch *gs)
{
    assert(sc != NULL);
    assert(gs != NULL);
    assert(sc->IsInEdgeCreationMode);
    if (gs->BvhTree == NULL) return;
    
    int vi = _CheckMouseCollision(gs, sc->IsInEdgeCreationMode, sc->IsInVertexCreationMode);
    if (!HAS_COLLISION(vi)) return;
    
    // Enter the edge creation state, where we are waiting for a second edge to be selected
    if (!sc->IsInEdgeCreationState)
    {
        sc->IsInEdgeCreationState = true;
        sc->EdgeCreationOriginPrim = gs->IndexToPrimitiveMap[vi];
        return;
    }
    
    // A second edge has been seleected at vi
    VertexIndex v1 = sc->EdgeCreationOriginPrim.VertexIndex;
    VertexIndex v2 = vi;
    GraphSketch_AddEdge(gs, v1, v2);
    
    Graph_DumpAdjMatrix(gs->Graph, sc->AdjMatrixDumpBuffer);
    Graph_DumpIncidenceMatrix(gs->Graph, sc->IncidenceMatrixDumpBuffer);
    sc->IsInEdgeCreationState = false;
}

void SceneController_CreateVertex(SceneController *sc, GraphSketch *gs)
{
    assert(sc != NULL);
    assert(gs != NULL);
    assert(sc->IsInVertexCreationMode);
    
    int vi = _CheckMouseCollision(gs, sc->IsInEdgeCreationMode, sc->IsInVertexCreationMode);
    
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
            Rectangle mouseBoundingBox = _MouseBoundingBox(mousePosition, sc->IsInEdgeCreationMode, sc->IsInVertexCreationMode);
            
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
    }
    
    if (GuiButton((Rectangle){ 530, 340, 140, 20 }, "Edge Mode"))
    {
        sc->IsInEdgeCreationMode = true;
        sc->IsInVertexCreationMode = false;
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
    
    
    if (sc->IsInEdgeCreationState)
    {
        DrawLineEx(sc->EdgeCreationOriginPrim.Centroid, mousePosition, 2, RAYWHITE);
    }
}
