//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_CEPSTRUM_H
#define EDSP_CEPSTRUM_H


#include "config.h"
#include "transforms/fft.h"
#include "transforms/ifft.h"
EDSP_BEGING_NAMESPACE
    namespace Frequency {
        template<typename T>
        class Cepstrum : AlgorithmTemplate {
        public:
            explicit Cepstrum(size_t size);
            ~Cepstrum() override;
            const std::vector<T>& compute(const std::vector<T>&);
        private:
            transforms::FFT<T> fft;
            transforms::IFFT<T> ifft;
            std::vector<T> data;
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_CEPSTRUM_H
