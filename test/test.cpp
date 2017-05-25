#include <ShortestPath.h>
#include <Queue.h>
#include <vector>
#include <unordered_map>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

typedef unsigned int Node;

class Graph {
    public:
    using Node = ::Node;
    using Weight = unsigned int;
    using WeightFunction = std::function< int(const Node&, const Node&) >;
    Graph () : Graph ([](const Node&, const Node&) { return 100; }) {
    }

    template < typename WeightFunc > Graph (WeightFunc weightFunc) {
        m_calcWeight = weightFunc;
    }

    int weight (const Node& from, const Node& to) {
        return m_calcWeight (from, to);
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
    GraphMap m_graph;
    WeightFunction m_calcWeight;
};


SCENARIO ("Testing dijkstra algorithm", "[spa_dijkstra]") {
    GIVEN ("A graph a dijkstras algorithm and a start position equal with 1") {
        using GraphMap = Graph::GraphMap;
        GraphMap graphMap = {{1, {2, 3}},
                             {2, {5, 6, 7, 3}},
                             {3, {8, 9, 10, 11, 4, 2}},
                             {4, {13, 14, 15, 16}}};

        Graph graph;
        graph.m_graph = graphMap;
        Spa::ShortestPath< Graph, Spa::PrioQueue > algo (graph);
        const auto spanningTree = algo.calculate (1);
        WHEN ("The destination is 1 and the start position is 16") {
            THEN ("The route should be: 16 -> 4 -> 3 -> 1") {
                const std::vector< unsigned int > expected = {16, 4, 3, 1};
                REQUIRE (spanningTree.calculate (16) == expected);
            }
        }
        WHEN ("The destination is 1 and the start position is 10") {
            THEN ("The route should be 10 -> 3 -> 1") {
                const std::vector< unsigned int > expected = {10, 3, 1};
                REQUIRE (spanningTree.calculate (10) == expected);
            }
        }
    }
}

SCENARIO ("Testing belman-fords algorithm", "[spa_bellmanford]") {
    GIVEN (
     "A graph, belman-fords algorithm and a start position equal with 1") {
        using GraphMap = Graph::GraphMap;
        GraphMap graphMap = {{1, {2, 3}},
                             {2, {5, 6, 7, 3}},
                             {3, {8, 9, 10, 11, 4, 2}},
                             {4, {13, 14, 15, 16}}};

        Graph graph;
        graph.m_graph = graphMap;
        Spa::ShortestPath< Graph, Spa::Queue > algo (graph);
        const auto spanningTree = algo.calculate (1);
        WHEN ("The destination is 1 and the start position is 16") {
            THEN ("The route should be: 16 -> 4 -> 3 -> 1") {
                const std::vector< unsigned int > expected = {16, 4, 3, 1};
                REQUIRE (spanningTree.calculate (16) == expected);
            }
        }
        WHEN ("The destination is 1 and the start position is 10") {
            THEN ("The route should be 10 -> 3 -> 1") {
                const std::vector< unsigned int > expected = {10, 3, 1};
                REQUIRE (spanningTree.calculate (10) == expected);
            }
        }
    }

    GIVEN ("A graph with negative weights, belman-fords algorithm and a start "
           "position equal with 1") {
        using GraphMap = Graph::GraphMap;
        GraphMap graphMap = {{1, {2, 3}},
                             {2, {5, 6, 7, 3, 4}},
                             {3, {8, 9, 10, 11, 4, 2}},
                             {4, {13, 14, 15, 16}}};

        auto calcWeight = [](const Node& a, const Node& b) {
            return a == 3 && b == 2 ? -300 : 100;
        };
        Graph graph (calcWeight);
        graph.m_graph = graphMap;
        Spa::ShortestPath< Graph, Spa::Queue > algo (graph);
        const auto spanningTree = algo.calculate (1);
        WHEN ("The destination is 1 and the start position is 16") {
            THEN ("The route should be: 16 -> 4 -> 3 -> 1") {
                const std::vector< unsigned int > expected = {16, 4, 3, 1};
                REQUIRE (spanningTree.calculate (16) == expected);
            }
        }
        WHEN ("The destination is 1 and the start position is 10") {
            THEN ("The route should be 10 -> 3 -> 1") {
                const std::vector< unsigned int > expected = {10, 3, 1};
                REQUIRE (spanningTree.calculate (10) == expected);
            }
        }
    }
}
