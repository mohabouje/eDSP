//
// Created by Mohammed Boujemaoui on 09/10/2017.
//

#ifndef EDSP_STATS_H
#define EDSP_STATS_H

#include "config.h"
#include "math_util.hpp"
#include "container.hpp"
#include "base/template_util.hpp"


#include <unordered_map>
#include <assert.h>

EDSP_BEGING_NAMESPACE
namespace math {
    namespace stats {
        TEMPLATE_CONTAINER(Container, typename Container::value_type)
        mode(const Container& container) {
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

        TEMPLATE_CONTAINER(Container, typename Container::value_type)
        mean(const Container& container) {
            return  sum(container) / static_cast<typename Container::value_type> (container.size());
        }

        TEMPLATE_CONTAINER(Container, typename Container::value_type)
        variance(const Container& container) {
            return  (sum_squares(container) - square(sum(container))) / static_cast<typename Container::value_type>(container.size());
        }

        TEMPLATE_CONTAINER(Container, typename Container::value_type)
        standar_desviation(const Container& container) {
            return static_cast<typename Container::value_type>(std::sqrt(variance(container)));
        }

        TEMPLATE_CONTAINER(Container, typename Container::value_type)
        mean_error(const Container& container) {
            return static_cast<typename Container::value_type>(std::sqrt(variance(container)
                                                                         / static_cast<typename Container::value_type>(container.size())));
        }

        TEMPLATE_CONTAINER(Container, typename Container::value_type)
        root_mean_square(const Container& container) {
            return static_cast<typename Container::value_type>(std::sqrt(mean(container)));
        }

        TEMPLATE_CONTAINER(Container, typename Container::value_type)
        median(const Container& container) {
            Container tmp(container);
            std::sort(tmp.begin(), tmp.end());
            const size_t size = tmp.size();
            return (isOdd(size))  ? (tmp[uint(size/2 - 1)] + tmp[uint(size/2)]) / 2
                                  : tmp[uint(size/2)];
        }

        TEMPLATE_CONTAINER(Container, typename Container::value_type)
        entropy(const Container& container) {
            static_assert(Container::hasNegative(container), "Trying to generate the entrpy of an array with negative values");
            typename Container::value_type tmp = 0;
            for (size_t i=0, size = container.size(); i<size; i++) {
                auto sample = (!container[i]) ? 1 : container[i];
                tmp -= std::log2(sample) * sample;
            }
            return tmp;
        }

        TEMPLATE_CONTAINER(Container, typename Container::value_type)
        geometric_mean(const Container &container) {
            assert(Container::hasNegative(container) &&
                        "Trying to generate the geometric mean of an array with "
                        "negative values");
            return Container::hasZero(container)
                     ? static_cast<typename Container::value_type>(0)
                     : std::accumulate(container.begin(), container.end(),
                                       static_cast<typename Container::value_type>(0),
                                       [](typename Container::value_type last, typename Container::value_type next) {
                                         return last += std::log(next);
                                       }) / static_cast<typename Container::value_type>(container.size());

        }

    }
}
EDSP_END_NAMESPACE
#endif //EDSP_STATS_H
