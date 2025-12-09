#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <unordered_set>

template<typename Vertex>
class Graph {
private:
    std::unordered_map<Vertex, std::unordered_set<Vertex>> adjacencyList;

public:
    Graph() = default;

    // Ajoute le sommet v. Si le sommet existe deja, ça ne fait rien. O(1)
    void addVertex(Vertex v);

    // Ajoute une arete entre u et v. O(1)
    void addEdge(Vertex u, Vertex v);

    // Renvoie true si le sommet v est dans le graphe. O(1)
    bool containsVertex(Vertex v) const;

    // Renvoie true si l'arete uv est dans le graphe. O(1)
    bool containsEdge(Vertex u, Vertex v) const;
};

#endif