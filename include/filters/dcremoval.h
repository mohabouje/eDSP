#ifndef EDSP_DCREMOVAL_H
#define EDSP_DCREMOVAL_H

#include "biquad.h"

EDSP_BEGIN_NAMESPACE
    namespace filters {

        template <typename T>
        class DCRemoval : private Biquad<T> {
        public:
            explicit DCRemoval(T alpha = 0.995) :
                alpha(alpha),
                Biquad<T>({1, -alpha, 0}, {1, -1, 0}) {

            }

            template<class InputIterator, class OutputIterator>
            void apply(InputIterator first, InputIterator last, OutputIterator out) {
                Biquad<T>::compute(first, last, out);
            }

            void set_alpha(const T _alpha) {
                alpha = _alpha;
                Biquad<T>::set_a1(alpha);
            }
        private:
            T alpha{0.995};
        };
    }
EDSP_END_NAMESPACE

#endif // DCREMOVAL_H
