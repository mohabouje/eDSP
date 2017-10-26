//
// Created by Mohammed Boujemaoui on 22/10/2017.
//

#ifndef EDSP_CROSSCORRELATION_H
#define EDSP_CROSSCORRELATION_H

#include "config.h"
#include "transforms/fft.h"
#include "transforms/ifft.h"
EDSP_BEGING_NAMESPACE
    namespace Frequency {
        template<typename T>
        class AutoCorrelation : AlgorithmTemplate {
        public:
            explicit AutoCorrelation(size_t size);
            ~AutoCorrelation() override;
            const std::vector<T>& compute(const std::vector<T>&);
        private:
            transforms::FFT<T> fft;
            transforms::IFFT<T> ifft;
            std::vector<T> data;
        };
    }
EDSP_END_NAMESPACE


#endif //EDSP_CROSSCORRELATION_H
