//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_WHITENOISE_H
#define EDSP_WHITENOISE_H

#include "generator.hpp"

EDSP_BEGING_NAMESPACE
    namespace generators {
        template <typename T, std::size_t N>
        class WhiteNoiseGenerator : public Generator<T, N> {
        public:
            explicit WhiteNoiseGenerator() = default;
            ~WhiteNoiseGenerator() override = default;
            const std::array<T, N> &generate() {
                for (size_t i = 0, size = this->data.size(); i < size; i++) {
                    this->data[i] = std::rand() / static_cast<T>(RAND_MAX);
                }
            }
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_WHITENOISE_H
