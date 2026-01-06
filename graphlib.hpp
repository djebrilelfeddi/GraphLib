/**
 * @file graphlib.hpp
 * @brief Undirected graph implementation using adjacency list
 * @author EL FEDDI DJEBRIL
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>
#include <queue>
#include <optional>
#include <type_traits>

// Specialization of std::hash for std::pair
namespace std {
    template <typename T1, typename T2>
    struct hash<std::pair<T1, T2>> {
        size_t operator()(const std::pair<T1, T2>& p) const {
            size_t h1 = std::hash<T1>{}(p.first);
            size_t h2 = std::hash<T2>{}(p.second);
            // using boost hash_combine method
            // https://www.boost.org/doc/libs/latest/libs/container_hash/doc/html/hash.html#ref_hash_combine
            return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
        }
    };
}

/**
 * @brief Class representing an undirected graph
 * @tparam Vertex Vertex type
 * @tparam Hash function (default: std::hash<Vertex>)
 */
template<typename Vertex, typename Hash=std::hash<Vertex>>
class Graph {
private:
    // Optimization: pass primitive types by value, complex ones by const ref
    using VertexParam = std::conditional_t<std::is_fundamental_v<Vertex>, Vertex, const Vertex&>;

    std::unordered_map<Vertex, std::unordered_set<Vertex, Hash>, Hash> adj;

public:
    Graph() = default;

    /**
     * @brief Adds a vertex to the graph
     * @param v The vertex to add
     * @note If the vertex already exists, the operation has no effect
     * @note Complexity: O(1) amortized
     */
    void addVertex(const VertexParam v) {
        adj.try_emplace(v);
    }

