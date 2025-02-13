//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira, Joao Manuel Rodrigues - Dec 2024
//
// Testing the Transitive Closure algorithm
//

#include <assert.h>

#include "Graph.h"
#include "GraphTransitiveClosure.h"
#include "instrumentation.h"
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

#define ITERATION InstrCount[0]

void complexityTable1(Graph *g) {
    int numVertices = GraphGetNumVertices(g);
    int numEdges = GraphGetNumEdges(g);

    printf("\nNum Vertices: %d\n", numVertices);
    printf("| Vertex | Num Edges | Iterations |\n");
    for (int i = 0; i < numVertices; i++) {
        InstrReset();
        Graph *TC_result = GraphComputeTransitiveClosure(g);
        printf("| %6d | %9d | %10lu |\n", i, numEdges, ITERATION);
        GraphDestroy(&TC_result);
    }
}

void complexityTableGood() {
    printf("\nBest Case");
    printf("\n| Num Vertices | Num Edges | Iterations |\n");
    for (int i = 3; i < 10; i++) {
        Graph *g = GraphCreate(i, 1, 0);
        int numEdges = GraphGetNumEdges(g);

        InstrReset();
        Graph *TC_result = GraphComputeTransitiveClosure(g);
        printf("| %12d | %9d | %10lu |\n", i, numEdges, ITERATION);
        GraphDestroy(&TC_result);
        GraphDestroy(&g);
    }
}
void complexityTableBad() {
    printf("\nWorst Case");
    printf("\n| Num Vertices | Num Edges | Iterations |\n");
    for (int i = 3; i < 10; i++) {
        Graph *g = GraphCreateComplete(i, 1);
        int numEdges = GraphGetNumEdges(g);

        InstrReset();
        Graph *TC_result = GraphComputeTransitiveClosure(g);
        printf("| %12d | %9d | %10lu |\n", i, numEdges, ITERATION);
        GraphDestroy(&TC_result);
        GraphDestroy(&g);
    }
}

void complexityTableRandom() {
    printf("\nRandom Case");
    printf("\n| Num Vertices | Num Edges | Iterations |\n");

    srand(time(NULL)); // Seed the random number generator

    for (int i = 2; i < 1024; i *= 2) {
        Graph *g = GraphCreate(i, 1, 0); // Create a graph with `i` vertices

        // Randomize edge density: Between i (sparse) and i*i/2 (dense)
        int maxEdges = i * (i - 1) / 2;   // Maximum edges for a directed graph
        int targetEdges = rand() % maxEdges + 1; // Random number of edges between 1 and maxEdges
        int numEdges = 0;

        for (int j = 0; j < targetEdges; j++) {
            int u = rand() % i; // Random vertex u
            int v = rand() % i; // Random vertex v
            if (u != v && GraphAddEdge(g, u, v)) {
                numEdges++;
            }
        }

        InstrReset();
        Graph *TC_result = GraphComputeTransitiveClosure(g);
        printf("| %12d | %9d | %10lu |\n", i, numEdges, ITERATION);
        GraphDestroy(&TC_result);
        GraphDestroy(&g);
    }
}
int main(void) {
    InstrCalibrate();
    InstrName[0] =
        "Iterations"; // InstrName[0] will count the number iterations
    // What kind of graph is dig01?
    Graph *dig01 = GraphCreate(6, 1, 0);
    GraphAddEdge(dig01, 1, 2);
    GraphAddEdge(dig01, 1, 4);
    GraphAddEdge(dig01, 3, 4);
    printf("The graph:\n");
    // Displaying in DOT format
    GraphDisplayDOT(dig01);
    printf("\n");

    GraphCheckInvariants(dig01);

    Graph *tcdig01 = GraphComputeTransitiveClosure(dig01);
    printf("The transitive closure:\n");
    // Displaying in DOT format
    GraphDisplayDOT(tcdig01);
    printf("\n");

    GraphCheckInvariants(tcdig01);

    // Reading a directed graph from file
    FILE *file = fopen("DG_2.txt", "r");
    Graph *dig03 = GraphFromFile(file);
    fclose(file);
    // Displaying in DOT format
    GraphDisplayDOT(dig03);
    printf("\n");

    GraphCheckInvariants(dig03);

    Graph *tcdig03 = GraphComputeTransitiveClosure(dig03);
    printf("The transitive closure:\n");
    // Displaying in DOT format
    GraphDisplayDOT(tcdig03);
    printf("\n");

    GraphCheckInvariants(tcdig03);

    Graph *test1 = GraphCreate(5, 1, 0);
    Graph *test2 = GraphCreateComplete(5, 1);

    complexityTable1(test1);
    complexityTable1(test2);

    complexityTableGood();
    complexityTableBad();
    complexityTableRandom();

    GraphDestroy(&test1);
    GraphDestroy(&test2);

    GraphDestroy(&dig01);
    GraphDestroy(&dig03);

    GraphDestroy(&tcdig01);
    GraphDestroy(&tcdig03);

    return 0;
}
