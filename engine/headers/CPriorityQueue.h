//
// Created by Ahmad Rahimi on 12/14/17.
//

#ifndef TOETS_CPRIORITYQUEUE_H
#define TOETS_CPRIORITYQUEUE_H


#include <queue>

template<
        class T,
        class Container = std::vector<T>,
        class Compare = std::less<typename Container::value_type>
> class CPriorityQueue : public std::priority_queue<T, Container, Compare>
{
public:
    typedef typename
    std::priority_queue<
            T,
            Container,
            Compare>::container_type::const_iterator const_iterator;

    const_iterator find(const T&val) const
    {
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first!=last) {
            if (*first==val) return first;
            ++first;
        }
        return last;
    }

    bool exists(const T&val) const
    {
        auto first = this->c.cbegin();
        auto last = this->c.cend();
        while (first!=last) {
            if (*first==val) return true;
            ++first;
        }
        return false;
    }
};


#endif //TOETS_CPRIORITYQUEUE_H
