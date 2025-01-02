//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphAllPairsShortestDistances
//

// Student Name : Eduardo José Farinha do Rosário
// Student Number : 119234
// Student Name : Henrique Marques Lopes
// Student Number : 119954

/*** COMPLETE THE GraphAllPairsShortestDistancesExecute FUNCTION ***/

#include "GraphAllPairsShortestDistances.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"

struct _GraphAllPairsShortestDistances {
    int **distance; // The 2D matrix storing the all-pairs shortest distances
                    // It is stored as an array of pointers to 1D rows
                    // Idea: an INDEFINITE distance value is stored as -1
    Graph *graph;
};

// Allocate memory and initialize the distance matrix
// Compute the distances between vertices by running the Bellman-Ford algorithm
GraphAllPairsShortestDistances *
GraphAllPairsShortestDistancesExecute(Graph *g) {
    assert(g != NULL);

    GraphAllPairsShortestDistances *result =
        (GraphAllPairsShortestDistances *)malloc(
            sizeof(GraphAllPairsShortestDistances));

    assert(result != NULL);

    unsigned int numVertices = GraphGetNumVertices(g);

    result->graph = g;
    result->distance = (int **)malloc(numVertices * sizeof(int *));

    assert(result->distance != NULL);

    GraphBellmanFordAlg *sdGraph;
    int distance;

    for (unsigned int i = 0; i < numVertices; i++) {
        // shortest distance path graph
        sdGraph = GraphBellmanFordAlgExecute(g, i);

        result->distance[i] = (int *)malloc(numVertices * sizeof(int));

        assert(result->distance[i] != NULL);

        for (unsigned int j = 0; j < numVertices; j++) {
            distance = GraphBellmanFordAlgDistance(sdGraph, j); // distance for i to j
            result->distance[i][j] = distance;
        }
        
        GraphBellmanFordAlgDestroy(&sdGraph);
    }

    return result;
}

void GraphAllPairsShortestDistancesDestroy(GraphAllPairsShortestDistances **p) {
    assert(*p != NULL);

    GraphAllPairsShortestDistances *aux = *p;
    unsigned int numVertices = GraphGetNumVertices(aux->graph);

    for (unsigned int i = 0; i < numVertices; i++) {
        free(aux->distance[i]);
    }

    free(aux->distance);

    free(*p);
    *p = NULL;
}

// Getting the result

int GraphGetDistanceVW(const GraphAllPairsShortestDistances *p, unsigned int v,
                       unsigned int w) {
    assert(p != NULL);
    assert(v < GraphGetNumVertices(p->graph));
    assert(w < GraphGetNumVertices(p->graph));

    return p->distance[v][w];
}

// DISPLAYING on the console

void GraphAllPairsShortestDistancesPrint(
    const GraphAllPairsShortestDistances *p) {
    assert(p != NULL);

    unsigned int numVertices = GraphGetNumVertices(p->graph);
    printf("Graph distance matrix - %u vertices\n", numVertices);

    for (unsigned int i = 0; i < numVertices; i++) {
        for (unsigned int j = 0; j < numVertices; j++) {
            int distanceIJ = p->distance[i][j];
            if (distanceIJ == -1) {
                // INFINITY - j was not reached from i
                printf(" INF");
            } else {
                printf(" %3d", distanceIJ);
            }
        }
        printf("\n");
    }
}
