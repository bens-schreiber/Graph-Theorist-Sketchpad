# Graph Theorist Sketchpad
Created for WSU MATH 453 Graph Theory. Made entirely with C in Raylib and Raygui. Has its own collision detection system using a Bounding Volume Hierarchy Tree.
This is definitely a "runs on my machine" kind of project, however, if you have a mac, Xcode, and some spare time, you can try to run it by cloning the Raygui repo

The following is the write-up required for the project submission:

## Graph Theorist Sketchpad

### Introduction
The Graph Theorist Sketchpad is a program that allows users to create, manipulate, and analyze graphs. The program was created using the C Programming language, along with Raylib, a C wrapper for OpenGL, and RayGUI, an auxiliary library for Raylib that provides a set of GUI elements. The program was created as a final project for Math 453: Graph Theory at Washington State University. Because I chose to create the program in C, the entire project is full of my own implementations of common data structures and algorithms, from collision detection to unit testing.

### Features

1. Create Vertices
    - Users can create vertices by entering "Vertex Creation Mode" and clicking anywhere on the screen away from the bounds of existing vertices and the GUI.

2. Create Edges
    - Users can create edges by entering "Edge Creation Mode" and clicking on two vertices. The program will automatically create an edge between the two vertices.

3. Parallel Edges
    - Users can create parallel edges by going through the same process as create edges. This edge will be created using a Bezier curve, which is moved away from all other edges to prevent overlap.

4. Move Vertices
    - Users can move vertices by entering "Vertex Move Mode" and dragging the vertex to a new location. All edges connected to the vertex will move with it.

5. Self Loops
    - Users can create self loops by entering "Edge Creation Mode" and clicking on the same vertex twice.

6. Directed Edges
    - Users can create directed edges by entering "Edge Creation Mode". The program will automatically create a directed edge from the first vertex to the second vertex.

7. Label Vertices
    - All vertices are labeled with a unique number. Users can toggle the visibility of these labels.

8. Label Edges
    - All edges are labeled with a unique number. Users can toggle the visibility of these labels.

9. View Edge count
    - Users can see the amount of edges in the graph at the top of the screen.

10. View Vertex count
    - Users can see the amount of vertices in the graph at the top of the screen.

11. Create Weighted Edges
    - Users can create weighted edges by entering "Edge Creation Mode" and entering a weight in the GUI. All edges are labeled with their weight.

12. Color Vertices
    - Users can color vertices by selecting a color from the GUI and creating a new vertex. The vertex will be colored with the selected color.

13. Incidence Matrix
    - Users can view the incidence matrix of the graph by pressing the "Show Incidence Matrix" button in the GUI. The incidence matrix also denotes the direction and weight of the edges. Self loops are denoted by a single 1 in the column of the vertex.

14. Adjacency Matrix
    - Users can view the adjacency matrix of the graph by pressing the "Show Adjacency Matrix" button in the GUI. The adjacency matrix simply denotes if the vertices are connected by an edge, with regard to direction.

15. Vertex Degrees
    - Users can view the degree of each vertex by pressing the "Show Vertex Degrees" button in the GUI. The degree of a vertex is the number of incoming and outgoing edges. Self loops are counted once.

16. Bvh Collison Detection
    - Users can click "Show BVH Tree" to see the bounding volume hierarchy tree that is used for collision detection. The tree is built using the graph, and updates every time the graph is updated. On Vertex mode, the user can see the bounding box of the mouse plus the required space between vertices On edge mode, the user can see a smaller bounding box around the mouse, denoting the mouse collision zone. When hovered over a collideable, the user will see a green square onn the mouse collision zone.

17. Clear All
    - Users can clear the graph by pressing the "Clear All" button in the GUI. This will remove all vertices and edges from the graph.

