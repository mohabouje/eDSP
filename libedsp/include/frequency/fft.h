//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#ifndef EDSP_REALFFT_H
#define EDSP_REALFFT_H

#include "base/transform.h"
#include <complex>
#include <array>
#include <fftw3.h>

EDSP_BEGIN_NAMESPACE
    namespace frequency {
        class FFT : public BaseTransform {
        public:
            FFT() = default;
            ~FFT() override = default;

            template <class InputIterator, class OutputIterator>
            void compute_c2c(InputIterator first, InputIterator last, OutputIterator out) {
                const auto m_size = std::distance(first, last);
                if (size != m_size || plan == nullptr) {
                    fftw_destroy_plan(plan);
                    size = m_size;
                    plan = fftw_plan_dft_1d(static_cast<int>(size),
                                                reinterpret_cast<fftw_complex *>(PTR(first)),
                                                reinterpret_cast<fftw_complex *>(PTR(out)),
                                                FFTW_FORWARD, FFTW_ESTIMATE);
                }
                fftw_execute_dft(plan,
                                 reinterpret_cast<fftw_complex *>(PTR(first)),
                                 reinterpret_cast<fftw_complex *>(PTR(out)));

            }

            template <class InputIterator, class OutputIterator>
            void compute_r2c(InputIterator first, InputIterator last, OutputIterator out) {
                const auto m_size = std::distance(first, last);
                if (size != m_size || plan == nullptr) {
                    fftw_destroy_plan(plan);
                    size = m_size;
                    plan = fftw_plan_dft_r2c_1d(static_cast<int>(size), PTR(first), reinterpret_cast<fftw_complex *>(PTR(out)), FFTW_ESTIMATE);
                }
                fftw_execute_dft_r2c(plan, PTR(first), reinterpret_cast<fftw_complex *>(PTR(out)));
            }
        };
    }
EDSP_END_NAMESPACE



#endif //EDSP_REALFFT_H
