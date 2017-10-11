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

            const std::vector<T>& compute();
            inline T duttyCycle() const { return dc; }
            void setDuttyCycle(const T& dc) { SquareGenerator::dc = dc;}
        private:
            T dc;
        };
   }
EDSP_END_NAMESPCE

#endif //EDSP_SQUAREGENERATOR_H
