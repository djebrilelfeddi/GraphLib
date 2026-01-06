/**
 * @file test4.cpp
 * @brief Test suite for graph collection methods (vertices, edges, neighbors)
 * 
 * This test validates:
 * - vertices() returns all graph vertices
 * - edges() returns all graph edges as pairs
 * - neighbors() returns adjacent vertices
 * - closedNeighbors() returns neighbors including the vertex itself
 * - Edge pair ordering (u < v convention)
 */

#include <iostream>
#include <cassert>
#include "graph.hpp"

int main() {
    Graph<int> g;
    std::unordered_set<std::pair<int, int>> expectedEdges;

    // =========================================================================
    // SETUP: Build a 4x3 grid graph and track expected edges
    // =========================================================================
    // Grid layout:
    //   11 -- 21 -- 31 -- 41
    //   |     |     |     |
    //   12 -- 22 -- 32 -- 42
    //   |     |     |     |
    //   13 -- 23 -- 33 -- 43

    for (int x = 1; x <= 4; x++) {
        for (int y = 1; y <= 3; y++) {
            if (x <= 3) {
                int u = 10 * x + y;
                int v = 10 * (x + 1) + y;
                g.addEdge(u, v); // Horizontal edge
                expectedEdges.insert(std::make_pair(u, v));
            }
            if (y <= 2) {
                int u = 10 * x + y;
                int v = 10 * x + y + 1;
                g.addEdge(u, v); // Vertical edge
                expectedEdges.insert(std::make_pair(u, v));
            }
        }
    }

    // =========================================================================
    // TEST 1: Verify all vertices are present
    // =========================================================================
    std::unordered_set<int> expectedVertices = {11, 12, 13, 21, 22, 23, 31, 32, 33, 41, 42, 43};
    
    assert(g.vertices() == expectedVertices && 
           "vertices() should return all 12 grid vertices");

    // =========================================================================
    // TEST 2: Verify all edges are present
    // =========================================================================
    assert(g.edges() == expectedEdges && 
           "edges() should return all grid edges with u < v ordering");

    // =========================================================================
    // TEST 3: Verify neighbors() for corner vertex (degree 2)
    // =========================================================================
    std::unordered_set<int> neighborsOf11 = {12, 21};
    
    assert(g.neighbors(11) == neighborsOf11 && 
           "Corner vertex 11 should have exactly 2 neighbors: 12 and 21");

    // =========================================================================
    // TEST 4: Verify neighbors() for interior vertex (degree 4)
    // =========================================================================
    std::unordered_set<int> neighborsOf22 = {12, 21, 23, 32};
    
    assert(g.neighbors(22) == neighborsOf22 && 
           "Interior vertex 22 should have 4 neighbors");

    // =========================================================================
    // TEST 5: Verify closedNeighbors() includes the vertex itself
    // =========================================================================
    std::unordered_set<int> closedNeighborsOf11 = {11, 12, 21};
    
    assert(g.closedNeighbors(11) == closedNeighborsOf11 && 
           "closedNeighbors(11) should include 11 itself");

    std::unordered_set<int> closedNeighborsOf22 = {22, 12, 21, 23, 32};
    
    assert(g.closedNeighbors(22) == closedNeighborsOf22 && 
           "closedNeighbors(22) should include 22 and all 4 neighbors");

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
