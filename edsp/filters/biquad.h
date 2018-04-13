//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_BIQUAD_H
#define EDSP_BIQUAD_H

#include "config.h"
#include "utility/vector.h"
#include <array>
#include <algorithm>

EDSP_BEGIN_NAMESPACE
    namespace filters {
        using BiquadCoefficients = std::array<real_t, 3>;

        struct BiquadState {
             void reset() noexcept {
                utility::set(std::begin(inputs), std::end(inputs), 0.);
                utility::set(std::begin(outputs), std::end(outputs), 0.);
            }
            std::array<real_t, 2> inputs{};
            std::array<real_t, 2> outputs{};
        };


        class Biquad  {
            EDSP_DECLARE_ALL_IMPLICITS(Biquad)
        public:
            EDSP_DEFAULT_CONSTRUCTOR(Biquad)
            EDSP_DEFAULT_DESTRUCTOR(Biquad)

            explicit Biquad(const BiquadCoefficients &a, const BiquadCoefficients &b);

            template<class InputIterator, class OutputIterator>
            EDSP_INLINE void compute(InputIterator first, InputIterator last, OutputIterator out) {
                for (; first != last; ++first, ++out) {
                    const auto input = *first *  m_gain;
                    *out = (m_b[0] * input
                             + m_b[1] * m_state.inputs[0]
                             + m_b[2] * m_state.inputs[1]
                             - m_a[1] * m_state.outputs[0]
                             - m_a[2] * m_state.outputs[1]) / m_a[0];

                    // Circular buffer;
                    m_state.inputs[1] = m_state.inputs[0];
                    m_state.inputs[0] = input;

                    m_state.outputs[1] = m_state.outputs[0];
                    m_state.outputs[0] = out;
                }
            }

            EDSP_INLINE const BiquadState& state() const noexcept;
            EDSP_INLINE const BiquadCoefficients& a() const noexcept;
            EDSP_INLINE const BiquadCoefficients& b() const noexcept;
            EDSP_INLINE real_t a0() const noexcept;
            EDSP_INLINE real_t a1() const noexcept;
            EDSP_INLINE real_t a2() const noexcept;
            EDSP_INLINE real_t b0() const noexcept;
            EDSP_INLINE real_t b1() const noexcept;
            EDSP_INLINE real_t b2() const noexcept;
            EDSP_INLINE real_t gain() const noexcept;

            EDSP_INLINE void set_a(const BiquadCoefficients& tmp) noexcept;
            EDSP_INLINE void set_b(const BiquadCoefficients& tmp) noexcept;
            EDSP_INLINE void set_a0(const real_t value) noexcept;
            EDSP_INLINE void set_a1(const real_t value) noexcept;
            EDSP_INLINE void set_a2(const real_t value) noexcept;
            EDSP_INLINE void set_b0(const real_t value) noexcept;
            EDSP_INLINE void set_b1(const real_t value) noexcept;
            EDSP_INLINE void set_b2(const real_t value) noexcept;
            EDSP_INLINE void set_gain(const real_t value) noexcept;
            EDSP_INLINE void reset() noexcept;
        private:
            BiquadCoefficients m_a{};
            BiquadCoefficients m_b{};
            BiquadState        m_state{};
            real_t             m_gain{1};
        };

        Biquad::Biquad(const BiquadCoefficients &a, const BiquadCoefficients &b) :
            m_a(a),
            m_b(b)
        {
        }

    const BiquadState& Biquad::state() const noexcept { return m_state; }
    const BiquadCoefficients& Biquad::a() const noexcept { return m_a; }
    const BiquadCoefficients& Biquad::b() const  noexcept { return m_b; }
    real_t Biquad::a0() const noexcept { return m_a[0]; }
    real_t Biquad::a1() const noexcept { return m_a[1]; }
    real_t Biquad::a2() const noexcept { return m_a[2]; }
    real_t Biquad::b0() const noexcept { return m_a[0]; }
    real_t Biquad::b1() const noexcept { return m_b[1]; }
    real_t Biquad::b2() const noexcept { return m_b[2]; }
    real_t Biquad::gain() const noexcept { return m_gain; }

    void Biquad::set_a(const BiquadCoefficients& tmp) noexcept { m_a = tmp; }
    void Biquad::set_b(const BiquadCoefficients& tmp) noexcept { m_b = tmp; }

    void Biquad::set_a0(const real_t value) noexcept { m_a[0] = value; }
    void Biquad::set_a1(const real_t value) noexcept { m_a[1] = value; }
    void Biquad::set_a2(const real_t value) noexcept { m_a[2] = value; }
    void Biquad::set_b0(const real_t value) noexcept { m_b[0] = value; }
    void Biquad::set_b1(const real_t value) noexcept { m_b[1] = value; }
    void Biquad::set_b2(const real_t value) noexcept { m_b[2] = value; }
    void Biquad::set_gain(const real_t value) noexcept { m_gain = value; }
    void Biquad::reset() noexcept { m_state.reset(); }

}
EDSP_END_NAMESPACE
#endif //EDSP_BIQUAD_H
