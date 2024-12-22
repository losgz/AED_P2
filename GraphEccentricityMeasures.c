//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphEccentricityMeasures
//

// Student Name : Eduardo José Farinha do Rosário
// Student Number : 119234
// Student Name : Henrique Marques Lopes
// Student Number : 119954

/*** COMPLETE THE GraphEccentricityMeasuresCompute FUNCTION ***/
/*** COMPLETE THE GraphGetCentralVertices FUNCTION ***/
/*** COMPLETE THE GraphEccentricityMeasuresPrint FUNCTION ***/

#include "GraphEccentricityMeasures.h"

#include <asm-generic/errno.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "GraphAllPairsShortestDistances.h"

struct _GraphEccentricityMeasures {
    unsigned int
        *centralVertices; // centralVertices[0] = number of central vertices
                          // array size is (number of central vertices + 1)
    int *eccentricity;    // the eccentricity value of each vertex
    Graph *graph;         // the graph
    int graphRadius;      // the graph radius
    int graphDiameter;    // the graph diameter
};

static int VertexGetEccentricity(Graph *g, unsigned int vertex);
// Allocate memory
// Compute the vertex eccentricity values
// Compute graph radius and graph diameter
// Compute the set of central vertices
GraphEccentricityMeasures *GraphEccentricityMeasuresCompute(Graph *g) {
    assert(g != NULL);

    GraphEccentricityMeasures *result =
        (GraphEccentricityMeasures *)malloc(sizeof(GraphEccentricityMeasures));

    unsigned int numVertices = GraphGetNumVertices(g);

    result->eccentricity = (int *)malloc(numVertices * sizeof(int));
    assert(result->eccentricity != NULL);
    result->graphRadius = -1;   // initialize with -1
    result->graphDiameter = -1; // initialize with -1
    result->graph = g;

    // initialize the number of central verices as 1
    unsigned int numCentralVertices = 0;
    int eccentricity;

    for (unsigned int i = 0; i < numVertices; i++) {
        eccentricity = VertexGetEccentricity(g, i);
        result->eccentricity[i] = eccentricity;

        if ((eccentricity < result->graphRadius || result->graphRadius == -1) &&
            eccentricity != -1) {
            // new value for the graph radius
            result->graphRadius = eccentricity;
            numCentralVertices = 1; // reset the number of central vertices to 1
        } else if (eccentricity == result->graphRadius) {
            numCentralVertices++; // the vertex is an central vertex
        }

        if (eccentricity > result->graphDiameter)
            // new value for the graph diameter
            result->graphDiameter = eccentricity;
    }

    result->centralVertices =
        (unsigned int *)malloc((numCentralVertices + 1) * sizeof(unsigned int));
    assert(result->centralVertices != NULL);

    result->centralVertices[0] = numCentralVertices;
    numCentralVertices = 0; // reset to 0 for the addition to the array

    for (unsigned int i = 0; i < numVertices; i++) {

        if (result->eccentricity[i] == result->graphRadius) {
            result->centralVertices[++numCentralVertices] = i;
            if (numCentralVertices == result->centralVertices[0])
                break;
        }
    }

    return result;
}

static int VertexGetEccentricity(Graph *g, unsigned int vertex) {
    GraphAllPairsShortestDistances *gPairs =
        GraphAllPairsShortestDistancesExecute(g);
    unsigned int numVertices = GraphGetNumVertices(g);

    int eccentricity = -1;
    int distance;

    // compare the distance to every vertex
    for (unsigned int i = 0; i < numVertices; i++) {
        if (i == vertex) // ignores the distance with it self
            continue;

        distance = GraphGetDistanceVW(gPairs, vertex, i);

        // the eccentricity is the max distance
        if (distance > eccentricity)
            eccentricity = distance;
    }

    GraphAllPairsShortestDistancesDestroy(&gPairs);
    return eccentricity;
}

void GraphEccentricityMeasuresDestroy(GraphEccentricityMeasures **p) {
    assert(*p != NULL);

    GraphEccentricityMeasures *aux = *p;

    free(aux->centralVertices);
    free(aux->eccentricity);

    free(*p);
    *p = NULL;
}

// Getting the computed measures

int GraphGetRadius(const GraphEccentricityMeasures *p) {
    assert(p != NULL);

    return p->graphRadius;
}

int GraphGetDiameter(const GraphEccentricityMeasures *p) {
    assert(p != NULL);

    return p->graphDiameter;
}

int GraphGetVertexEccentricity(const GraphEccentricityMeasures *p,
                               unsigned int v) {
    assert(p != NULL);
    assert(v < GraphGetNumVertices(p->graph));
    assert(p->eccentricity != NULL);

    return p->eccentricity[v];
}

// Getting a copy of the set of central vertices
// centralVertices[0] = number of central vertices in the set
unsigned int *GraphGetCentralVertices(const GraphEccentricityMeasures *p) {
    assert(p != NULL);
    assert(p->centralVertices != NULL);

    size_t size = p->centralVertices[0] * sizeof(unsigned int);
    unsigned int *centralVertices = (unsigned int *)malloc(size);
    memcpy(centralVertices, p->centralVertices, size);

    return centralVertices;
}

// Print the graph radius and diameter
// Print the vertex eccentricity values
// Print the set of central vertices
void GraphEccentricityMeasuresPrint(const GraphEccentricityMeasures *p) {
    printf("Graph Radius: %d\n", p->graphRadius);
    printf("Graph Diameter: %d\n", p->graphDiameter);

    unsigned int numVertices = GraphGetNumVertices(p->graph);

    printf("Eccentricity values: \n");
    for (unsigned int i = 0; i < numVertices; i++) {
        if (p->eccentricity[i] == -1) {
            printf("%d : INF\n", i);
        } else
            printf("%d : %d\n", i, p->eccentricity[i]);
    }

    printf("\nCentral Vertices: \n");
    for (unsigned int i = 1; i <= p->centralVertices[0]; i++) {
        printf("%d\n", p->centralVertices[i]);
    }
}
