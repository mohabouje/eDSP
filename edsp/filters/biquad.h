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
        using BiquadCoefficients = std::array<double, 3>;

        struct BiquadState {
            constexpr void reset() noexcept {
                utility::set(std::begin(inputs), std::end(inputs), 0.);
                utility::set(std::begin(outputs), std::end(outputs), 0.);
            }
            std::array<double, 2> inputs{};
            std::array<double, 2> outputs{};
        };


        class Biquad  {
        public:
            constexpr explicit Biquad() = default;
            constexpr explicit Biquad(const BiquadCoefficients &a, const BiquadCoefficients &b) :
                    m_a(a),
                    m_b(b)
            {
            }
            ~Biquad() = default;

            template<class InputIterator, class OutputIterator>
            constexpr void compute(InputIterator first, InputIterator last, OutputIterator out) {
                for (; first != last; ++first, ++out) {
                    compute(*first, *out);
                }
            }

            template<typename C>
            constexpr void compute(const C in, C& out) {
                const auto input = in *  m_gain;
                out = (m_b[0] * input
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

            constexpr const BiquadState& state() const noexcept { return m_state; }
            constexpr const BiquadCoefficients& a() const noexcept { return m_a; }
            constexpr const BiquadCoefficients& b() const noexcept { return m_b; }
            constexpr double a0() const noexcept { return m_a[0]; }
            constexpr double a1() const noexcept { return m_a[1]; }
            constexpr double a2() const noexcept { return m_a[2]; }
            constexpr double b0() const noexcept { return m_a[0]; }
            constexpr double b1() const noexcept { return m_b[1]; }
            constexpr double b2() const noexcept { return m_b[2]; }
            constexpr double gain() const noexcept { return m_gain; }

            constexpr void set_a(const BiquadCoefficients& tmp) noexcept { m_a = tmp; }
            constexpr void set_b(const BiquadCoefficients& tmp) noexcept { m_b = tmp; }

            constexpr void set_a0(const double value) noexcept { m_a[0] = value; }
            constexpr void set_a1(const double value) noexcept { m_a[1] = value; }
            constexpr void set_a2(const double value) noexcept { m_a[2] = value; }
            constexpr void set_b0(const double value) noexcept { m_b[0] = value; }
            constexpr void set_b1(const double value) noexcept { m_b[1] = value; }
            constexpr void set_b2(const double value) noexcept { m_b[2] = value; }
            constexpr void set_gain(const double value) noexcept { m_gain = value; }

            constexpr void reset() { m_state.reset(); }

        private:
            BiquadCoefficients m_a{};
            BiquadCoefficients m_b{};
            BiquadState        m_state{};
            double             m_gain{1};
        };

    }
EDSP_END_NAMESPACE
#endif //EDSP_BIQUAD_H
