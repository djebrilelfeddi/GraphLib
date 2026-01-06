#include <iostream>
#include <cassert>
#include "graph.hpp" // C'est a vous de l'ecrire

int main() {
  Graph<int> g; // C'est votre classe

  // Grille 4x3
  for(int x = 1; x <= 4; x++) {
    for(int y = 1; y <= 3; y++) {
      if(x <= 3)
        g.addEdge(10*x+y, 10*(x+1)+y); // Horizontal edge
      if(y <= 2)
        g.addEdge(10*x+y, 10*x+y+1); // Vertical edge
    }
  }

  assert(g.degree(11) == 2);
  assert(g.degree(12) == 3);
  assert(g.degree(22) == 4);

  assert(g.maxDegree() == 4);
  assert(g.countVertices() == 12);
  assert(g.countEdges() == 17);

  std::cout << "Vous avez reussi !" << std::endl;

  return 0;
}
