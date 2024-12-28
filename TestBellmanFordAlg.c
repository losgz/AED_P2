//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira, Joao Manuel Rodrigues - Dec 2024
//
// Testing the Bellman-Ford algorithm
//

#include <assert.h>
#include <stdio.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"
#include <stdlib.h> 
#include <time.h>

#define ITERATION InstrCount[0]

void ComplexityTable(Graph *g) {
    int numVertices = GraphGetNumVertices(g);
    int numEdges = GraphGetNumEdges(g);
    printf("Num Vertices: %d\n", numVertices);
    printf("\n| Vertex | Num Edges | Iterations |\n");
    for (int i = 0; i < numVertices; i++) {
        InstrReset();
        GraphBellmanFordAlg *BF_result = GraphBellmanFordAlgExecute(g, i);

        printf("| %6d | %9d | %10lu |\n", i, numEdges, ITERATION);

        GraphBellmanFordAlgDestroy(&BF_result);
    }
    printf("\n");
}

void complexityTableGood() {
    printf("\nBest Case");
    printf("\n| Num Vertices | Num Edges | Iterations |\n");
    for (int i = 3; i < 10; i++) {
        Graph *g = GraphCreate(i, 1, 0);
        int numEdges = GraphGetNumEdges(g);

        InstrReset();
        GraphBellmanFordAlg *BF_result = GraphBellmanFordAlgExecute(g, 0);
        printf("| %12d | %9d | %10lu |\n", i, numEdges, ITERATION);
        GraphBellmanFordAlgDestroy(&BF_result);
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
        GraphBellmanFordAlg *BF_result = GraphBellmanFordAlgExecute(g, 0);
        printf("| %12d | %9d | %10lu |\n", i, numEdges, ITERATION);
        GraphBellmanFordAlgDestroy(&BF_result);
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
        GraphBellmanFordAlg *BF_result = GraphBellmanFordAlgExecute(g, 0);
        printf("| %12d | %9d | %10lu |\n", i, numEdges, ITERATION);
        GraphBellmanFordAlgDestroy(&BF_result);
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

    // Bellman-Ford Algorithm

    // Consider each vertex as a start vertex
    for (unsigned int i = 0; i < 6; i++) {
        GraphBellmanFordAlg *BF_result = GraphBellmanFordAlgExecute(dig01, i);

        printf("The shortest path tree rooted at %u\n", i);
        GraphBellmanFordAlgDisplayDOT(BF_result);
        printf("\n");

        GraphBellmanFordAlgDestroy(&BF_result);
    }

    // What kind of graph is g01?
    Graph *g01 = GraphCreate(6, 0, 0);
    GraphAddEdge(g01, 0, 5);
    GraphAddEdge(g01, 2, 4);
    GraphAddEdge(g01, 2, 3);
    GraphAddEdge(g01, 1, 2);
    GraphAddEdge(g01, 0, 1);
    GraphAddEdge(g01, 3, 4);
    GraphAddEdge(g01, 3, 5);
    GraphAddEdge(g01, 0, 2);
    printf("The graph:\n");
    // Displaying in DOT format
    GraphDisplayDOT(g01);
    printf("\n");

    GraphCheckInvariants(g01);

    // Bellman-Ford Algorithm

    // Consider each vertex as a start vertex
    for (unsigned int i = 0; i < 6; i++) {
        GraphBellmanFordAlg *BF_result = GraphBellmanFordAlgExecute(g01, i);

        printf("The shortest path tree rooted at %u\n", i);
        GraphBellmanFordAlgDisplayDOT(BF_result);
        printf("\n");

        GraphBellmanFordAlgDestroy(&BF_result);
    }

    // Reading a directed graph from file
    FILE *file = fopen("DG_2.txt", "r");
    Graph *dig03 = GraphFromFile(file);
    fclose(file);
    // Displaying in DOT format
    GraphDisplayDOT(dig03);
    printf("\n");

    GraphCheckInvariants(dig03);

    // Bellman-Ford Algorithm

    // Consider each vertex as a start vertex
    for (unsigned int i = 0; i < GraphGetNumVertices(dig03); i++) {
        GraphBellmanFordAlg *BF_result = GraphBellmanFordAlgExecute(dig03, i);

        printf("The shortest path tree rooted at %u\n", i);
        GraphBellmanFordAlgDisplayDOT(BF_result);
        printf("\n");

        GraphBellmanFordAlgDestroy(&BF_result);
    }

    Graph *test1 = GraphCreate(5, 0, 0);
    Graph *test2 = GraphCreate(5, 0, 0);
    GraphAddEdge(test2, 0, 1);
    GraphAddEdge(test2, 1, 2);
    GraphAddEdge(test2, 2, 3);
    GraphAddEdge(test2, 3, 4);

    Graph *test3 = GraphCreateComplete(5, 0);

    ComplexityTable(test1);
    ComplexityTable(test2);
    ComplexityTable(test3);

    complexityTableGood();
    complexityTableBad();
    complexityTableRandom();

    GraphDestroy(&test1);
    GraphDestroy(&test2);
    GraphDestroy(&test3);
    GraphDestroy(&g01);
    GraphDestroy(&dig01);
    GraphDestroy(&dig03);

    return 0;
}
