//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_BIQUAD_H
#define EDSP_BIQUAD_H

#include "config.h"
#include "base/algoritmtemplate.h"
#include <algorithm>
EDSP_BEGING_NAMESPACE
    namespace Filters {
        template <typename T>
        using BiquadCoefficients = std::array<T, 3>;

        template<typename T>
        class BiquadState {
        public:
            BiquadState() {
                std::fill(inputs.begin(), inputs.end(), static_cast<T>(0));
                std::fill(outputs.begin(), outputs.end(), static_cast<T>(0));
            }

            inline const std::array<T, 2>& last_inputs() const { return  inputs; };
            inline const std::array<T, 2>& last_outputs() const { return  outputs; };
        private:
            friend class Biquad;
            std::array<T, 2> inputs{};
            std::array<T, 2> outputs{};

        };

        template<typename T>
        class Biquad : AlgorithmTemplate {
        public:
            explicit Biquad() : AlgorithmTemplate(true, Error()) {}
            explicit Biquad(const BiquadCoefficients& a, const BiquadCoefficients& b) :
                    AlgorithmTemplate(true, Error()),
                    m_a(a),
                    m_b(b)
            {
            }
            ~Biquad() override = default;
            const std::vector<T>& compute(const std::vector<T>&input) {
                m_out.resize(input.size());
                for (size_t i = 0, size = input.size(); i < size; i++) {
                    m_out[i] = (m_b[0] * input[i]
                             + m_b[1] * m_state.inputs[0]
                             + m_b[2] * m_state.inputs[1]
                             - m_a[1] * m_state.outputs[0]
                             - m_a[2] * m_state.outputs[1]) / m_a[0];

                    // Circular buffer;
                    m_state.inputs[1] = m_state.inputs[0];
                    m_state.inputs[0] = input[i];

                    m_state.outputs[1] = m_state.outputs[0];
                    m_state.outputs[0] = m_out[i];
                } 
                return m_out;
            }

            inline const BiquadState& state() const { return m_state; }
            inline const BiquadCoefficients& a() const { return m_a; }
            inline const BiquadCoefficients& b() const { return m_b; }
            inline T a0() const { return m_a[0]; }
            inline T a1() const { return m_a[1]; }
            inline T a2() const { return m_a[2]; }

            inline T b0() const { return m_a[0]; }
            inline T b1() const { return m_b[1]; }
            inline T b2() const { return m_b[2]; }

            void set_a(const BiquadCoefficients& tmp) { std::copy(tmp.begin(), tmp.end(), m_a.begin()); }
            void set_b(const BiquadCoefficients& tmp) { std::copy(tmp.begin(), tmp.end(), m_b.begin()); }

            void set_a0(T value) { m_a[0] = value; }
            void set_a1(T value) { m_a[1] = value; }
            void set_a2(T value) { m_a[2] = value; }

            void set_b0(T value) { m_b[0] = value; }
            void set_b1(T value) { m_b[1] = value; }
            void set_b2(T value) { m_b[2] = value; }

        private:
            BiquadCoefficients m_a{};
            BiquadCoefficients m_b{};
            BiquadState        m_state{};
            std::vector<T>     m_out{};
        };

    }
EDSP_END_NAMESPACE
#endif //EDSP_BIQUAD_H
