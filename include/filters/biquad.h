//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_BIQUAD_H
#define EDSP_BIQUAD_H

#include "config.h"
#include <array>
#include <algorithm>
EDSP_BEGIN_NAMESPACE
    namespace filters {
        template <typename T>
        using BiquadCoefficients = std::array<T, 3>;

        template<typename T>
        struct BiquadState {
            std::array<T, 2> inputs{};
            std::array<T, 2> outputs{};
        };

        template<typename T>
        class Biquad  {
        public:
            explicit Biquad() = default;
            explicit Biquad(const BiquadCoefficients<T>& a, const BiquadCoefficients<T>& b) :
                    m_a(a),
                    m_b(b)
            {
            }
            virtual ~Biquad() = default;

            template<class ForwardIterator, class OutputIterator>
            void compute(ForwardIterator __first, ForwardIterator __last, OutputIterator __out) {
                const auto size = std::distance(__first, __last);
                const auto input(__first, __last);
                for (; __first != __last; ++__last, ++__out) {
                    *__out = (m_b[0] * *__first
                             + m_b[1] * m_state.inputs[0]
                             + m_b[2] * m_state.inputs[1]
                             - m_a[1] * m_state.outputs[0]
                             - m_a[2] * m_state.outputs[1]) / m_a[0];

                    // Circular buffer;
                    m_state.inputs[1] = m_state.inputs[0];
                    m_state.inputs[0] = *__last;

                    m_state.outputs[1] = m_state.outputs[0];
                    m_state.outputs[0] = *__out;
                }
            }

            const BiquadState<T>& state() const { return m_state; }
            const BiquadCoefficients<T>& a() const { return m_a; }
            const BiquadCoefficients<T>& b() const { return m_b; }
            T a0() const { return m_a[0]; }
            T a1() const { return m_a[1]; }
            T a2() const { return m_a[2]; }

            T b0() const { return m_a[0]; }
            T b1() const { return m_b[1]; }
            T b2() const { return m_b[2]; }

            void set_a(const BiquadCoefficients<T>& tmp) { std::copy(tmp.begin(), tmp.end(), m_a.begin()); }
            void set_b(const BiquadCoefficients<T>& tmp) { std::copy(tmp.begin(), tmp.end(), m_b.begin()); }

            void set_a0(T value) { m_a[0] = value; }
            void set_a1(T value) { m_a[1] = value; }
            void set_a2(T value) { m_a[2] = value; }

            void set_b0(const T value) { m_b[0] = value; }
            void set_b1(const T value) { m_b[1] = value; }
            void set_b2(const T value) { m_b[2] = value; }

        private:
            BiquadCoefficients<T> m_a{};
            BiquadCoefficients<T> m_b{};
            BiquadState<T>        m_state{};
        };

    }
EDSP_END_NAMESPACE
#endif //EDSP_BIQUAD_H
