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
  
  std::vector<int> bfs_list = g.bfs(11);
  std::cout << "bfs : ";
  for(int v : bfs_list)
    std::cout << v << " ";
  std::cout << std::endl;
  
  assert(bfs_list.size() == 12);
  assert(bfs_list.at(0) == 11);
  assert(bfs_list.at(1) == 12 || bfs_list.at(1) == 21);
  assert(bfs_list.at(2) == 12 || bfs_list.at(2) == 21);
  assert(bfs_list.back() == 43);
  
  std::vector<int> bfs_shortlist = g.bfs(43,3);
  std::cout << "bfs short: ";
  for(int v : bfs_shortlist)
    std::cout << v << " ";
  std::cout << std::endl;  
  
  assert(bfs_shortlist.size() == 3);
  assert(bfs_shortlist[0] == 43);
  assert(bfs_shortlist[1] == 33 || bfs_shortlist[1] == 42);
  assert(bfs_shortlist[2] == 33 || bfs_shortlist[2] == 42);
  
  std::cout << "Vous avez reussi !" << std::endl;
  
  return 0;
}
