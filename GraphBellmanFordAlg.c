//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphBellmanFord - Bellman-Ford Algorithm
//

// Student Name : Eduardo José Farinha do Rosário
// Student Number : 119234
// Student Name : Henrique Marques Lopes
// Student Number : 119954

/*** COMPLETE THE GraphBellmanFordAlgExecute FUNCTION ***/

#include "GraphBellmanFordAlg.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IntegersStack.h"
#include "SortedList.h"
#include "instrumentation.h"

struct _GraphBellmanFordAlg {
    unsigned int *marked; // To mark vertices when reached for the first time
    int *
        distance; // The number of edges on the path from the start vertex
                  // distance[i]=-1, if no path found from the start vertex to i
    int *predecessor; // The predecessor vertex in the shortest path
                      // predecessor[i]=-1, if no predecessor exists
    Graph *graph;
    unsigned int startVertex; // The root of the shortest-paths tree
};

GraphBellmanFordAlg *GraphBellmanFordAlgExecute(Graph *g,
                                                unsigned int startVertex) {
    assert(g != NULL);
    assert(startVertex < GraphGetNumVertices(g));
    assert(GraphIsWeighted(g) == 0);

    GraphBellmanFordAlg *result =
        (GraphBellmanFordAlg *)malloc(sizeof(struct _GraphBellmanFordAlg));
    assert(result != NULL);

    // Given graph and start vertex for the shortest-paths
    result->graph = g;
    result->startVertex = startVertex;

    unsigned int numVertices = GraphGetNumVertices(g);

    unsigned int numEdeges = GraphGetNumEdges(g);

    // allocate the required memory
    result->distance = (int *)malloc(numVertices * sizeof(int));
    result->predecessor = (int *)malloc(numVertices * sizeof(int));
    result->marked = (unsigned int *)malloc(numVertices * sizeof(unsigned int));

    // initialize the result distance, predecessor and marked;
    for (int i = 0; i < numVertices; i++) {
        result->distance[i] = -1;
        result->predecessor[i] = -1;
        result->marked[i] = 0; // set all elements to false
    }

    // set the distance to the start vertex to 0 and mark it
    result->distance[startVertex] = 0;
    result->marked[startVertex] = 1;

    // initialize variables
    unsigned int *adjacents;

    for (int i = 0; i < numVertices; i++) {
        for (int u = 0; u < numVertices; u++) {
            if (result->marked[u] == 0) // ignores unmarked elements
                continue;

            adjacents = GraphGetAdjacentsTo(g, u);
            unsigned int size = adjacents[0]; // number of adjacent vertices

            for (int j = 1; j <= size; j++) {
                unsigned int v = adjacents[j]; 

                // checks if theres no path to vertex v or if the new path is
                // shorter
                if (result->distance[v] == -1 ||
                    result->distance[u] + 1 < result->distance[v]) {

                    // if true update the results
                    result->distance[v] = result->distance[u] + 1;
                    result->predecessor[v] = u;
                    result->marked[v] = 1;
                }
            }
            free(adjacents); // free the array with the adjacent vertices
        }
    }

    return result;
}

void GraphBellmanFordAlgDestroy(GraphBellmanFordAlg **p) {
    assert(*p != NULL);

    GraphBellmanFordAlg *aux = *p;

    free(aux->marked);
    free(aux->predecessor);
    free(aux->distance);

    free(*p);
    *p = NULL;
}

// Getting the paths information

int GraphBellmanFordAlgReached(const GraphBellmanFordAlg *p, unsigned int v) {
    assert(p != NULL);
    assert(v < GraphGetNumVertices(p->graph));

    return p->marked[v];
}

int GraphBellmanFordAlgDistance(const GraphBellmanFordAlg *p, unsigned int v) {
    assert(p != NULL);
    assert(v < GraphGetNumVertices(p->graph));

    return p->distance[v];
}
Stack *GraphBellmanFordAlgPathTo(const GraphBellmanFordAlg *p, unsigned int v) {
    assert(p != NULL);
    assert(v < GraphGetNumVertices(p->graph));

    Stack *s = StackCreate(GraphGetNumVertices(p->graph));

    if (p->marked[v] == 0) {
        return s;
    }

    // Store the path
    for (unsigned int current = v; current != p->startVertex;
         current = p->predecessor[current]) {
        StackPush(s, current);
    }

    StackPush(s, p->startVertex);

    return s;
}

// DISPLAYING on the console

void GraphBellmanFordAlgShowPath(const GraphBellmanFordAlg *p, unsigned int v) {
    assert(p != NULL);
    assert(v < GraphGetNumVertices(p->graph));

    Stack *s = GraphBellmanFordAlgPathTo(p, v);

    while (StackIsEmpty(s) == 0) {
        printf("%d ", StackPop(s));
    }

    StackDestroy(&s);
}

// Display the Shortest-Paths Tree in DOT format
void GraphBellmanFordAlgDisplayDOT(const GraphBellmanFordAlg *p) {
    assert(p != NULL);

    Graph *original_graph = p->graph;
    unsigned int num_vertices = GraphGetNumVertices(original_graph);

    // The paths tree is a digraph, with no edge weights
    Graph *paths_tree = GraphCreate(num_vertices, 1, 0);

    // Use the predecessors array to add the tree edges
    for (unsigned int w = 0; w < num_vertices; w++) {
        // Vertex w has a predecessor vertex v?
        int v = p->predecessor[w];
        if (v != -1) {
            GraphAddEdge(paths_tree, (unsigned int)v, w);
        }
    }

    // Display the tree in the DOT format
    GraphDisplayDOT(paths_tree);

    // Housekeeping
    GraphDestroy(&paths_tree);
}
