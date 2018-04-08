//
// Created by Mohammed Boujemaoui on 22/10/2017.
//

#ifndef EDSP_CROSSCORRELATION_H
#define EDSP_CROSSCORRELATION_H

#include "config.h"
#include "math/complex.h"
#include "fft.h"
#include "ifft.h"
EDSP_BEGIN_NAMESPACE
    namespace frequency {
        class AutoCorrelation  {
        public:
            template<class InputIterator, class OutputIterator>
            void compute(InputIterator first, InputIterator last, OutputIterator out) {
                const auto size = std::distance(first, last);
                if (buffer.size() != size) { buffer.resize(size); }
                std::transform(first, last, std::begin(buffer), [](const auto& val) {
                    return std::complex<double>(val, 0);
                });

                fft.compute_c2c(std::begin(buffer), std::end(buffer), std::begin(buffer));
                std::transform(std::begin(buffer), std::end(buffer), std::begin(buffer), [](std::complex<double>& value) {
                    const auto tmp = std::abs(value);
                    return std::complex<double>(tmp * tmp, 0);
                });

                ifft.compute_c2r(std::begin(buffer), std::end(buffer), out);
            }
        private:
            std::vector<std::complex<double>> buffer;
            DFT  fft;
            IFFT ifft;
        };
    }
EDSP_END_NAMESPACE


#endif //EDSP_CROSSCORRELATION_H
