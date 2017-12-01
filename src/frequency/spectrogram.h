//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_SPECTROGRAM_H
#define EDSP_SPECTROGRAM_H

#include "config.h"
#include "transforms/fft.h"
#include "math/complex.h"
EDSP_BEGING_NAMESPACE
    namespace frequency {
        template<typename T, std::size_t N>
        class Spectrogram {
        public:
            Spectrogram() = default;
            virtual ~Spectrogram() = default;

            template<typename Container>
            typename std::enable_if<std::is_same<typename Container::value_type,
                    T>::value, Container>::type
            compute(const Container& input) {
                Container data(N);
                const auto& fft_data = fft.compute(math::complex::real_to_complex(input));
                std::transform(fft_data.begin(), fft_data.end(), data.begin(), [](const std::complex<T>& value) {
                    auto tmp = static_cast<T>(std::abs(value));
                    return  (tmp * tmp);
                });
                return data;
            };


            template<typename Container>
            typename std::enable_if<std::is_same<typename Container::value_type,
                    T>::value, Container>::type
            compute_db(const Container& input) {
                Container data(N);
                const auto& fft_data = fft.compute(math::complex::real_to_complex(input));
                std::transform(fft_data.begin(), fft_data.end(), data.begin(), [](const std::complex<T>& value) {
                    auto tmp = static_cast<T>(std::abs(value));
                    return 20 * log10(tmp);
                });
                return data;
            };

        private:
            transforms::FFT<T, N> fft{};
        };
    }
EDSP_END_NAMESPACE
#endif //EDSP_SPECTROGRAM_H
