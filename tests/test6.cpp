/**
 * @file test6.cpp
 * @brief Test suite for graph statistics (degree, maxDegree, counts)
 * 
 * This test validates:
 * - degree() returns correct neighbor count for vertices
 * - maxDegree() returns the highest degree in the graph
 * - countVertices() returns total vertex count
 * - countEdges() returns total edge count
 * - Grid graph property verification
 */

#include <iostream>
#include <cassert>
#include "graph.hpp"

int main() {
    Graph<int> g;

    // =========================================================================
    // SETUP: Build a 4x3 grid graph
    // =========================================================================
    // Grid layout with expected degrees:
    //   11(2) -- 21(3) -- 31(3) -- 41(2)    <- corners have degree 2
    //    |        |        |        |           edges have degree 3
    //   12(3) -- 22(4) -- 32(4) -- 42(3)    <- interior has degree 4
    //    |        |        |        |
    //   13(2) -- 23(3) -- 33(3) -- 43(2)
    //
    // Total: 12 vertices, 17 edges

    for (int x = 1; x <= 4; x++) {
        for (int y = 1; y <= 3; y++) {
            if (x <= 3)
                g.addEdge(10 * x + y, 10 * (x + 1) + y); // Horizontal edge
            if (y <= 2)
                g.addEdge(10 * x + y, 10 * x + y + 1);   // Vertical edge
        }
    }

    // =========================================================================
    // TEST 1: Verify corner vertex degree (should be 2)
    // =========================================================================
    assert(g.degree(11) == 2 && "Corner vertex 11 should have degree 2");

    // =========================================================================
    // TEST 2: Verify edge vertex degree (should be 3)
    // =========================================================================
    assert(g.degree(12) == 3 && "Edge vertex 12 should have degree 3");

    // =========================================================================
    // TEST 3: Verify interior vertex degree (should be 4)
    // =========================================================================
    assert(g.degree(22) == 4 && "Interior vertex 22 should have degree 4");

    // =========================================================================
    // TEST 4: Verify maximum degree in graph
    // =========================================================================
    assert(g.maxDegree() == 4 && "Max degree in 4x3 grid should be 4");

    // =========================================================================
    // TEST 5: Verify vertex count (4 columns x 3 rows = 12)
    // =========================================================================
    assert(g.countVertices() == 12 && "4x3 grid should have 12 vertices");

    // =========================================================================
    // TEST 6: Verify edge count
    // =========================================================================
    // Horizontal edges: 3 per row x 3 rows = 9
    // Vertical edges: 4 per column x 2 gaps = 8
    // Total: 9 + 8 = 17 edges
    assert(g.countEdges() == 17 && "4x3 grid should have 17 edges");

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
