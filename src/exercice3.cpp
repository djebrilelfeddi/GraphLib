#include <iostream>
#include <cassert>
#include "graph.hpp" // C'est a vous de l'ecrire

int main() {
  Graph<int> g; // C'est votre classe

  // Graphe K5 https://en.wikipedia.org/wiki/Complete_graph

  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      if(i!=j)
        g.addEdge(i,j);
    }
  }

  assert(g.containsVertex(4));
  assert(g.containsEdge(0,1));
  assert(!g.containsVertex(5));
  assert(g.countVertices() == 5);
  assert(g.countEdges() == 5*4/2);
  assert(g.maxDegree() == 4);

  // Graphe K3,2 https://fr.wikipedia.org/wiki/Graphe_complet

  for(int i = 0; i < 5-1; i++) {
    for(int j = i+1; j < 5; j++) {
      if(i%2 == j%2)
        g.removeEdge(i,j);
    }
  }

  assert(!g.containsEdge(0,2));
  assert(!g.containsEdge(1,3));
  assert(g.containsEdge(0,1));
  assert(g.countVertices() == 5);
  assert(g.countEdges() == 3*2);
  assert(g.maxDegree() == 3);

  // Graphe K2,2 https://fr.wikipedia.org/wiki/Graphe_complet
  g.removeVertex(4);
  assert(!g.containsEdge(1,4));
  assert(g.countVertices() == 4);
  assert(g.countEdges() == 4);
  assert(g.maxDegree() == 2);

  g.clear();

  // Graphe K100 https://en.wikipedia.org/wiki/Complete_graph
  for(int i = 0; i < 100; i++) {
    for(int j = 0; j < 100; j++) {
      if(i!=j)
        g.addEdge(i,j);
    }
  }

  // Graphe K50
  for(int i = 0; i < 100; i += 2) {
    g.removeVertex(i);
  }

  assert(g.countEdges() == 50*49/2);
  assert(g.maxDegree() == 49);

  g.clear();
  g.addEdge(-1, -5);
  assert(g.maxDegree() == 1);
  assert(g.countVertices() == 2);
  assert(g.countEdges() == 1);

  std::cout << "Vous avez reussi !" << std::endl;

  return 0;
}
