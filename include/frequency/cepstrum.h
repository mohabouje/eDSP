//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_CEPSTRUM_H
#define EDSP_CEPSTRUM_H


#include "config.h"
#include "fft.h"
#include "ifft.h"
#include "math/complex.h"
EDSP_BEGING_NAMESPACE
    namespace frequency {
        class Cepstrum  {
        public:
            explicit Cepstrum() = default;

            template<class InputIterator, class OutputIterator>
            void compute(InputIterator __first, InputIterator __last, OutputIterator __out) {
                const auto size = std::distance(__first, __last);
                if (buffer.size() != size) { buffer.resize(size); }
                std::transform(__first, __last, std::begin(buffer), [](const auto& val) {
                    return std::complex<double>(val, 0);
                });

                fft.compute_c2c(std::begin(buffer), std::end(buffer), std::begin(buffer));
                std::transform(std::begin(buffer), std::end(buffer), std::begin(buffer), [](std::complex<double>& value) {
                    return std::complex<double>( 2 * std::log(std::abs(value)), 0);
                });
                ifft.compute_c2r(std::begin(buffer), std::end(buffer), __out);
            }

        private:
            FFT fft;
            IFFT ifft;
            std::vector<std::complex<double>> buffer;
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_CEPSTRUM_H
