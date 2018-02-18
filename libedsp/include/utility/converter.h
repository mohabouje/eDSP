//
// Created by Mohammed Boujemaoui on 10/12/2017.
//

#ifndef EDSP_CONVERTER_H
#define EDSP_CONVERTER_H

#include <experimental/optional>
#include <cmath>
#include "config.h"

EDSP_BEGIN_NAMESPACE
    namespace converter {
        // TODO: add some constants like log(2) to the database
        // static constexpr double REF_FREQ = 8.17579892;

        template <typename T>
        constexpr std::experimental::optional<T> hertz_to_absolute_cent(const T hertz_value) {
            return (hertz_value > 0) ? 1200 * std::log(hertz_value / 8.17579892) / std::log(2.0)
                   : std::experimental::nullopt;
        }


        template <typename T>
        constexpr auto absolute_cent_to_hertz(const T absolute_cent) {
            return 8.17579892 * std::pow(2, absolute_cent / 1200.0);
        }

        template <typename T>
        constexpr auto hertz_to_midi_cent(const T hertz_value) {
            return (hertz_value != 0) ? 12 * std::log(hertz_value / 440) / std::log(2.0) + 69
                                      : 0;
        }

        template <typename T>
        constexpr std::experimental::optional<T> hertz_to_relative_cent(const T hertz_value) {
            const auto absolute_cent_value = hertz_to_absolute_cent(hertz_value)
                    .value_or(std::numeric_limits<T>::quiet_NaN());
            return std::isnan(absolute_cent_value) ? std::experimental::nullopt
                                                   : (absolute_cent_value < 0) ? std::abs(T(1200) + absolute_cent_value)
                                                                               : (absolute_cent_value % 1200);
        }

        template <typename T>
        constexpr auto midi_cent_to_hertz(const T midi_cent) {
            return 440 * std::pow(2, (midi_cent - 69) / 12d);
        }

        template <typename T>
        constexpr std::experimental::optional<T> hertz_to_midi_key(const T hertz_value) {
            const auto midi_key = std::round(hertz_to_midi_cent(hertz_value));
            return (midi_key < 0 || midi_key > 127) ? std::experimental::nullopt : midi_key;
        }


        template <typename T>
        constexpr std::experimental::optional<T> midi_key_to_hertz(const T midi_key) {
            return (midi_key < 0 || midi_key > 127) ? std::experimental::nullopt : midi_cent_to_hertz(midi_key);
        }

        template <typename T>
        constexpr auto cent_to_ratio(const T cent) {
            return std::pow(10, std::log10(2) * cent / 1200.0);
        }


        template <typename T>
        constexpr auto ratio_to_cent(const T ratio) {
            return 1200 / std::log10(2) * std::log10(ratio);
        }


    }
EDSP_END_NAMESPACE


#endif //EDSP_CONVERTER_H
