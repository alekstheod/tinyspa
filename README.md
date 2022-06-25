# tinyspa

Small header only shortest path algorithm implementation
by adapting the weight function can be used as a dijkstra
or AStar algorithm

Usage:

Define a graph class

- Graph is a class with the following interface
  - Node type defines the node
  - Weight type defines the weight
  - Weight weight(const Node& from, const Node& to) // calculates the weight for the edge between the nodes from and to
  - Iterator begin(const Node& node) // returns iterator of of predecessors of the given node
  - Iterator end(const Node& node) // returns end iterator of predecessors of the given node
  - bool goal (const Node& cur) // returns true if the goal is reached (destination == cur)

Create a graph

```
#include <ShortestPath.h>
#include <Queue.h>

#include <vector>
#include <unordered_map>

typedef unsigned int Node;

class Graph {
    public:
    using Node = ::Node;
    using Weight = unsigned int;
    Graph () {
    }

    Weight weight (const Node& from, const Node& to) {
        return 100;
    }

    using Container = typename std::vector< Node >;
    using Iterator = typename Container::const_iterator;

    Iterator begin (const Node& node) {
        return m_graph[node].cbegin ();
    }

    Iterator end (const Node& node) {
        return m_graph[node].cend ();
    }

    // In case of dijkstra return true if cur == m_dest
    bool goal (const Node& cur) {
        return false;
    }

    using GraphMap = std::unordered_map< unsigned int, Container >;
    GraphMap m_graph = {{1, {2, 3}},
                        {2, {5, 6, 7, 3}},
                        {3, {8, 9, 10, 11, 4, 2}},
                        {4, {13, 14, 15, 16}}};
};
```

Calculate the route

```
Spa::ShortestPath< Graph, Spa::PrioQueue > algo (graph);
const auto spanningTree = algo.calculate (1);
const auto path = spanningTree.calculate(16);
const auto path2 = spanningTree.calculate(10);
```
