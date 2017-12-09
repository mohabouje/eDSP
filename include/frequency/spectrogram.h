//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_SPECTROGRAM_H
#define EDSP_SPECTROGRAM_H

#include "config.h"
#include "fft.h"
#include "math/complex.h"
EDSP_BEGIN_NAMESPACE
    namespace frequency {
        class  Spectrogram {
        public:
            typename <class InputIterator, class OutputIterator>
            void compute(InputIterator __first, InputIterator __last, OutputIterator __out) {
                const auto size = std::distance(__first, __last);
                if (buffer.size() != size) { buffer.resize(size); }
                fft.compute_r2c(__first, __last, std::begin(buffer));
                std::transform(std::begin(buffer), std::end(buffer), __out, [](const auto& value) {
                    const auto tmp = std::abs(value);
                    return  (tmp * tmp);
                });
            }
        private:
            FFT fft{};
            std::vector<std::complex<double>> buffer;
        };
    }
EDSP_END_NAMESPACE
#endif //EDSP_SPECTROGRAM_H
