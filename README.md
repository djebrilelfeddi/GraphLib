# GraphLib - C++20 Generic Graph Library

![Language](https://img.shields.io/badge/language-C%2B%2B20-blue.svg)
![License](https://img.shields.io/badge/license-MIT-green.svg)

**GraphLib** is a high-performance, header-only C++20 library for managing and manipulating undirected graphs. Designed for efficiency and ease of use, it leverages modern C++ features and standard STL containers, and works with any efficient key type (integers, strings, custom structures).

## Features

- **Generic Implementation**: Works with any efficient key type (integers, strings, custom objects).
- **High Performance**: 
  - Adjacency list representation using `std::unordered_map` and `std::unordered_set`.
  - **O(1)** amortized complexity for vertex/edge insertion and lookup.
  - "Single Lookup" optimizations for removal operations.
  - Memory pre-allocation (`reserve`) to prevent costly rehashing.
- **STL Compatible**: Includes a fully compliant `iterator` class (LegacyInputIterator) for range-based loops.
- **Robust Algorithms**:
  - Breadth-First Search (BFS).
  - Shortest path calculation (Memory-optimized Level-by-Level BFS).
- **Flexible**: Supports custom hash functions for complex vertex types.

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
    Simply copy `graph.hpp` to your project's include directory.

    ```cpp
    #include "graph.hpp"
    ```

## Usage Example

```cpp
#include <iostream>
#include <string>
#include "graph.hpp"

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

Or individual exercises:

```bash
make exercice3  # Builds and runs logic for exercise 3
```

## Documentation

Detailed documentation can be generated via Doxygen:

```bash
doxygen Doxyfile
```

## Author

**EL FEDDI Djebril**
