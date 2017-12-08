//
// Created by Mohammed Boujemaoui on 16/10/2017.
//

#ifndef EDSP_IFFT_H
#define EDSP_IFFT_H

#include "fft.h"


EDSP_BEGING_NAMESPACE
    namespace frequency {
        class IFFT : public BaseTransform {
        public:
            template <class InputIterator, class OutputIterator>
            void compute_c2c(InputIterator __first, InputIterator __last, OutputIterator __out) {
                const auto m_size = std::distance(__first, __last);
                if (size != m_size || plan == nullptr) {
                    fftw_destroy_plan(plan);
                    size = m_size;
                    plan = fftw_plan_dft_1d(static_cast<int>(size),
                                            reinterpret_cast<fftw_complex *>(PTR(__first)),
                                            reinterpret_cast<fftw_complex *>(PTR(__out)),
                                            FFTW_BACKWARD, FFTW_ESTIMATE);
                }
                fftw_execute_dft(plan,
                                 reinterpret_cast<fftw_complex *>(PTR(__first)),
                                 reinterpret_cast<fftw_complex *>(PTR(__out)));
                scale_output(__out);

            }

            template <class InputIterator, class OutputIterator>
            void compute_c2r(InputIterator __first, InputIterator __last, OutputIterator __out) {
                const auto m_size = std::distance(__first, __last);
                if (size != m_size || plan == nullptr) {
                    fftw_destroy_plan(plan);
                    size = m_size;
                    plan = fftw_plan_dft_c2r_1d(static_cast<int>(size),
                                                reinterpret_cast<fftw_complex *>(PTR(__first)),
                                                PTR(__out),
                                                FFTW_ESTIMATE | FFTW_PRESERVE_INPUT);
                }
                fftw_execute_dft_c2r(plan, reinterpret_cast<fftw_complex *>(PTR(__first)), PTR(__out));
                scale_output(__out);
            }

        private:
            template <class OutputIterator>
            void scale_output(OutputIterator __out) const {
                for (auto i = 0; i < size; ++i, ++__out) {
                    *__out /= static_cast<typename std::iterator_traits<OutputIterator>::value_type>(size);
                }
            }
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_IFFT_H
