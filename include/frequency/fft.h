//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#ifndef EDSP_REALFFT_H
#define EDSP_REALFFT_H

#include "base/transform.h"
#include <complex>
#include <array>
#include <fftw3.h>

EDSP_BEGING_NAMESPACE
    namespace frequency {
        class FFT : public BaseTransform {
        public:
            template <class InputIterator, class OutputIterator>
            void compute_c2c(InputIterator __first, InputIterator __last, OutputIterator __out) {
                const auto m_size = std::distance(__first, __last);
                if (size != m_size && plan != nullptr) {
                    fftw_destroy_plan(plan);
                    size = m_size;
                    plan = fftw_plan_dft_1d(static_cast<int>(size),
                                                reinterpret_cast<fftw_complex *>(__first),
                                                reinterpret_cast<fftw_complex *>(__out),
                                                FFTW_FORWARD, FFTW_ESTIMATE);
                }
                fftw_execute_dft(plan,
                                 reinterpret_cast<fftw_complex *>(__first),
                                 reinterpret_cast<fftw_complex *>(__out));

            }

            template <class InputIterator, class OutputIterator>
            void compute_r2c(InputIterator __first, InputIterator __last, OutputIterator __out) {
                const auto m_size = std::distance(__first, __last);
                if (size != m_size && plan != nullptr) {
                    fftw_destroy_plan(plan);
                    size = m_size;
                    plan = fftw_plan_dft_r2c_1d(static_cast<int>(size),
                                            __first,
                                            __out,
                                            FFTW_ESTIMATE);
                }
                fftw_execute_dft_r2c(plan,
                                 __first,
                                 __out);
            }
        };
    }
EDSP_END_NAMESPACE



#endif //EDSP_REALFFT_H
