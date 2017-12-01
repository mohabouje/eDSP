//
// Created by Mohammed Boujemaoui on 16/10/2017.
//

#ifndef EDSP_IFFT_H
#define EDSP_IFFT_H

#include "utility/vector_util.hpp"
#include <fftw3.h>
#include <assert.h>

EDSP_BEGING_NAMESPACE
    namespace transforms {

        template<typename T, std::size_t N>
        class IFFT {
        public:
            explicit IFFT() {
                fftwPlan = fftw_plan_dft_1d(static_cast<int>(N),
                                            reinterpret_cast<fftw_complex *>(&input[0]),
                                            reinterpret_cast<fftw_complex *>(&output[0]),
                                            FFTW_BACKWARD, FFTW_ESTIMATE);
            }
            virtual ~IFFT() { fftw_destroy_plan(fftwPlan); }

            template<typename Container>
            typename std::enable_if<std::is_same<typename Container::value_type,
                    std::complex<T>>::value, const std::array<std::complex<double>, N>&>::type
            compute(const Container& data) {
                assert(data.size() <= input.size());
                std::transform(data.begin(), data.end(), input.begin(), [](std::complex<T> tmp) {
                    return std::complex<double>(tmp.real(), tmp.imag());
                });
                fftw_execute(fftwPlan);
                return output;
            }
        private:
            fftw_plan fftwPlan{nullptr};
            std::array<std::complex<double>, N>  input{};
            std::array<std::complex<double>, N>  output{};
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_IFFT_H
