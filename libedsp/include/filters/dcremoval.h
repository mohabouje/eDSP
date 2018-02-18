#ifndef EDSP_DCREMOVAL_H
#define EDSP_DCREMOVAL_H

#include "biquad.h"

EDSP_BEGIN_NAMESPACE
    namespace filters {

        class DCRemoval {
        public:
            constexpr DCRemoval() = default;
            constexpr explicit DCRemoval(double alpha = 0.995) :
                biquad_(Biquad({1, -alpha, 0}, {1, -1, 0})) {

            }
            template<class InputIterator, class OutputIterator>
            void compute(InputIterator first, InputIterator last, OutputIterator out) {
                Biquad::compute(first, last, out);
            }

            constexpr double alpha() const noexcept{ return biquad_.a1(); }
            constexpr void set_alpha(const double alpha) noexcept {
                biquad_.set_a1(alpha);
            }
        private:
            T alpha_{0.995};
            Biquad biquad_;
        };
    }
EDSP_END_NAMESPACE

#endif // DCREMOVAL_H
