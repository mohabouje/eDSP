//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_SQUAREGENERATOR_H
#define EDSP_SQUAREGENERATOR_H

#include "generator.h"

EDSP_BEGING_NAMESPACE
   namespace generators {
        template<typename T, std::size_t N>
        class SquareGenerator : Generator<T, N> {
        public:
            explicit SquareGenerator(T duttycycle, T sampleRate, T frequency, T amplitude) :
                duttyCycle(duttycycle), Generator<T,N>(sampleRate, frequency, amplitude) {

            }
            ~SquareGenerator() override = default;
            const std::array<T, N> &generate() {
                auto samplesPerPeriod = static_cast<size_t>(this->sampleRate / this->frequency);
                auto samplesPerDuttyCycle = static_cast<size_t> (duttyCycle * samplesPerPeriod);
                for (size_t i = 0, size = this->data.size(); i < size; i++) {
                    this->data[i] = this->amplitude * ((i % samplesPerPeriod) < samplesPerDuttyCycle ? 1 : -1);
                }
                return this->data;
            }

            T getDuttyCycle() const { return duttyCycle; }
            void setDuttyCycle(const T& dc) { SquareGenerator::duttyCycle = dc;}

        private:
            T duttyCycle;
        };
   }
EDSP_END_NAMESPACE

#endif //EDSP_SQUAREGENERATOR_H
