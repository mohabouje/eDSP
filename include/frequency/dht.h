//
// Created by Mohammed Boujemaoui on 16/10/2017.
//

#ifndef EDSP_DHT_H
#define EDSP_DHT_H

#include "fft.h"

EDSP_BEGING_NAMESPACE
namespace frequency {
    class DHT : BaseTransform {
    public:
        DHT() : BaseTransform() {}

        template<class InputIterator, class OutputIterator>
        void compute_r2r(InputIterator __first, InputIterator __last, OutputIterator __out) {
            const auto m_size = std::distance(__first, __last);
            if (size != m_size || plan == nullptr) {
                fftw_destroy_plan(plan);
                size = m_size;
                plan = fftw_plan_r2r_1d(static_cast<int>(size),
                                        PTR(__first),
                                        PTR(__out),
                                        FFTW_DHT,
                                        FFTW_MEASURE);
            }
            fftw_execute_r2r(plan, PTR(__first), PTR(__out));
        }
    };
}
EDSP_END_NAMESPACE
#endif //EDSP_DHT_H
