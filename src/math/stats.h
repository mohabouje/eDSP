//
// Created by Mohammed Boujemaoui on 09/10/2017.
//

#ifndef EDSP_STATS_H
#define EDSP_STATS_H

#include "config.h"
#include "math_util.h"
#include "container.h"

#include <unordered_map>
EDSP_BEGING_NAMESPACE
namespace Math {
    namespace Stat {

        template<EDSP_TEMPLATE_CONTAINER(T), EDSP_ENABLE_IF_ARITHMETIC(T)>
        constexpr T mode(const Container& container) {
            typedef std::unordered_map<T,unsigned int> Map;
            Map counts;
            for (int i = 0, size = container.size(); i < size; ++i) {
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

        template<EDSP_TEMPLATE_CONTAINER(T), EDSP_ENABLE_IF_ARITHMETIC(T)>
        constexpr T mean(const Container& container) {
            return  Container::sum(container) / static_cast<T> (container.size());
        }

        template<EDSP_TEMPLATE_CONTAINER(T), EDSP_ENABLE_IF_ARITHMETIC(T)>
        constexpr T variance(const Container& container) {
            return  (Container::sum_squares(container) - Util::square<T>(Container::sum(container))
                                                          / static_cast<T>(container.size()));
        }

        template<EDSP_TEMPLATE_CONTAINER(T), EDSP_ENABLE_IF_ARITHMETIC(T)>
        constexpr T standar_desviation(const Container& container) {
            return static_cast<T>(std::sqrt(variance(container)));
        }

        template<EDSP_TEMPLATE_CONTAINER(T), EDSP_ENABLE_IF_ARITHMETIC(T)>
        constexpr T mean_error(const Container& container) {
            return std::sqrt(variance(container) / static_cast<T>(container.size()));
        }

    }
}
EDSP_END_NAMESPCE
#endif //EDSP_STATS_H
