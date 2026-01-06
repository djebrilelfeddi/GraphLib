/**
 * @file test3.cpp
 * @brief Test suite for BFS traversal and distance calculation
 * 
 * This test validates:
 * - Breadth-First Search (bfs) traversal order
 * - BFS with maximum vertex limit (maxv parameter)
 * - Shortest path distance calculation
 * - Distance to self (should be 0)
 * - Distance to unreachable vertices (should be nullopt)
 * - Distance in disconnected graphs
 */

#include <iostream>
#include <cassert>
#include "graphlib.hpp"

int main() {
    Graph<int> g;

    // =========================================================================
    // SETUP: Build a 4x3 grid graph
    // =========================================================================
    // Grid layout:
    //   11 -- 21 -- 31 -- 41
    //   |     |     |     |
    //   12 -- 22 -- 32 -- 42
    //   |     |     |     |
    //   13 -- 23 -- 33 -- 43
    
    for (int x = 1; x <= 4; x++) {
        for (int y = 1; y <= 3; y++) {
            if (x <= 3)
                g.addEdge(10 * x + y, 10 * (x + 1) + y); // Horizontal edge
            if (y <= 2)
                g.addEdge(10 * x + y, 10 * x + y + 1);   // Vertical edge
        }
    }

    // =========================================================================
    // TEST 1: Full BFS traversal from corner vertex
    // =========================================================================
    std::vector<int> bfsList = g.bfs(11);

    std::cout << "BFS traversal from 11: ";
    for (int v : bfsList) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    // Verify BFS properties
    assert(bfsList.size() == 12 && "BFS should visit all 12 vertices");
    assert(bfsList.at(0) == 11 && "BFS should start with source vertex");
    
    // Second vertex should be a neighbor of 11 (either 12 or 21)
    assert((bfsList.at(1) == 12 || bfsList.at(1) == 21) && 
           "Second vertex should be a neighbor of 11");
    assert((bfsList.at(2) == 12 || bfsList.at(2) == 21) && 
           "Third vertex should be a neighbor of 11");
    
    // Last vertex should be the farthest corner (43)
    assert(bfsList.back() == 43 && "Last vertex should be opposite corner (43)");

    // =========================================================================
    // TEST 2: BFS with maximum vertex limit
    // =========================================================================
    std::vector<int> bfsShortList = g.bfs(43, 3);

    std::cout << "BFS from 43 (max 3): ";
    for (int v : bfsShortList) {
        std::cout << v << " ";
    }
    std::cout << std::endl;

    assert(bfsShortList.size() == 3 && "BFS should stop after 3 vertices");
    assert(bfsShortList[0] == 43 && "Should start with source vertex");
    
    // Second and third vertices should be neighbors of 43 (33 or 42)
    assert((bfsShortList[1] == 33 || bfsShortList[1] == 42) && 
           "Second vertex should be neighbor of 43");
    assert((bfsShortList[2] == 33 || bfsShortList[2] == 42) && 
           "Third vertex should be neighbor of 43");

    // =========================================================================
    // TEST 3: Distance calculations
    // =========================================================================
    // Distance to self should be 0
    assert(*g.distance(11, 11) == 0 && "Distance to self should be 0");

    // Distance across grid (11 to 32 = right 2, down 1 = 3 steps)
    assert(*g.distance(11, 32) == 3 && "Distance 11->32 should be 3");

    // Distance to non-existent vertex should be nullopt
    assert(!g.distance(999, 11).has_value() && 
           "Distance from non-existent vertex should be nullopt");

    // =========================================================================
    // TEST 4: Distance in disconnected graph
    // =========================================================================
    // Add a disconnected component
    g.addEdge(998, 999);
    
    // Distance between disconnected components should be nullopt
    assert(!g.distance(999, 11).has_value() && 
           "Distance between disconnected components should be nullopt");

    // Connect the components
    g.addEdge(998, 11);
    
    // Now distance should be calculable (999 -> 998 -> 11 = 2)
    assert(*g.distance(999, 11) == 2 && 
           "Distance 999->11 should be 2 after connecting");

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
