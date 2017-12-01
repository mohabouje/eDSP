//
// Created by Mohammed Boujemaoui on 12/10/2017.
//

#ifndef EDSP_BROWNNOISEGENERATOR_H
#define EDSP_BROWNNOISEGENERATOR_H


#include "generator.hpp"
EDSP_BEGING_NAMESPACE
    namespace generators {
        template<typename T, std::size_t N>
        class BrownNoiseGenerator : public Generator<T, N> {
        public:
            explicit BrownNoiseGenerator() = default;
            ~BrownNoiseGenerator() override = default;
            const std::array<T, N> &generate() {
                T ns = static_cast<T>(0);
                for (size_t i = 0, size = this->data.size(); i < size; ++i) {
                    this->data[i] = [&]() {
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
                }
                return this->data;
            }
        private:
            static constexpr T BrownInterval{static_cast<T>(8.0)};
            static constexpr T BrownScale{static_cast<T>(0.0625)};
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_BROWNNOISEGENERATOR_H
