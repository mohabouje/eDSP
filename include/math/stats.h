//
// Created by Mohammed Boujemaoui on 09/10/2017.
//

#ifndef EDSP_STATS_H
#define EDSP_STATS_H

#include "config.h"
#include "math.h"
#include "utility/vector.h"


#include <unordered_map>
#include <assert.h>

EDSP_BEGING_NAMESPACE
namespace math {
    namespace stats {

        template <typename Container>
        EDSP_EXPORT constexpr typename Container::value_type mode(const Container& container) {
            typedef std::unordered_map<typename Container::value_type,unsigned int> Map;
            Map counts;
            for (size_t i = 0, size = container.size(); i < size; ++i) {
                typename Map::iterator it(counts.find(container[i]));
                (it != counts.end()) ? it->second++ : counts[container[i]] = 1;
            }

            const typename Map::const_iterator pr = std::max_element(
                    counts.begin(),
                    counts.end(),
                    [] (const typename Map::value_type& p1,
                        const typename Map::value_type& p2) {
                        return  p1.second < p2.second;
                    });
            return pr->first;
        }

        template <class ForwardIterator>
        constexpr auto mean(ForwardIterator __first, ForwardIterator __last) {
            return utility::sum(__first, __last)
                   / static_cast< typename std::iterator_traits<ForwardIterator>::value_type> (std::distance(__first, __last));
        }

        template <class ForwardIterator>
        constexpr auto variance(ForwardIterator __first, ForwardIterator __last) {
            return  (utility::sum_squares(__first, __last) - square(utility::sum(__first, __last)))
                    / static_cast< typename std::iterator_traits<ForwardIterator>::value_type> (std::distance(__first, __last));
        }

        template <class ForwardIterator>
        constexpr auto standar_desviation(ForwardIterator __first, ForwardIterator __last) {
            return std::sqrt(variance(__first, __last));
        }

        template <class ForwardIterator>
        constexpr auto mean_error(ForwardIterator __first, ForwardIterator __last) {
            return std::sqrt(variance(__first, __last)) /
                    static_cast<typename std::iterator_traits<ForwardIterator>::value_type> (std::distance(__first, __last));
        }

        template <class ForwardIterator>
        constexpr auto root_mean_square(ForwardIterator __first, ForwardIterator __last) {
            return std::sqrt(mean(__first, __last));
        }

        template <class ForwardIterator>
        constexpr auto median(ForwardIterator __first, ForwardIterator __last) {
            const auto size = std::distance(__first, __last);
            const auto middle = is_odd(size) ? (size/2 - 1) : size/2;
            std::nth_element(__first, __first + middle, __last);
            return *__first + middle;
        }

        template <class ForwardIterator>
        constexpr auto entropy(ForwardIterator __first, ForwardIterator __last) {
            return std::accumulate(__first, __last,
                                   typename std::iterator_traits<ForwardIterator>::value_type(),
                                   [](auto& last, auto& next) {
                                       auto sample = !next ? 1 : next;
                                       last -= std::log2(sample) * sample;
                                       return last;
                                   });
        }

        template <class ForwardIterator>
        constexpr auto geometric_mean(ForwardIterator __first, ForwardIterator __last) {
            return std::any_of(__first, __last, 0)
                     ? typename std::iterator_traits<ForwardIterator>::value_type()
                     : std::accumulate(__first, __last,
                                       typename std::iterator_traits<ForwardIterator>::value_type(),
                                       [](auto& last, auto& next) {
                                            last += std::log(next);
                                            return last;
                                       })
                       / static_cast< typename std::iterator_traits<ForwardIterator>::value_type> (std::distance(__first, __last));
        }

    }
}
EDSP_END_NAMESPACE
#endif //EDSP_STATS_H
