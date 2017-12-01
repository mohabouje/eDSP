//
// Created by Mohammed Boujemaoui on 12/10/2017.
//

#ifndef EDSP_SINGENERATOR_H
#define EDSP_SINGENERATOR_H

#include "generator.hpp"
#include "base/constants.h"

EDSP_BEGING_NAMESPACE
    namespace generators {
        template<typename T, std::size_t N>
        class SinGenerator : public Generator<T, N> {
        public:
            SinGenerator(T sr, T f, T ph, T a) : Generator(sr, f, a), phase(ph) {}
            const std::array<T, N> &generate() {
                T increment = 0, period = 1. / this->sampleRate;
                T normPhase = 2 * Constants<T>::pi * this->phase;
                for (size_t i = 0, size = this->data.size(); i < size; i++) {
                    this->data[i] = this->amplitude * std::sin(2 * Constants<T>::pi * this->frequency * increment + normPhase);
                    increment += period;
                }
                return this->data;
            }
            T getPhase() const { return phase; }
            void setPhase(T phase) { SinGenerator::phase = phase; }
        private:
            T phase{0};
        };
    }
EDSP_END_NAMESPACE
#endif //EDSP_SINGENERATOR_H
