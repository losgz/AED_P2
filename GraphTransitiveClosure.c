//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira - Dec 2024
//
// GraphTransitiveClosure - Transitive Closure of a directed graph
//

// Student Name : Eduardo José Farinha do Rosário
// Student Number : 119234
// Student Name : Henrique Marques Lopes
// Student Number : 119954

/*** COMPLETE THE GraphComputeTransitiveClosure FUNCTION ***/

#include "GraphTransitiveClosure.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "GraphBellmanFordAlg.h"
#include "instrumentation.h"

#define ITERATION InstrCount[0]

// Compute the transitive closure of a directed graph
// Return the computed transitive closure as a directed graph
// Use the Bellman-Ford algorithm
Graph *GraphComputeTransitiveClosure(Graph *g) {
    assert(g != NULL);
    assert(GraphIsDigraph(g));
    assert(GraphIsWeighted(g) == 0);

    // COMPLETE THE CODE

    // vou criar o grafo para o fecho transitivo
    Graph *transitiveClosure = GraphCreate(GraphGetNumVertices(g), 1, 0);

    assert(transitiveClosure != NULL);

    unsigned int numVertices = GraphGetNumVertices(g);

    // vou a cada vertice do grafo
    for (unsigned int u = 0; u < numVertices; u++) {
        // usar Bellman-Ford para determinar os vertices alcancaveis a partir da
        // 'source'
        GraphBellmanFordAlg *bellmanGraph =
            GraphBellmanFordAlgExecute(g, u);
        assert(bellmanGraph != NULL);

        // percorrer os resultados bellman-ford
        for (unsigned int v = 0; v < numVertices; v++) {
            ITERATION++;
            // ver se o vertice é alcancavel
            if (GraphBellmanFordAlgReached(bellmanGraph, v) && u != v) {
                GraphAddEdge(transitiveClosure, u, v);
            }
        }

        // libertar memoria usada para os resultados bellman-ford
        GraphBellmanFordAlgDestroy(&bellmanGraph);
    }

    return transitiveClosure;
}
