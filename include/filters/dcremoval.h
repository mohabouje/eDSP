#ifndef EDSP_DCREMOVAL_H
#define EDSP_DCREMOVAL_H

#include "biquad.h"

EDSP_BEGIN_NAMESPACE
    namespace filters {

        template <typename T>
        class DCRemoval : public Biquad<T> {
        public:
            explicit DCRemoval(const T alpha = 0.995) :
                Biquad<T>({{1, -alpha, 0}}, {{1, -1, 0}}),
                m_alpha(alpha) { }

            void set_alpha(const T alpha) {
                m_alpha = alpha;
                Biquad<T>::set_a1(m_alpha);
            }

            T alpha() const { return m_alpha; }
        private:
            T m_alpha{0.995};
        };
    }
EDSP_END_NAMESPACE

#endif // DCREMOVAL_H
