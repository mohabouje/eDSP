//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_SPECTROGRAM_H
#define EDSP_SPECTROGRAM_H

#include "config.h"
#include "transforms/fft.h"
EDSP_BEGING_NAMESPACE
    namespace Math {
        namespace Frequency {
            template<typename T>
            class Spectrogram : AlgorithmTemplate {
            public:
                explicit Spectrogram(size_t size);
                ~Spectrogram() override;
                const std::vector<T>& compute(const std::vector<T>&);
            private:
                transforms::FFT<T> fft;
                std::vector<T> data;
            };
        }
    }
EDSP_END_NAMESPACE
#endif //EDSP_SPECTROGRAM_H
