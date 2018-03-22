//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_GENERATOR_H
#define EDSP_GENERATOR_H

#include "base/constants.h"
#include <array>
#include <cmath>

EDSP_BEGIN_NAMESPACE
    namespace generators {

        template <typename T, std::size_t N, typename R>
        constexpr auto sin(R frequency, R phase, R samplerate, R amplitudee) {
            std::array<T, N> data;
            R increment = 0, period = 1. / samplerate;
            R norm_phase = 2 * Constants<T>::pi * phase;
            for (auto i = 0; i < N; i++) {
                data[i] = amplitudee * std::sin(2 * Constants<T>::pi * frequency * increment + norm_phase);
                increment += period;
            }
            return data;
        }

        template <typename T, std::size_t N, typename R>
        constexpr auto square(R frequency, R dutty_cycle, R samplerate, R amplitudee) {
            std::array<T, N> data;
            auto samplesPerPeriod = static_cast<size_t>(samplerate / frequency);
            auto samplesPerDuttyCycle = static_cast<size_t> (dutty_cycle * samplesPerPeriod);
            for (auto i = 0; i < N; i++) {
                data[i] =  amplitudee * ((i % samplesPerPeriod) < samplesPerDuttyCycle ? 1 : -1);
            }
            return data;
        };

        template <typename T, std::size_t N>
        constexpr auto white_noise(){
            std::array<T, N> data;
            std::for_each(std::begin(data), std::end(data), [](auto& val) {
                val = std::rand() / static_cast<T>(RAND_MAX);
            });
            return data;
        };

        template <typename T, std::size_t N>
        constexpr auto brown_noise() {
            static constexpr T BrownInterval{static_cast<T>(8.0)};
            static constexpr T BrownScale{static_cast<T>(0.0625)};
            std::array<T, N> data;
            T ns = static_cast<T>(0);
            std::for_each(std::begin(data), std::end(data), [&](auto& val) {
                val = [&]() {
                    bool compute = true;
                    while (compute) {
                        const T sample =  std::rand() / static_cast<T>(RAND_MAX);
                        ns += sample;
                        if (ns < -BrownInterval || ns > BrownInterval)
                            ns -= sample;
                        else
                            compute = false;
                    }
                    return ns * BrownScale;
                }();
            });
            return data;
        };

        template <typename T, std::size_t N, typename R>
        constexpr auto inpulse_generator(R amplitudee) {
            std::array<T, N> data;
            std::fill(std::begin(data), std::end(data), 0);
            data[0] = 1;
            return data;
        };

}

EDSP_END_NAMESPACE


#endif //EDSP_GENERATOR_H
