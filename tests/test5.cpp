/**
 * @file test5.cpp
 * @brief Test suite for graph modification operations (remove, clear)
 * 
 * This test validates:
 * - Complete graph construction (K5, K100)
 * - Edge removal (removeEdge)
 * - Vertex removal (removeVertex) and cascade edge deletion
 * - Graph clearing (clear)
 * - Degree, vertex count, and edge count consistency after modifications
 * - Negative vertex values handling
 */

#include <iostream>
#include <cassert>
#include "graph.hpp"

int main() {
    Graph<int> g;

    // =========================================================================
    // TEST 1: Build complete graph K5
    // =========================================================================
    // K5: https://en.wikipedia.org/wiki/Complete_graph
    // Every vertex connected to every other vertex
    
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i != j)
                g.addEdge(i, j);
        }
    }

    assert(g.containsVertex(4) && "Vertex 4 should exist in K5");
    assert(g.containsEdge(0, 1) && "Edge 0-1 should exist in K5");
    assert(!g.containsVertex(5) && "Vertex 5 should NOT exist in K5");
    assert(g.countVertices() == 5 && "K5 should have 5 vertices");
    assert(g.countEdges() == 5 * 4 / 2 && "K5 should have 10 edges");
    assert(g.maxDegree() == 4 && "K5 max degree should be 4");

    // =========================================================================
    // TEST 2: Transform K5 to K3,2 by removing edges
    // =========================================================================
    // K3,2: Complete bipartite graph (3 vertices on one side, 2 on other)
    // Remove edges between vertices of same parity
    
    for (int i = 0; i < 5 - 1; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (i % 2 == j % 2)
                g.removeEdge(i, j);
        }
    }

    assert(!g.containsEdge(0, 2) && "Edge 0-2 should be removed (same parity)");
    assert(!g.containsEdge(1, 3) && "Edge 1-3 should be removed (same parity)");
    assert(g.containsEdge(0, 1) && "Edge 0-1 should remain (different parity)");
    assert(g.countVertices() == 5 && "Vertex count should still be 5");
    assert(g.countEdges() == 3 * 2 && "K3,2 should have 6 edges");
    assert(g.maxDegree() == 3 && "K3,2 max degree should be 3");

    // =========================================================================
    // TEST 3: Remove vertex to get K2,2
    // =========================================================================
    g.removeVertex(4);

    assert(!g.containsEdge(1, 4) && "Edges to removed vertex should be gone");
    assert(g.countVertices() == 4 && "K2,2 should have 4 vertices");
    assert(g.countEdges() == 4 && "K2,2 should have 4 edges");
    assert(g.maxDegree() == 2 && "K2,2 max degree should be 2");

    // =========================================================================
    // TEST 4: Clear graph and build K100
    // =========================================================================
    g.clear();

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (i != j)
                g.addEdge(i, j);
        }
    }

    // =========================================================================
    // TEST 5: Remove every even vertex to get K50
    // =========================================================================
    for (int i = 0; i < 100; i += 2) {
        g.removeVertex(i);
    }

    assert(g.countEdges() == 50 * 49 / 2 && "K50 should have 1225 edges");
    assert(g.maxDegree() == 49 && "K50 max degree should be 49");

    // =========================================================================
    // TEST 6: Verify negative vertex values work correctly
    // =========================================================================
    g.clear();
    g.addEdge(-1, -5);

    assert(g.maxDegree() == 1 && "Graph with one edge should have max degree 1");
    assert(g.countVertices() == 2 && "Graph should have 2 vertices");
    assert(g.countEdges() == 1 && "Graph should have 1 edge");

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
