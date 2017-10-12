//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_SQUAREGENERATOR_H
#define EDSP_SQUAREGENERATOR_H

#include "config.h"
#include "generator.h"

EDSP_BEGING_NAMESPACE
   namespace generators {
        template<typename T>
        class SquareGenerator : Generator<T> {
        public:
            explicit SquareGenerator(size_t size, T duttycycle, T sampleRate, T frequency, T amplitude);
            SquareGenerator() = default;
            ~SquareGenerator() override = default;

            const std::vector<T>& generate();
            inline T getDuttyCycle() const { return duttyCycle; }
            void setDuttyCycle(const T& dc) { SquareGenerator::duttyCycle = dc;}

            T getPhase() const final = delete;
            void setPhase(T _phase) final = delete;
        private:
            T duttyCycle;
        };
   }
EDSP_END_NAMESPCE

#endif //EDSP_SQUAREGENERATOR_H
