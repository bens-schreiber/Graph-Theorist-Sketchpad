//
//  LongestAxis.h
//  Graph Theorist Sketchpad
//
//  Created by Benjamin Schreiber on 4/23/24.
//

#ifndef LongestAxis_h
#define LongestAxis_h

struct Rectangle;

typedef int (*QSortCompare)(const void *, const void *);

int LongestAxis_CompareX(const void *a, const void *b);

int LongestAxis_CompareY(const void *a, const void *b);

/// Determines which axis is the longest in a bounding box
/// - Returns a function for the axis longest to sort by
QSortCompare LongestAxis_CompareByLongestAxis(struct Rectangle boundingBox);

#endif /* LongestAxis_h */
