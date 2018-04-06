//
// Created by Mohammed Boujemaoui on 16/10/2017.
//

#ifndef EDSP_IDCT_H
#define EDSP_IDCT_H

#include "dct.h"
EDSP_BEGIN_NAMESPACE
    namespace frequency {
        class IDCT : public BaseTransform {
        public:
            explicit IDCT(DCT_Type t = DCT_Type::Type_I);

            DCT_Type type() const noexcept { return t; }
            void setType(DCT_Type t) noexcept { IDCT::t = t; }

            template <class InputIterator, class OutputIterator>
            void compute_r2r(InputIterator first, InputIterator last, OutputIterator out) {
                const auto m_size = std::distance(first, last);
                if (size != m_size || plan == nullptr) {
                    fftw_destroy_plan(plan);
                    size = m_size;
                    plan = fftw_plan_r2r_1d(static_cast<int>(size),
                                            PTR(first),
                                            PTR(out),
                                            format(),
                                            FFTW_ESTIMATE);
                }
                fftw_execute_r2r(plan, PTR(first), PTR(out));
            }

        private:
            DCT_Type t{DCT_Type::Type_I};
            fftw_r2r_kind format() const noexcept ;
        };
    }
EDSP_END_NAMESPACE
#endif //EDSP_IDCT_H
