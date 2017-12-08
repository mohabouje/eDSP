#ifndef EDSP_PROPERTIES_H
#define EDSP_PROPERTIES_H


#include "config.h"
#include "utility/vector.h"
#include <utility>
#include <valarray>

EDSP_BEGING_NAMESPACE
namespace properties {

    template <class InputIterator>
    constexpr auto energy(InputIterator __first, InputIterator __last) {
        return utility::sum_squares(__first, __last);
    };

    template <class InputIterator>
    constexpr auto loudness(InputIterator __first, InputIterator __last) {
        return std::pow(utility::sum_squares(__first, __last), 0.67f); // StevenLawLevel
    };

    template <class InputIterator>
    constexpr auto power(InputIterator __first, InputIterator __last) {
        return utility::sum_squares(__first, __last)
               / static_cast<typename std::iterator_traits<InputIterator>::value_type>(std::distance(__first, __last));
    };

    template <class InputIterator>
    constexpr auto zero_crossing_rate(InputIterator __first, InputIterator __last) {
        typename std::iterator_traits<InputIterator>::value_type tmp = 0;
        for (auto before = __first, after = ++__first, ; after != __last; ++before, ++after) {
            tmp += (math::sign(after) != math::sign(before)) ? 1 : 0;
        }
        return tmp
               / static_cast<typename std::iterator_traits<InputIterator>::value_type>(std::distance(__first, __last));
    };
}
EDSP_END_NAMESPACE
#endif
