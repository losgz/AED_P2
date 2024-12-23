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

#define ITERATION InstrCount[0]

void complexityTable(Graph *g) {
    int numVertices = GraphGetNumVertices(g);
    int numEdges = GraphGetNumEdges(g);

    printf("\n| Vertex | Num Edges | Iterations |\n");
    for (int i = 0; i < numVertices; i++) {
        InstrReset();
        Graph *TC_result = GraphComputeTransitiveClosure(g);
        printf("| %6d | %9d | %10lu |\n", numVertices, numEdges, ITERATION);
        GraphDestroy(&TC_result);
    }

    printf("| %6c | %9c | %10c |\n", ' ', ' ', ' ');
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

    complexityTable(dig01);
    complexityTable(dig03);

    GraphDestroy(&dig01);
    GraphDestroy(&dig03);

    GraphDestroy(&tcdig01);
    GraphDestroy(&tcdig03);

    return 0;
}
