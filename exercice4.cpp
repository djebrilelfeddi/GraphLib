#include <iostream>
#include <cassert>
#include "graph.hpp" // C'est a vous de l'ecrire

int main() {
  Graph<int> g; // C'est votre classe
  std::unordered_set<std::pair<int,int>> edges;

  // Grille 4x3
  for(int x = 1; x <= 4; x++) {
    for(int y = 1; y <= 3; y++) {
      if(x <= 3) {
        g.addEdge(10*x+y, 10*(x+1)+y); // Horizontal edge
        edges.insert(std::make_pair(10*x+y, 10*(x+1)+y));
      }
      if(y <= 2) {
        g.addEdge(10*x+y, 10*x+y+1); // Vertical edge
        edges.insert(std::make_pair(10*x+y, 10*x+y+1));
      }
    }
  }

  std::unordered_set<int> s = {11,12,13,21,22,23,31,32,33,41,42,43};
  assert(g.vertices() == s);

  assert(g.edges() == edges);

  assert(g.neighbors(11) == std::unordered_set<int>({12,21}));
  assert(g.neighbors(22) == std::unordered_set<int>({12,21,23,32}));
  assert(g.closedNeighbors(11) == std::unordered_set<int>({11,12,21}));
  assert(g.closedNeighbors(22) == std::unordered_set<int>({22,12,21,23,32}));

  std::cout << "Vous avez reussi !" << std::endl;

  return 0;
}
