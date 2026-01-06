<div align="center">

<!-- Logo -->
<img src="https://iili.io/fOMHAWQ.png" alt="GraphLib Logo" width="900"/>

<br/>

[![C++](https://img.shields.io/badge/C++-20-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![Header Only](https://img.shields.io/badge/Header--Only-✓-success?style=for-the-badge)](https://en.wikipedia.org/wiki/Header-only)
[![Platform](https://img.shields.io/badge/Platform-Windows%20|%20Linux%20|%20macOS-lightgrey?style=for-the-badge)](https://github.com/djebrilelfeddi/GraphLib)
[![Docs](https://img.shields.io/badge/Docs-Doxygen-blue?style=for-the-badge&logo=readthedocs&logoColor=white)](https://www.doxygen.nl/)

---

</div>

<br/>

**GraphLib** is a high-performance, header-only C++20 library for managing and manipulating undirected graphs. Designed for efficiency and ease of use, it leverages modern C++ features and standard STL containers, and works with any efficient key type (integers, strings, custom structures).

## Available Methods

> **Legend**: `n` = vertices, `m` = edges, `d` = degree of vertex, `V` = visited vertices, `E` = visited edges

| Function | Description | Complexity |
|----------|-------------|------------|
| `addVertex(v)` | **Adds a vertex** to the graph. No effect if it already exists. | O(1) |
| `addEdge(u, v)` | **Adds an undirected edge** between two vertices. Creates vertices if needed. Self-loops are ignored. | O(1) |
| `containsVertex(v)` | **Checks if a vertex exists** in the graph. | O(1) |
| `containsEdge(u, v)` | **Checks if an edge exists between** two vertices. | O(1) |
| `degree(v)` | **Returns the number of neighbors** of a vertex. | O(1) |
| `maxDegree()` | **Returns the maximum degree** in the graph. | O(n) |
| `countVertices()` | **Returns the total number** of vertices. | O(1) |
| `countEdges()` | **Returns the total number** of edges. | O(n) |
| `removeEdge(u, v)` | **Removes an edge between** two vertices. | O(1) |
| `removeVertex(v)` | **Removes a vertex and all** its incident edges. | O(d) |
| `clear()` | **Removes all vertices and edges** from the graph. | O(n + m) |
| `vertices()` | **Returns an `unordered_set` of all** vertices. | O(n) |
| `edges()` | **Returns an `unordered_set` of all edges** as pairs. | O(m) |
| `neighbors(v)` | **Returns the set of neighbors** of a vertex. | O(1) |
| `closedNeighbors(v)` | **Returns neighbors of a vertex** including itself. | O(d) |
| `bfs(v, maxv)` | **Performs BFS from a vertex.** Optional limit on visited vertices. | O(V + E) |
| `distance(u, v)` | **Returns shortest path distance**, or `std::nullopt` if unreachable. | O(V + E) |
| `begin()` / `end()` | **Iterators** for range-based loops over vertices. | O(1) |

## Prerequisites

- A C++20 compatible compiler (GCC 10+, Clang 10+, MSVC 19.28+).
- **Make** (for build automation).
- **Boost Libraries** (only required for running unit tests).

## Installation

Since GraphLib is a header-only library, no compilation is required for the library itself.

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/djebrilelfeddi/GraphLib.git
    cd GraphLib
    ```

2.  **Include in your project:**
    Simply copy `graphlib.hpp` to your project's include directory.

    ```cpp
    #include "graphlib.hpp"
    ```

## Usage Example

```cpp
#include <iostream>
#include <string>
#include "graphlib.hpp"

int main() {
    // Create a graph of Strings
    Graph<std::string> g;

    // Add edges (vertices are created automatically)
    g.addEdge("Paris", "London");
    g.addEdge("London", "New York");
    g.addEdge("Paris", "Tokyo");

    // Print degrees
    std::cout << "Degree of Paris: " << g.degree("Paris") << std::endl;

    // BFS Traversal
    auto path = g.bfs("Paris");
    std::cout << "BFS from Paris: ";
    for (const auto& city : path) {
        std::cout << city << " ";
    }
    std::cout << std::endl;

    // Calculate Distance
    if (auto dist = g.distance("Paris", "New York")) {
        std::cout << "Distance Paris -> New York: " << *dist << std::endl;
    }

    return 0;
}
```

## Running Tests

The project comes with a comprehensive test suite (Unit Tests & Boost Tests).

To build and run all tests:

```bash
make test
```

Or individual tests:

```bash
make test1  # Builds and runs logic for test 1
```

## Documentation

Detailed documentation can be generated via Doxygen:

```bash
doxygen Doxyfile
```

## Author

**EL FEDDI Djebril**

![License](https://img.shields.io/badge/license-MIT-green.svg)
