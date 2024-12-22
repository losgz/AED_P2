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

// Compute the transitive closure of a directed graph
// Return the computed transitive closure as a directed graph
// Use the Bellman-Ford algorithm
Graph* GraphComputeTransitiveClosure(Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g));
  assert(GraphIsWeighted(g) == 0);

  // COMPLETE THE CODE

  //vou criar o grafo para o fecho transitivo
  Graph* transitiveClosure = GraphCreate(GraphGetNumVertices(g), 1, 0);

  assert(transitiveClosure != NULL);

  unsigned int numVertices = GraphGetNumVertices(g);

  //vou a cada vertice do grafo
  for (unsigned int source = 0; source < numVertices; source++) {
    //usar Bellman-Ford para determinar os vertices alcancaveis a partir da 'source'
    GraphBellmanFordAlg* distances = GraphBellmanFordAlgExecute(g, source);
    assert(distances != NULL);

    //percorrer os resultados bellman-ford
    for (unsigned int target = 0; target < numVertices; target++) {
      if (distances[target] != -1) {  //ver se o vertice é alcancavel
        if (source != target) {   //evitar loops (u -> u)
          GraphAddEdge(transitiveClosure, source, target);
        }
      }
    }

    //libertar memoria usada para os resultados bellman-ford
    free(distances);
  }

  return transitiveClosure;
}
