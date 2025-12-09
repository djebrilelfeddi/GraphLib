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

  std::unordered_set<int> vert1, vert2;
  vert1 = g.vertices();
  for(auto v : g)
    vert2.insert(v);
  assert(vert1 == vert2);

  vert2.clear();
  for(Graph<int>::iterator it = g.begin(); it != g.end(); ++it)
    vert2.insert(*it);
  assert(vert1 == vert2);

  std::cout << "Vous avez reussi !" << std::endl;

  return 0;
}
