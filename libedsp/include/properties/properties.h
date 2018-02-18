#ifndef EDSP_PROPERTIES_H
#define EDSP_PROPERTIES_H


#include "config.h"
#include "utility/vector.h"
#include <utility>
#include <valarray>

EDSP_BEGIN_NAMESPACE
namespace properties {

    template <class InputIterator>
    constexpr auto energy(InputIterator first, InputIterator last) {
        return utility::sum_squares(first, last);
    };

    template <class InputIterator, typename StevenLowLevel>
    constexpr auto loudness(InputIterator first, InputIterator last, StevenLowLevel factor = 0.67f) {
        return std::pow(utility::sum_squares(first, last), factor);    
    };

    template <class InputIterator>
    constexpr auto power(InputIterator first, InputIterator last) {
        using value_type = typename std::iterator_traits<InputIterator>::value_type;
        return utility::sum_squares(first, last) / static_cast<value_type >(std::distance(first, last));
    };

    template <class InputIterator, typename  Threshold_dB>
    constexpr bool is_silence_db(InputIterator first, InputIterator last, Threshold_dB limit) {
        return 20 * std::log10(energy(first, last)) <= limit;
    };

    template <class InputIterator, typename Threshold>
    constexpr bool is_silence(InputIterator first, InputIterator last, Threshold limit) {
        return energy(first, last) <= limit;
    };

    template <class InputIterator>
    constexpr auto zero_crossing_rate(InputIterator first, InputIterator last) {
        using value_type = typename std::iterator_traits<InputIterator>::value_type;
        value_type tmp = 0;
        for (auto before = first, after = ++first; after != last; ++before, ++after) {
            tmp += (math::sign(*after) != math::sign(*before)) ? 1 : 0;
        }
        return tmp / static_cast<value_type >(std::distance(first, last));
    };


    template <class InputIterator, typename SampleRate>
    constexpr float buffer_duration_secs(const InputIterator first, const InputIterator last, const SampleRate sr) {
        return static_cast<float>(std::distance(first, last)) / static_cast<float>(sr);
    };
}
EDSP_END_NAMESPACE
#endif
