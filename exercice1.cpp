#include <iostream>
#include <cassert>
#include "graph.hpp" // C'est a vous de l'ecrire

int main() {
  Graph<std::string> g; // C'est votre classe
  
  // Morceau du graphe de https://fr.wikipedia.org/wiki/Graphe_de_Kneser#/media/Fichier:Kneser-5-2.svg
  g.addVertex("12");
  g.addVertex("34");
  g.addVertex("35");
  g.addVertex("45");
  assert(g.containsVertex("12"));
  assert(g.containsVertex("45"));
  assert(!g.containsVertex("15"));

  assert(!g.containsEdge("12","45"));
  g.addEdge("12","45");
  g.addEdge("12","34");
  g.addEdge("12","35");
  assert(g.containsEdge("12","45"));
  assert(g.containsEdge("45","12"));
  assert(!g.containsEdge("34","35"));
  assert(!g.containsEdge("34","15"));
  
  g.addEdge("34","15");
  g.addEdge("15","23");
  g.addEdge("45","23");
  assert(g.containsEdge("15","34"));
  assert(g.containsEdge("34","15"));
  assert(g.containsVertex("15"));
  assert(g.containsVertex("23"));
  assert(!g.containsEdge("98","99"));
  
  std::cout << "Vous avez reussi !" << std::endl;
  
  return 0;
}
