#pragma once

#include <unordered_map>
#include <vector>
#include <limits>

namespace Spa {
    template< typename Node, typename Weight >
    struct SpanningTree {
        struct Label {
            Node pred;
            Weight label;
            Label() : label(INVALID) {
            }

            static const auto INVALID = std::numeric_limits< Weight >::max();
            Label(const Node& p, Weight l) : pred(p), label(l) {
            }
        };

        SpanningTree(const Node& dest, const std::unordered_map< Node, Label >&& labels)
         : m_labels(std::move(labels)), m_dest(dest) {
        }

        std::vector< Node > calculate(const Node& start) const {
            Node cur = start;
            std::vector< Node > route;
            while(cur != m_dest && cur != Node()) {
                route.push_back(cur);
                cur = m_labels.at(cur).pred;
            }

            if(cur == m_dest) {
                route.push_back(cur);
            }

            return route;
        }

      private:
        std::unordered_map< Node, Label > m_labels;
        Node m_dest;
    };
} // namespace Spa
