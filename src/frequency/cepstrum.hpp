//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_CEPSTRUM_H
#define EDSP_CEPSTRUM_H


#include "config.h"
#include "transforms/fft.hpp"
#include "transforms/ifft.hpp"
#include "math/complex.hpp"
EDSP_BEGING_NAMESPACE
    namespace frequency {
        template<typename T, std::size_t N = 1024>
        class Cepstrum  {
        public:
            explicit Cepstrum() = default;
            virtual ~Cepstrum() = default;
            template<typename Container>
            typename std::enable_if<std::is_same<typename Container::value_type,
                    T>::value, Container>::type
            compute(const Container& input) {
                Container data(N);
                auto fft_data = fft.compute(math::complex::real_to_complex(input));
                std::transform(fft_data.begin(), fft_data.end(), fft_data.begin(), [](std::complex<T>& value) {
                    return std::complex<T>( 2 * std::log(std::abs(value)), 0);
                });

                fft_data = ifft.compute(fft_data);

                std::transform(fft_data.begin(), fft_data.end(), data.begin(), [](const std::complex<T>& value) {
                    return value.real();
                });

                return data;
            }
        private:
            transforms::FFT<T,N> fft;
            transforms::IFFT<T,N> ifft;
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_CEPSTRUM_H
