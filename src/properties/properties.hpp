#ifndef EDSP_PROPERTIES_H
#define EDSP_PROPERTIES_H



#include "utility/vector_util.hpp"
#include "utility/template_util.hpp"
#include <utility>

EDSP_BEGING_NAMESPACE
    namespace properties {

        EDSP_FTEMPLATE_ARITHMETIC_CONTAINER(Container, typename Container::value_type)
        energy(const Container& data) {
            utility::vector::sum_squares(data);
        };

        EDSP_FTEMPLATE_ARITHMETIC_CONTAINER(Container, typename Container::value_type)
        loudness(const Container& data) {
            return std::pow(utility::vector::sum_squares(data), static_cast<typename Container::value_type>(0.67)); // StevenLawLevel
        };

        EDSP_FTEMPLATE_ARITHMETIC_CONTAINER(Container, typename Container::value_type)
        power(const Container& data) {
            return utility::vector::sum_squares(data) / static_cast<typename Container::value_type>(data.size());
        };

        EDSP_FTEMPLATE_ARITHMETIC_CONTAINER(Container, size_t)
        strong_peak(const Container& data) {
            auto it = std::max_element(data.begin(), data.end());
            return static_cast<size_t>(std::distance(data.begin(), it));
        };


        EDSP_FTEMPLATE_ARITHMETIC_CONTAINER(Container, typename Container::value_type)
        zero_crossing_rate(const Container& data) {
            typename Container::value_type tmp = 0;
            for (size_t i = 0, size = data.size(); i < size; i++) {
                tmp += (math::sign(data[i]) != math::sign(data[i - 1])) ? 1 : 0;
            }
            return tmp / static_cast<typename Container::value_type>(data.size()) ;        };

    }
EDSP_END_NAMESPACE

#endif