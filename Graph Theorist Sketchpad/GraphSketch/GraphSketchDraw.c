//
//  Draw.c
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/24/24.
//

#include "GraphSketch.h"
#include <assert.h>
#include <stdio.h>
#include "math.h"

void DrawableVertex_Draw(const DrawableVertex *dv, const Primitive *p)
{
    assert(dv != NULL);
    assert(p != NULL);
    DrawCircleV(p->Centroid, GRAPH_VERTEX_RADIUS, SKYBLUE);
    int fontMeasure = MeasureText(dv->Label, 20);
    DrawText(dv->Label, p->Centroid.x - fontMeasure / 2, p->Centroid.y - fontMeasure / 2, 20, BLACK);
}

static Vector2 _QuadraticBezierMidpoint(Vector2 p0, Vector2 p1, Vector2 p2) {
    Vector2 midpoint;

    // Calculate the midpoint using the parametric equation
    midpoint.x = (p0.x + 2 * p1.x + p2.x) / 4.0;
    midpoint.y = (p0.y + 2 * p1.y + p2.y) / 4.0;

    return midpoint;
}

static void _DrawableEdge_DrawSelfLoop(const GraphSketch *gs, DrawableEdge de)
{
    Primitive v = gs->IndexToPrimitiveMap[de.V1];
    const int xOffset = 20;
    const int yOffset = 80;
    
    DrawText(de.Label, v.Centroid.x, v.Centroid.y - yOffset / 1.5, 15, BLACK);
    
    Vector2 p1 = (Vector2) { v.Centroid.x - xOffset, v.Centroid.y};
    Vector2 splineControl = (Vector2) {v.Centroid.x, v.Centroid.y - yOffset};
    Vector2 p2 = (Vector2) {v.Centroid.x + xOffset, v.Centroid.y};
    Vector2 points[3] = { p1, splineControl, p2 };
    DrawSplineBezierQuadratic(points, 3, 2, BLACK);
}

void CalculateCurvature(Vector2 v0, Vector2 v1, Vector2 v2, double* curvatureX, double* curvatureY)
{
    
    // First derivatives
    Vector2 dpdt1 = {2 * (v1.x - v0.x), 2 * (v1.y - v0.y)};
    Vector2 dpdt2 = {2 * (v2.x - v1.x), 2 * (v2.y - v1.y)};
    
    // Second derivatives
    Vector2 d2pdt21 = {2 * (v0.x - 2 * v1.x + v2.x), 2 * (v0.y - 2 * v1.y + v2.y)};
    
    // Curvature calculation
    *curvatureX = (dpdt1.x * d2pdt21.y - dpdt1.y * d2pdt21.x) / pow(dpdt1.x * dpdt1.x + dpdt1.y * dpdt1.y, 1.5);
    *curvatureY = (dpdt2.x * d2pdt21.y - dpdt2.y * d2pdt21.x) / pow(dpdt2.x * dpdt2.x + dpdt2.y * dpdt2.y, 1.5);
}

void DrawableEdge_Draw(const GraphSketch *gs, DrawableEdge de)
{
    if (de.V1 == de.V2)
    {
        _DrawableEdge_DrawSelfLoop(gs, de);
        return;
    }
    
    // Find the linear midpoint between centroid1 and centroid2
    Vector2 c1 = gs->IndexToPrimitiveMap[de.V1].Centroid;
    Vector2 c2 = gs->IndexToPrimitiveMap[de.V2].Centroid;
    Vector2 mid = { (c1.x + c2.x) / 2, (c1.y + c2.y) / 2};
    
    // The spline control will be the point in between c1 and c2 that indicates the bezier curve.
    Vector2 splineControl = mid;
    
    // Calculate curvature
    double curvatureX, curvatureY;
    CalculateCurvature(c1, splineControl, c2, &curvatureX, &curvatureY);
    
    // Move control point in the direction of maximum curvature
    splineControl.x += de.Curvature * (curvatureX > 0 ? 1 : -1);
    splineControl.y += de.Curvature * (curvatureY > 0 ? 1 : -1);
//    if (fabs(curvatureX) > fabs(curvatureY))
//    {
//        splineControl.x += de.Curvature * (curvatureX > 0 ? 1 : -1);
//    }
//    else
//    {
//        splineControl.y += de.Curvature * (curvatureY > 0 ? 1 : -1);
//    }
    
    Vector2 points[3] = { c1, splineControl, c2 };
    Vector2 bezierMid = _QuadraticBezierMidpoint(points[0], points[1], points[2]);
    
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

static void _DrawMatrix(StringBuffer buffer, Vector2 position, int spacingHorizontal)
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
        xOffset += *iter == '-' ? 6 : spacingHorizontal;
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
    
    _DrawMatrix(buffer, (Vector2){10,10}, 8);
}

void GraphSketch_DrawIncidenceMatrix(const GraphSketch *gs, StringBuffer buffer, bool update)
{
    assert(gs != NULL);
    
    if (update)
    {
        Graph_DumpIncidenceMatrix(gs->Graph, buffer);
    }
    
    _DrawMatrix(buffer, (Vector2){10,300}, 12);
}

void GraphSketch_DrawEdges(const GraphSketch *gs)
{
    assert(gs != NULL);
    
    for (int i = 0; i < gs->Graph->Edges; i++)
    {
        DrawableEdge_Draw(gs, gs->DrawableEdgeList[i]);
    }
}
