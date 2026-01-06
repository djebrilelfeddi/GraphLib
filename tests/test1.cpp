/**
 * @file test1.cpp
 * @brief Test suite for basic vertex and edge operations
 * 
 * This test validates:
 * - Adding vertices to the graph
 * - Checking vertex existence (containsVertex)
 * - Adding edges between vertices
 * - Checking edge existence (containsEdge)
 * - Automatic vertex creation when adding edges
 * - Edge symmetry (undirected graph property)
 */

#include <iostream>
#include <cassert>
#include "graphlib.hpp"

int main() {
    Graph<std::string> g;

    // =========================================================================
    // TEST 1: Adding vertices explicitly
    // =========================================================================
    // Based on Kneser graph K(5,2): https://en.wikipedia.org/wiki/Kneser_graph
    g.addVertex("12");
    g.addVertex("34");
    g.addVertex("35");
    g.addVertex("45");

    // Verify vertices were added correctly
    assert(g.containsVertex("12") && "Vertex '12' should exist");
    assert(g.containsVertex("45") && "Vertex '45' should exist");
    assert(!g.containsVertex("15") && "Vertex '15' should NOT exist yet");

    // =========================================================================
    // TEST 2: Adding edges and verifying symmetry
    // =========================================================================
    // Before adding edge, it should not exist
    assert(!g.containsEdge("12", "45") && "Edge 12-45 should NOT exist yet");

    // Add edges from vertex "12"
    g.addEdge("12", "45");
    g.addEdge("12", "34");
    g.addEdge("12", "35");

    // Verify edge existence (both directions for undirected graph)
    assert(g.containsEdge("12", "45") && "Edge 12-45 should exist");
    assert(g.containsEdge("45", "12") && "Edge 45-12 should exist (symmetry)");
    assert(!g.containsEdge("34", "35") && "Edge 34-35 should NOT exist");
    assert(!g.containsEdge("34", "15") && "Edge to non-existent vertex should not exist");

    // =========================================================================
    // TEST 3: Automatic vertex creation via addEdge
    // =========================================================================
    // Vertices "15" and "23" don't exist yet - they should be created automatically
    g.addEdge("34", "15");
    g.addEdge("15", "23");
    g.addEdge("45", "23");

    // Verify edges were created
    assert(g.containsEdge("15", "34") && "Edge 15-34 should exist");
    assert(g.containsEdge("34", "15") && "Edge 34-15 should exist (symmetry)");

    // Verify vertices were auto-created
    assert(g.containsVertex("15") && "Vertex '15' should have been auto-created");
    assert(g.containsVertex("23") && "Vertex '23' should have been auto-created");

    // =========================================================================
    // TEST 4: Non-existent edges
    // =========================================================================
    assert(!g.containsEdge("98", "99") && "Edge between non-existent vertices should not exist");

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
