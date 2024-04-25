//
//  Draw.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/24/24.
//

#include "GraphSketch.h"
#include <assert.h>
#include <stdio.h>

void DrawableVertex_Draw(const DrawableVertex *dv, const Primitive *p)
{
    assert(dv != NULL);
    assert(p != NULL);
    DrawCircleV(p->Centroid, GRAPH_VERTEX_RADIUS, SKYBLUE);
    int fontMeasure = MeasureText(dv->Label, 20);
    DrawText(dv->Label, p->Centroid.x - fontMeasure / 2, p->Centroid.y - fontMeasure / 2, 20, BLACK);
}

static void _DrawableEdge_DrawSelfLoop(const GraphSketch *gs, DrawableEdge de)
{
    Primitive v = gs->IndexToPrimitiveMap[de.V1];
    DrawText(de.Label, v.Centroid.x, v.Centroid.y + GRAPH_VERTEX_RADIUS, 15, BLACK);
    DrawCircleLinesV(v.Centroid, GRAPH_VERTEX_RADIUS + 10, BLACK);
}

// Function to calculate the midpoint of a quadratic bezier curve
Vector2 QuadraticBezierMidpoint(Vector2 p0, Vector2 p1, Vector2 p2) {
    Vector2 midpoint;

    // Calculate the midpoint using the parametric equation
    midpoint.x = (p0.x + 2 * p1.x + p2.x) / 4.0;
    midpoint.y = (p0.y + 2 * p1.y + p2.y) / 4.0;

    return midpoint;
}


void DrawableEdge_Draw(const GraphSketch *gs, DrawableEdge de)
{
    if (de.V1 == de.V2)
    {
        _DrawableEdge_DrawSelfLoop(gs, de);
        return;
    }
    
    Vector2 c1 = gs->IndexToPrimitiveMap[de.V1].Centroid;
    Vector2 c2 = gs->IndexToPrimitiveMap[de.V2].Centroid;
    Vector2 mid = { (c1.x + c2.x) / 2, (c1.y + c2.y) / 2};
    
    Vector2 splineControl = mid;
    if (c1.x > c2.y)
    {
        splineControl.x += 100;
    }
    else
    {
        splineControl.y += 100;
    }
    Vector2 points[3] = { c1, splineControl, c2 };
    Vector2 bezierMid = QuadraticBezierMidpoint(points[0], points[1], points[2]);
    DrawText(de.Label, bezierMid.x, bezierMid.y + 10, 15, BLACK);
    DrawSplineBezierQuadratic(points, 3, 2, BLACK);
    
    DrawLineV(gs->IndexToPrimitiveMap[de.V1].Centroid, gs->IndexToPrimitiveMap[de.V2].Centroid, BLACK);
}
void GraphSketch_DrawVertices(const GraphSketch *gs)
{
    assert(gs != NULL);
    
    for (VertexIndex vi = 0; vi < gs->Graph->Vertices; vi++)
    {
        DrawableVertex_Draw(&gs->IndexToDrawableVertexMap[vi], &gs->IndexToPrimitiveMap[vi]);
    }
}

static void _DrawMatrix(StringBuffer buffer, Vector2 position)
{
    int xOffset = position.x;
    int yOffset = position.y;
    char *iter = buffer;
    char text[2] = {*iter, '\0'};
    while (*iter != '\0')
    {
        if (*iter == '\n')
        {
            yOffset += 15;
            xOffset = 10;
            iter++;
            continue;
        }
        text[0] = *iter;
        DrawText(text, xOffset, yOffset, 15, BLACK);
        xOffset += 8;
        iter++;
    }
}

void GraphSketch_DrawAdjMatrix(const GraphSketch *gs, StringBuffer buffer, bool update)
{
    assert(gs != NULL);
    
    if (update)
    {
        Graph_DumpAdjMatrix(gs->Graph, buffer);
    }
    
    _DrawMatrix(buffer, (Vector2){10,10});
}

void GraphSketch_DrawIncidenceMatrix(const GraphSketch *gs, StringBuffer buffer, bool update)
{
    assert(gs != NULL);
    
    if (update)
    {
        Graph_DumpIncidenceMatrix(gs->Graph, buffer);
    }
    
    _DrawMatrix(buffer, (Vector2){10,300});
}

void GraphSketch_DrawEdges(const GraphSketch *gs)
{
    assert(gs != NULL);
    
    for (int i = 0; i < gs->Graph->Edges; i++)
    {
        DrawableEdge_Draw(gs, gs->DrawableEdgeList[i]);
    }
}
