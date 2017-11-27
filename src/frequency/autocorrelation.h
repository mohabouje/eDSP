//
// Created by Mohammed Boujemaoui on 22/10/2017.
//

#ifndef EDSP_CROSSCORRELATION_H
#define EDSP_CROSSCORRELATION_H

#include "config.h"
#include "transforms/fft.hpp"
#include "transforms/ifft.hpp"
EDSP_BEGING_NAMESPACE
    namespace Frequency {
        template<typename T>
        class AutoCorrelation : AlgorithmTemplate {
        public:
            explicit AutoCorrelation(size_t size);
            ~AutoCorrelation() override;
            const std::vector<T>& compute(const std::vector<T>&);
        private:
            using complex_array = std::vector<std::complex<T>>;
            transforms::FFT  fft;
            transforms::IFFT ifft;
            std::vector<T> data;
        };
    }
EDSP_END_NAMESPACE


#endif //EDSP_CROSSCORRELATION_H
