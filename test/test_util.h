//
// Created by Mohammed Boujemaoui on 15/10/2017.
//

#ifndef EDSP_TEST_UTIL_H
#define EDSP_TEST_UTIL_H

#include <limits>
#include <cmath>
namespace test {
    namespace util {
        template <typename T>
        constexpr bool isEqual(const T& a, const T& b) {
            return static_cast<T>(std::abs(a - b)) <= std::numeric_limits<T>::epsilon();
        }
    }
}


#endif //EDSP_TEST_UTIL_H
