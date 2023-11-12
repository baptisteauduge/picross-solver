//
// Created by Baptiste Audugé on 03/11/2023.
//

#ifndef TOMOGRAPHIE_UTILS_H
#define TOMOGRAPHIE_UTILS_H
#include <vector>

namespace tomographie {
    typedef std::vector<int> Sequence;
    typedef std::vector<Sequence> ListSequence;
    enum class TriState {
        True = 1,
        False = 0,
        Unknown = -1
    };
}

#endif //TOMOGRAPHIE_UTILS_H
