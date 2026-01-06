/**
 * @file test2.cpp
 * @brief Test suite for graph iterators
 * 
 * This test validates:
 * - Building a 4x3 grid graph
 * - vertices() method returns all vertices
 * - Range-based for loop iteration (begin/end)
 * - Explicit iterator usage with Graph<T>::iterator
 * - Iterator consistency with vertices() output
 */

#include <iostream>
#include <cassert>
#include "graph.hpp"

int main() {
    Graph<int> g;

    // =========================================================================
    // SETUP: Build a 4x3 grid graph
    // =========================================================================
    // Grid layout (vertices labeled as XY where X=column, Y=row):
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
    // TEST 1: Compare vertices() with range-based for loop
    // =========================================================================
    std::unordered_set<int> verticesFromMethod = g.vertices();
    std::unordered_set<int> verticesFromRangeFor;

    for (auto v : g) {
        verticesFromRangeFor.insert(v);
    }

    assert(verticesFromMethod == verticesFromRangeFor && 
           "Range-based for should yield same vertices as vertices()");

    // =========================================================================
    // TEST 2: Explicit iterator usage
    // =========================================================================
    std::unordered_set<int> verticesFromExplicitIterator;

    for (Graph<int>::iterator it = g.begin(); it != g.end(); ++it) {
        verticesFromExplicitIterator.insert(*it);
    }

    assert(verticesFromMethod == verticesFromExplicitIterator && 
           "Explicit iterator should yield same vertices as vertices()");

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
