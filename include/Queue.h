#pragma once

#include <queue>

namespace Spa {
    namespace detail {
        template < typename Node, typename Weight > struct QItem {
            const Node node;
            const Weight label;

            QItem (const Node& node, Weight l) : node (node), label (l) {
            }

            const QItem& operator= (const QItem& other) {
                const_cast< Node& > (node) = other.node;
                const_cast< Weight& > (label) = other.label;
                return *this;
            }

            bool operator< (const QItem& other) const {
                return label > other.label;
            }
        };

        template < typename ItemType >
        const ItemType& top (const std::queue< ItemType >& q) {
            return q.front ();
        }

        template < typename ItemType >
        const ItemType& top (const std::priority_queue< ItemType >& q) {
            return q.top ();
        }

        template < typename Node, typename QueueType > class Queue {
            public:
            using Item = typename QueueType::value_type;
            void push (const Item& item) {
                m_queue.push (item);
            }

            bool empty () const {
                return m_queue.empty ();
            }

            const Item& top () const {
                return detail::top (m_queue);
            }

            void pop () {
                m_queue.pop ();
            }

            void clear () {
                m_queue = QueueType{};
            }

            private:
            QueueType m_queue;
        };
    } // namespace detail

    template < typename Node, typename Weight >
    using PrioQueue =
     detail::Queue< Node, std::priority_queue< detail::QItem< Node, Weight > > >;

    template < typename Node, typename Weight >
    using Queue = detail::Queue< Node, std::queue< detail::QItem< Node, Weight > > >;
} // namespace Spa
