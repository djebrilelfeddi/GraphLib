/**
 * @file boosttests.cpp
 * @brief Comprehensive Boost.Test suite for Graph class
 * @author EL FEDDI DJEBRIL
 * 
 * This test suite validates all Graph class functionality using Boost.Test framework.
 * Compile with: g++ -std=c++20 -o boosttests -Wall boosttests.cpp -lboost_unit_test_framework
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE GraphLibTests
#include <boost/test/unit_test.hpp>

#include <iostream>
#include "graph.hpp"

// =============================================================================
// TEST SUITE 1: Basic Vertex and Edge Operations
// =============================================================================
// Tests: addVertex, containsVertex, addEdge, containsEdge
// Validates basic graph construction and query operations

BOOST_AUTO_TEST_CASE(BasicVertexAndEdgeOperations) {
    Graph<std::string> g;

    // --- Test: Adding vertices explicitly ---
    // Based on Kneser graph K(5,2): https://en.wikipedia.org/wiki/Kneser_graph
    g.addVertex("12");
    g.addVertex("34");
    g.addVertex("35");
    g.addVertex("45");
    
    BOOST_CHECK_MESSAGE(g.containsVertex("12"), "Vertex '12' should exist");
    BOOST_CHECK_MESSAGE(g.containsVertex("45"), "Vertex '45' should exist");
    BOOST_CHECK_MESSAGE(!g.containsVertex("15"), "Vertex '15' should NOT exist yet");
    BOOST_CHECK_MESSAGE(!g.containsEdge("12", "45"), "Edge 12-45 should NOT exist yet");

    // --- Test: Adding edges and verifying symmetry ---
    g.addEdge("12", "45");
    g.addEdge("12", "34");
    g.addEdge("12", "35");
    
    BOOST_CHECK_MESSAGE(g.containsEdge("12", "45"), "Edge 12-45 should exist");
    BOOST_CHECK_MESSAGE(g.containsEdge("45", "12"), "Edge 45-12 should exist (symmetry)");
    BOOST_CHECK_MESSAGE(!g.containsEdge("34", "35"), "Edge 34-35 should NOT exist");
    BOOST_CHECK_MESSAGE(!g.containsEdge("34", "15"), "Edge to non-existent vertex");

    // --- Test: Automatic vertex creation via addEdge ---
    g.addEdge("34", "15");
    g.addEdge("15", "23");
    g.addEdge("45", "23");
    
    BOOST_CHECK_MESSAGE(g.containsEdge("15", "34"), "Edge 15-34 should exist");
    BOOST_CHECK_MESSAGE(g.containsEdge("34", "15"), "Edge 34-15 should exist (symmetry)");
    BOOST_CHECK_MESSAGE(g.containsVertex("15"), "Vertex '15' auto-created");
    BOOST_CHECK_MESSAGE(g.containsVertex("23"), "Vertex '23' auto-created");
    BOOST_CHECK_MESSAGE(!g.containsEdge("98", "99"), "Non-existent edge check");
}

// =============================================================================
// TEST SUITE 2: Graph Statistics (degree, counts)
// =============================================================================
// Tests: degree, maxDegree, countVertices, countEdges
// Validates statistical queries on a 4x3 grid graph

BOOST_AUTO_TEST_CASE(GraphStatistics) {
    Graph<int> g;

    // Build a 4x3 grid graph
    // Layout:
    //   11(d=2) -- 21(d=3) -- 31(d=3) -- 41(d=2)
    //      |          |          |          |
    //   12(d=3) -- 22(d=4) -- 32(d=4) -- 42(d=3)
    //      |          |          |          |
    //   13(d=2) -- 23(d=3) -- 33(d=3) -- 43(d=2)
    
    for (int x = 1; x <= 4; x++) {
        for (int y = 1; y <= 3; y++) {
            if (x <= 3) g.addEdge(10 * x + y, 10 * (x + 1) + y); // Horizontal
            if (y <= 2) g.addEdge(10 * x + y, 10 * x + y + 1);   // Vertical
        }
    }

    // --- Test: Individual vertex degrees ---
    BOOST_CHECK_EQUAL(g.degree(11), 2);  // Corner vertex
    BOOST_CHECK_EQUAL(g.degree(12), 3);  // Edge vertex
    BOOST_CHECK_EQUAL(g.degree(22), 4);  // Interior vertex

    // --- Test: Global statistics ---
    BOOST_CHECK_EQUAL(g.maxDegree(), 4);
    BOOST_CHECK_EQUAL(g.countVertices(), 12);
    BOOST_CHECK_EQUAL(g.countEdges(), 17);  // 9 horizontal + 8 vertical
}

// =============================================================================
// TEST SUITE 3: Graph Modification (remove, clear)
// =============================================================================
// Tests: removeEdge, removeVertex, clear
// Validates graph transformations: K5 -> K3,2 -> K2,2 -> K100 -> K50

BOOST_AUTO_TEST_CASE(GraphModification) {
    Graph<int> g;

    // --- Build K5 (complete graph on 5 vertices) ---
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i != j) g.addEdge(i, j);
        }
    }

    BOOST_CHECK(g.containsVertex(4));
    BOOST_CHECK(g.containsEdge(0, 1));
    BOOST_CHECK(!g.containsVertex(5));
    BOOST_CHECK_EQUAL(g.countVertices(), 5);
    BOOST_CHECK_EQUAL(g.countEdges(), 10);  // C(5,2) = 10
    BOOST_CHECK_EQUAL(g.maxDegree(), 4);

    // --- Transform to K3,2 (bipartite) by removing same-parity edges ---
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (i % 2 == j % 2) g.removeEdge(i, j);
        }
    }

    BOOST_CHECK(!g.containsEdge(0, 2));
    BOOST_CHECK(!g.containsEdge(1, 3));
    BOOST_CHECK(g.containsEdge(0, 1));
    BOOST_CHECK_EQUAL(g.countVertices(), 5);
    BOOST_CHECK_EQUAL(g.countEdges(), 6);  // 3 * 2 = 6
    BOOST_CHECK_EQUAL(g.maxDegree(), 3);

    // --- Remove vertex to get K2,2 ---
    g.removeVertex(4);
    
    BOOST_CHECK(!g.containsEdge(1, 4));
    BOOST_CHECK_EQUAL(g.countVertices(), 4);
    BOOST_CHECK_EQUAL(g.countEdges(), 4);
    BOOST_CHECK_EQUAL(g.maxDegree(), 2);

    // --- Clear and build K100 ---
    g.clear();
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            if (i != j) g.addEdge(i, j);
        }
    }

    // --- Remove even vertices to get K50 ---
    for (int i = 0; i < 100; i += 2) {
        g.removeVertex(i);
    }

    BOOST_CHECK_EQUAL(g.countEdges(), 50 * 49 / 2);  // C(50,2) = 1225
    BOOST_CHECK_EQUAL(g.maxDegree(), 49);

    // --- Test negative vertex values ---
    g.clear();
    g.addEdge(-1, -5);
    
    BOOST_CHECK_EQUAL(g.maxDegree(), 1);
    BOOST_CHECK_EQUAL(g.countVertices(), 2);
    BOOST_CHECK_EQUAL(g.countEdges(), 1);
}

// =============================================================================
// TEST SUITE 4: Collection Methods (vertices, edges, neighbors)
// =============================================================================
// Tests: vertices, edges, neighbors, closedNeighbors
// Validates graph collection retrieval methods

BOOST_AUTO_TEST_CASE(CollectionMethods) {
    Graph<int> g;
    std::unordered_set<std::pair<int, int>> expectedEdges;

    // Build 4x3 grid and track expected edges
    for (int x = 1; x <= 4; x++) {
        for (int y = 1; y <= 3; y++) {
            if (x <= 3) {
                g.addEdge(10 * x + y, 10 * (x + 1) + y);
                expectedEdges.insert({10 * x + y, 10 * (x + 1) + y});
            }
            if (y <= 2) {
                g.addEdge(10 * x + y, 10 * x + y + 1);
                expectedEdges.insert({10 * x + y, 10 * x + y + 1});
            }
        }
    }

    // --- Test: vertices() returns all vertices ---
    std::unordered_set<int> expectedVertices = {11, 12, 13, 21, 22, 23, 31, 32, 33, 41, 42, 43};
    BOOST_CHECK(g.vertices() == expectedVertices);

    // --- Test: edges() returns all edges ---
    BOOST_CHECK(g.edges() == expectedEdges);

    // --- Test: neighbors() for corner and interior vertices ---
    BOOST_CHECK(g.neighbors(11) == std::unordered_set<int>({12, 21}));
    BOOST_CHECK(g.neighbors(22) == std::unordered_set<int>({12, 21, 23, 32}));

    // --- Test: closedNeighbors() includes vertex itself ---
    BOOST_CHECK(g.closedNeighbors(11) == std::unordered_set<int>({11, 12, 21}));
    BOOST_CHECK(g.closedNeighbors(22) == std::unordered_set<int>({22, 12, 21, 23, 32}));
}

// =============================================================================
// TEST SUITE 5: BFS and Distance
// =============================================================================
// Tests: bfs (full and limited), distance
// Validates graph traversal and shortest path algorithms

BOOST_AUTO_TEST_CASE(BFSAndDistance) {
    Graph<int> g;

    // Build 4x3 grid
    for (int x = 1; x <= 4; x++) {
        for (int y = 1; y <= 3; y++) {
            if (x <= 3) g.addEdge(10 * x + y, 10 * (x + 1) + y);
            if (y <= 2) g.addEdge(10 * x + y, 10 * x + y + 1);
        }
    }

    // --- Test: Full BFS traversal ---
    std::vector<int> bfsList = g.bfs(11);
    
    std::cout << "BFS traversal: ";
    for (int v : bfsList) std::cout << v << " ";
    std::cout << std::endl;

    BOOST_CHECK_EQUAL(bfsList.size(), 12);
    BOOST_CHECK_EQUAL(bfsList.at(0), 11);
    BOOST_CHECK(bfsList.at(1) == 12 || bfsList.at(1) == 21);
    BOOST_CHECK(bfsList.at(2) == 12 || bfsList.at(2) == 21);
    BOOST_CHECK_EQUAL(bfsList.back(), 43);

    // --- Test: BFS with vertex limit ---
    std::vector<int> bfsShort = g.bfs(43, 3);
    
    std::cout << "BFS limited (3): ";
    for (int v : bfsShort) std::cout << v << " ";
    std::cout << std::endl;

    BOOST_CHECK_EQUAL(bfsShort.size(), 3);
    BOOST_CHECK_EQUAL(bfsShort[0], 43);
    BOOST_CHECK(bfsShort[1] == 33 || bfsShort[1] == 42);
    BOOST_CHECK(bfsShort[2] == 33 || bfsShort[2] == 42);

    // --- Test: Distance calculations ---
    BOOST_CHECK_EQUAL(*g.distance(11, 11), 0);  // Self distance
    BOOST_CHECK_EQUAL(*g.distance(11, 32), 3);  // Cross-grid distance
    BOOST_CHECK(!g.distance(999, 11).has_value());  // Non-existent vertex

    // --- Test: Distance in disconnected graph ---
    g.addEdge(998, 999);
    BOOST_CHECK(!g.distance(999, 11).has_value());  // Disconnected

    g.addEdge(998, 11);  // Connect components
    BOOST_CHECK_EQUAL(*g.distance(999, 11), 2);  // Now reachable
}

// =============================================================================
// TEST SUITE 6: Iterator Compliance
// =============================================================================
// Tests: begin, end, range-based for, explicit iterator
// Validates STL-compatible iterator implementation

BOOST_AUTO_TEST_CASE(IteratorCompliance) {
    Graph<int> g;

    // Build 4x3 grid
    for (int x = 1; x <= 4; x++) {
        for (int y = 1; y <= 3; y++) {
            if (x <= 3) g.addEdge(10 * x + y, 10 * (x + 1) + y);
            if (y <= 2) g.addEdge(10 * x + y, 10 * x + y + 1);
        }
    }

    std::unordered_set<int> verticesFromMethod = g.vertices();

    // --- Test: Range-based for loop ---
    std::unordered_set<int> verticesFromRangeFor;
    for (auto v : g) {
        verticesFromRangeFor.insert(v);
    }
    BOOST_CHECK(verticesFromMethod == verticesFromRangeFor);

    // --- Test: Explicit iterator usage ---
    std::unordered_set<int> verticesFromIterator;
    for (Graph<int>::iterator it = g.begin(); it != g.end(); ++it) {
        verticesFromIterator.insert(*it);
    }
    BOOST_CHECK(verticesFromMethod == verticesFromIterator);
}
