//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_CEPSTRUM_H
#define EDSP_CEPSTRUM_H


#include "config.h"
#include "fft.h"
#include "ifft.h"
#include "math/complex.h"
EDSP_BEGIN_NAMESPACE
    namespace frequency {
        class Cepstrum  {
        public:
            explicit Cepstrum() = default;

            template<class InputIterator, class OutputIterator>
            void compute(InputIterator first, InputIterator last, OutputIterator out) {
                const auto size = std::distance(first, last);
                if (buffer.size() != size) { buffer.resize(size); }
                std::transform(first, last, std::begin(buffer), [](const auto& val) {
                    return std::complex<double>(val, 0);
                });

                fft.compute_c2c(std::begin(buffer), std::end(buffer), std::begin(buffer));
                std::transform(std::begin(buffer), std::end(buffer), std::begin(buffer), [](std::complex<double>& value) {
                    return std::complex<double>( 2 * std::log(std::abs(value)), 0);
                });
                ifft.compute_c2r(std::begin(buffer), std::end(buffer), out);
            }

        private:
            FFT fft;
            IFFT ifft;
            std::vector<std::complex<double>> buffer;
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_CEPSTRUM_H
