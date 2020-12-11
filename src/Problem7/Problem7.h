#ifndef _PROBLEM7_H_
#define _PROBLEM7_H_

#include "../../include/PriorQueue.h"

template <class T>
struct GreaterThan
{
    bool operator()(const T &lhs, const T &rhs)
    {
        return lhs > rhs;
    }
};
#endif //!_PROBLEM7_H_