    /**
     * @brief Adds an undirected edge between two vertices
     * @param u First vertex of the edge
     * @param v Second vertex of the edge
     * @note Vertices are automatically created if they don't exist
     * @note If the edge already exists, the operation has no effect
     * @note Self-loops (u == v) are silently ignored
     * @note Complexity: O(1) amortized
     */
    void addEdge(const VertexParam u, const VertexParam v) {
        if (u == v) return;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    /**
     * @brief Checks if a vertex exists in the graph
     * @param v The vertex to search for
     * @return true if the vertex exists, false otherwise
     * @note Complexity: O(1) amortized
     */
    bool containsVertex(const VertexParam v) const {
        return adj.contains(v);
    }

    /**
     * @brief Checks if an edge exists between two vertices
     * @param u First vertex of the edge
     * @param v Second vertex of the edge
     * @return true if the edge exists, false otherwise
     * @note Self-loops (u == v) always return false
     * @note Complexity: O(1) amortized
     */
    bool containsEdge(const VertexParam u, const VertexParam v) const {
        if (u == v) return false;
        
        // Optimization: using find() instead of contains() + at() avoids
        // computing the hash twice. The iterator retains the bucket position.
        auto it = adj.find(u);
        return (it != adj.end()) && it->second.contains(v);
    }

    /**
     * @brief Returns the degree (number of neighbors) of a vertex
     * @param v The vertex to check
     * @return The degree of v, or 0 if v is not in the graph
     * @note Complexity: O(1) amortized
     */
    size_t degree(const VertexParam v) const {
        auto it = adj.find(v);
        return (it != adj.end()) ? it->second.size() : 0;
    }

    /**
     * @brief Returns the maximum degree in the graph
     * @return The maximum degree, or 0 if the graph is empty
     * @note Complexity: O(n) where n is the number of vertices
     */
    size_t maxDegree() const {
        size_t max_d = 0;
        for (const auto& [_, neighbors] : adj) {
            if (neighbors.size() > max_d) max_d = neighbors.size();
        }
        return max_d;
    }

    /**
     * @brief Returns the number of vertices in the graph
     * @return The number of vertices
     * @note Complexity: O(1)
     */
    size_t countVertices() const {
        return adj.size();
    }

    /**
     * @brief Returns the number of edges in the graph
     * @return The number of edges
     * @note Here i used https://en.wikipedia.org/wiki/Handshaking_lemma as a reference
     * @note Complexity: O(n) where n is the number of vertices
     */
    size_t countEdges() const {
        size_t total = 0;
        for (const auto& [_, neighbors] : adj) {
            total += neighbors.size();
        }
        return total / 2;
    }

    /**
     * @brief Removes an edge between two vertices
     * @param u First vertex of the edge
     * @param v Second vertex of the edge
     * @note If the edge does not exist, the operation has no effect
     * @note Complexity: O(1) amortized
     */
    void removeEdge(const VertexParam u, const VertexParam v) {
        if (u == v) return; 
        
        auto itU = adj.find(u);
        if (itU != adj.end()) itU->second.erase(v);
        
        auto itV = adj.find(v);
        if (itV != adj.end()) itV->second.erase(u);
    }

    /**
     * @brief Removes a vertex from the graph and all incident edges
     * @param v The vertex to remove
     * @note If the vertex does not exist, the operation has no effect
     * @note Complexity: O(d) where d is the degree of v
     */
    void removeVertex(const VertexParam v) {
        auto it = adj.find(v);
        if (it == adj.end()) return;
        
        for (const auto& neighbor : it->second) {
            adj[neighbor].erase(v);
        }
        adj.erase(it);
    }

    /**
     * @brief Removes all vertices and edges from the graph
     * @note Post-condition: countVertices() == 0 && countEdges() == 0
     * @note Complexity: O(n + m) linear in the size of the graph
     */
    void clear() {
        adj.clear();
    }

    /**
     * @brief Returns the set of all vertices in the graph
     * @return An unordered_set containing all vertices
     * @note Complexity: O(n) where n is the number of vertices
     */
    std::unordered_set<Vertex> vertices() const {
        std::unordered_set<Vertex> res;
        res.reserve(adj.size()); //optimization: avoid reallocations
        for (const auto& [v, _] : adj) {
            res.insert(v);
        }
        return res;
    }

    /**
     * @brief Returns the set of all edges in the graph
     * @return An unordered_set of pairs representing edges (with u < v)
     * @note Complexity: O(m) where m is the number of edges
     */
    std::unordered_set<std::pair<Vertex, Vertex>> edges() const {
        std::unordered_set<std::pair<Vertex, Vertex>> res;
        for (const auto& [u, neighbors] : adj) {
            for (const auto& v : neighbors) {
                if (u < v) {
                    res.emplace(u, v);
                }
            }
        }
        return res;
    }

    /**
     * @brief Returns the set of neighbors of a vertex
     * @param v The vertex to check
     * @return The set of neighbors
     * @note Returns an empty set if v is not in the graph
     * @note Complexity: O(1)
     */
    const std::unordered_set<Vertex>& neighbors(const VertexParam v) const {
        static const std::unordered_set<Vertex> empty;
        auto it = adj.find(v);
        return (it != adj.end()) ? it->second : empty;
    }

    /**
     * @brief Returns the closed neighborhood of a vertex (neighbors + vertex itself)
     * @param v The vertex to check
     * @return The set of neighbors including v
     * @note Complexity: O(d) where d is the degree of v
     */
    std::unordered_set<Vertex> closedNeighbors(const VertexParam v) const {
        auto it = adj.find(v);
        if (it == adj.end()) return {};
        
        std::unordered_set<Vertex> res = it->second;
        res.insert(v);
        return res;
    }

    /**
     * @brief Performs a Breadth-First Search (BFS) starting from a vertex
     * @param v The starting vertex
     * @param maxv Maximum number of vertices to visit (0 for unlimited)
     * @return A vector of visited vertices in BFS order
     * @note Here i used https://en.wikipedia.org/wiki/Breadth-first_search as a reference
     * @note Complexity: O(V + E) where V is visited vertices and E visited edges
     */
    std::vector<Vertex> bfs(const VertexParam v, size_t maxv = 0) const {
        std::vector<Vertex> result;
        if (!containsVertex(v)) return result;
        
        if (maxv > 0) result.reserve(maxv); // Pre-allocate if limit is known (optimization)
        
        std::unordered_set<Vertex, Hash> seen;
        std::queue<Vertex> pending;
        
        pending.push(v);
        seen.insert(v);
        
        while (!pending.empty()) {
            if (maxv > 0 && result.size() >= maxv) break;
            
            Vertex current = pending.front();
            pending.pop();
            result.emplace_back(current);
            
            auto it = adj.find(current);
            if (it == adj.end()) continue;
            
            for (const Vertex& next : it->second) {
                if (seen.insert(next).second) {
                    pending.push(next);
                }
            }
        }
        return result;
    }

    /**
     * @brief Calculates the shortest path distance between two vertices
     * @param u Start vertex
     * @param v End vertex
     * @return The distance if a path exists, std::nullopt otherwise
     * @note Complexity: O(V + E) for BFS traversal
     */
    std::optional<int> distance(const VertexParam u, const VertexParam v) const {
        if (!containsVertex(u) || !containsVertex(v)) return std::nullopt;
        if (u == v) return 0;
        
        std::unordered_set<Vertex, Hash> seen;
        std::queue<Vertex> level;
        int depth = 0;
        
        level.push(u);
        seen.insert(u);
        
        while (!level.empty()) {
            depth++;
            int level_size = level.size();
            
            for (int i = 0; i < level_size; i++) {
                Vertex current = level.front();
                level.pop();
                
                auto it = adj.find(current);
                if (it == adj.end()) continue;
                
                for (const Vertex& neighbor : it->second) {
                    if (neighbor == v) return depth;
                    if (seen.insert(neighbor).second) {
                        level.push(neighbor);
                    }
                }
            }
        }
        return std::nullopt;
    }

    /**
     * @brief Iterator class to iterate over graph vertices
     * Satisfies C++ LegacyInputIterator requirements that you can find here https://en.cppreference.com/w/cpp/named_req/InputIterator
     */
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Vertex;
        using difference_type = std::ptrdiff_t;
        using pointer = const Vertex*;
        using reference = const Vertex&;

    private:
        typename std::unordered_map<Vertex, std::unordered_set<Vertex, Hash>, Hash>::const_iterator it;

    public:
        iterator(typename std::unordered_map<Vertex, std::unordered_set<Vertex, Hash>, Hash>::const_iterator i) : it(i) {}
        
        reference operator*() const { return it->first; }
        pointer operator->() const { return &(it->first); }
        
        iterator& operator++() { ++it; return *this; }
        
        iterator operator++(int) { 
            iterator temp = *this; 
            ++(*this); 
            return temp; 
        }
        
        bool operator==(const iterator& other) const { return it == other.it; }
        bool operator!=(const iterator& other) const { return it != other.it; }
    };

    iterator begin() const { return iterator(adj.begin()); }
    iterator end() const { return iterator(adj.end()); }
};

#endif