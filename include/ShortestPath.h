#pragma once

#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <unordered_map>
#include "SpanningTree.h"

namespace Spa {
    template< typename Graph, template< typename, typename > class Queue >
    struct ShortestPath {
        using Node = typename Graph::Node;
        using Weight = typename Graph::Weight;
        using Label = typename SpanningTree< Node, Weight >::Label;
        using Item = typename Queue< Node, Weight >::Item;

        ShortestPath(Graph& graph) : m_graph(graph) {
        }

        SpanningTree< Node, Weight > calculate(const Node& dest) {
            m_queue.push(Item(dest, 0));
            m_labels[dest].label = 0;
            while(!m_queue.empty() && !m_graph.goal(m_queue.top().node)) {
                Item currentNode = m_queue.top();
                m_queue.pop();
                using namespace std::placeholders;
                std::for_each(m_graph.begin(currentNode.node),
                              m_graph.end(currentNode.node),
                              std::bind(&ShortestPath::enque, this, currentNode.node, _1));
            }

            m_queue.clear();
            return SpanningTree< Node, Weight >(dest, std::move(m_labels));
        }

      private:
        void enque(const Node& currentNode, const Node& child) {
            auto label = m_labels[currentNode].label + m_graph.weight(currentNode, child);

            Label newLabel(child, label);
            auto& predLabel = m_labels[child];
            if(predLabel.label > newLabel.label) {
                m_queue.push(Item(child, label));
                predLabel = newLabel;
                predLabel.pred = currentNode;
            }
        }

        std::unordered_map< Node, Label > m_labels;
        Queue< Node, Weight > m_queue;
        Graph& m_graph;
    };
} // namespace Spa
