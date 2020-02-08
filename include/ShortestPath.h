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
            while(!m_queue.empty() && !m_graph.goal(m_queue.top().node)) {
                Item cur = m_queue.top();
                m_queue.pop();
                m_labels[dest].label = 0;
                using namespace std::placeholders;
                std::for_each(m_graph.begin(cur.node),
                              m_graph.end(cur.node),
                              std::bind(&ShortestPath::enque, this, cur.node, _1));
            }

            m_queue.clear();
            return SpanningTree< Node, Weight >(dest, std::move(m_labels));
        }

      private:
        void enque(const Node& cur, const Node& child) {
            auto label = m_labels[cur].label + m_graph.weight(cur, child);

            Label entry(child, label);
            auto& predLabel = m_labels[child];
            if(predLabel.label > entry.label) {
                m_queue.push(Item(child, label));
                predLabel = entry;
                predLabel.pred = cur;
            }
        }

        std::unordered_map< Node, Label > m_labels;
        Queue< Node, Weight > m_queue;
        Graph& m_graph;
    };
} // namespace Spa
