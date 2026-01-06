// g++ -std=c++20 -o boosttest -Wall boosttest.cpp -lboost_unit_test_framework

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MainTests
#include <boost/test/unit_test.hpp>

#include <iostream>
#include "graph.hpp" // C'est a vous de l'ecrire

BOOST_AUTO_TEST_CASE(Test1) {
  Graph<std::string> g; // C'est votre classe

  // Morceau du graphe de https://fr.wikipedia.org/wiki/Graphe_de_Kneser#/media/Fichier:Kneser-5-2.svg
  g.addVertex("12");
  g.addVertex("34");
  g.addVertex("35");
  g.addVertex("45");
  BOOST_CHECK(g.containsVertex("12"));
  BOOST_CHECK(g.containsVertex("45"));
  BOOST_CHECK(!g.containsVertex("15"));
  BOOST_CHECK(!g.containsEdge("12","45"));

  g.addEdge("12","45");
  g.addEdge("12","34");
  g.addEdge("12","35");
  BOOST_CHECK(g.containsEdge("12","45"));
  BOOST_CHECK(g.containsEdge("45","12"));
  BOOST_CHECK(!g.containsEdge("34","35"));
  BOOST_CHECK(!g.containsEdge("34","15"));
  
  g.addEdge("34","15");
  g.addEdge("15","23");
  g.addEdge("45","23");
  BOOST_CHECK(g.containsEdge("15","34"));
  BOOST_CHECK(g.containsEdge("34","15"));
  BOOST_CHECK(g.containsVertex("15"));
  BOOST_CHECK(g.containsVertex("23"));
  BOOST_CHECK(!g.containsEdge("98","99"));
}

BOOST_AUTO_TEST_CASE(Test2) {
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

  BOOST_CHECK(g.degree(11) == 2);
  BOOST_CHECK(g.degree(12) == 3);
  BOOST_CHECK(g.degree(22) == 4);

  BOOST_CHECK(g.maxDegree() == 4);
  BOOST_CHECK(g.countVertices() == 12);
  BOOST_CHECK(g.countEdges() == 17);
}

BOOST_AUTO_TEST_CASE(Test3) {
  Graph<int> g; // C'est votre classe

  // Graphe K5 https://en.wikipedia.org/wiki/Complete_graph

  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      if(i!=j)
        g.addEdge(i,j);
    }
  }

  BOOST_CHECK(g.containsVertex(4));
  BOOST_CHECK(g.containsEdge(0,1));
  BOOST_CHECK(!g.containsVertex(5));
  BOOST_CHECK(g.countVertices() == 5);
  BOOST_CHECK(g.countEdges() == 5*4/2);
  BOOST_CHECK(g.maxDegree() == 4);

  // Graphe K3,2 https://fr.wikipedia.org/wiki/Graphe_complet

  for(int i = 0; i < 5-1; i++) {
    for(int j = i+1; j < 5; j++) {
      if(i%2 == j%2)
        g.removeEdge(i,j);
    }
  }

  BOOST_CHECK(!g.containsEdge(0,2));
  BOOST_CHECK(!g.containsEdge(1,3));
  BOOST_CHECK(g.containsEdge(0,1));
  BOOST_CHECK(g.countVertices() == 5);
  BOOST_CHECK(g.countEdges() == 3*2);
  BOOST_CHECK(g.maxDegree() == 3);

  // Graphe K2,2 https://fr.wikipedia.org/wiki/Graphe_complet
  g.removeVertex(4);
  BOOST_CHECK(!g.containsEdge(1,4));
  BOOST_CHECK(g.countVertices() == 4);
  BOOST_CHECK(g.countEdges() == 4);
  BOOST_CHECK(g.maxDegree() == 2);

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

  BOOST_CHECK(g.countEdges() == 50*49/2);
  BOOST_CHECK(g.maxDegree() == 49);

  g.clear();
  g.addEdge(-1, -5);
  BOOST_CHECK(g.maxDegree() == 1);
  BOOST_CHECK(g.countVertices() == 2);
  BOOST_CHECK(g.countEdges() == 1);
}

BOOST_AUTO_TEST_CASE(Test4) {
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
  BOOST_CHECK(g.vertices() == s);

  BOOST_CHECK(g.edges() == edges);

  BOOST_CHECK(g.neighbors(11) == std::unordered_set<int>({12,21}));
  BOOST_CHECK(g.neighbors(22) == std::unordered_set<int>({12,21,23,32}));
  BOOST_CHECK(g.closedNeighbors(11) == std::unordered_set<int>({11,12,21}));
  BOOST_CHECK(g.closedNeighbors(22) == std::unordered_set<int>({22,12,21,23,32}));

}

BOOST_AUTO_TEST_CASE(Test5) {
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

  BOOST_CHECK(bfs_list.size() == 12);
  BOOST_CHECK(bfs_list.at(0) == 11);
  BOOST_CHECK(bfs_list.at(1) == 12 || bfs_list.at(1) == 21);
  BOOST_CHECK(bfs_list.at(2) == 12 || bfs_list.at(2) == 21);
  BOOST_CHECK(bfs_list.back() == 43);

  std::vector<int> bfs_shortlist = g.bfs(43,3);
  std::cout << "bfs short: ";
  for(int v : bfs_shortlist)
    std::cout << v << " ";
  std::cout << std::endl;

  BOOST_CHECK(bfs_shortlist.size() == 3);
  BOOST_CHECK(bfs_shortlist[0] == 43);
  BOOST_CHECK(bfs_shortlist[1] == 33 || bfs_shortlist[1] == 42);
  BOOST_CHECK(bfs_shortlist[2] == 33 || bfs_shortlist[2] == 42);

  BOOST_CHECK(*g.distance(11,11) == 0);
  BOOST_CHECK(*g.distance(11,32) == 3);
  BOOST_CHECK(!g.distance(999,11).has_value());
  g.addEdge(998,999);
  BOOST_CHECK(!g.distance(999,11).has_value());
  g.addEdge(998,11);
  BOOST_CHECK(*g.distance(999,11) == 2);

}

BOOST_AUTO_TEST_CASE(Test6) {
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
  BOOST_CHECK(vert1 == vert2);

  vert2.clear();
  for(Graph<int>::iterator it = g.begin(); it != g.end(); ++it)
    vert2.insert(*it);
  BOOST_CHECK(vert1 == vert2);
}
