//
// Created by Mohammed Boujemaoui on 12/10/2017.
//

#ifndef EDSP_BROWNNOISEGENERATOR_H
#define EDSP_BROWNNOISEGENERATOR_H


#include "generator.h"
EDSP_BEGING_NAMESPACE
    namespace generators {
        template<typename T>
        class BrownNoiseGenerator : public Generator<T> {
        public:
            explicit BrownNoiseGenerator(size_t size);
            BrownNoiseGenerator() = default;
            virtual ~BrownNoiseGenerator() = default;
            const std::vector<T>& generate();
        private:
            static constexpr T BrownInterval{static_cast<T>(8.0)};
            static constexpr T BrownScale{static_cast<T>(0.0625)};
        };




    }
EDSP_END_NAMESPACE

#endif //EDSP_BROWNNOISEGENERATOR_H
