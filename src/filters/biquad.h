//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_BIQUAD_H
#define EDSP_BIQUAD_H

#include "config.h"
#include "base/algoritmtemplate.h"
EDSP_BEGING_NAMESPACE
    namespace Filters {
        template<typename T>
        class Biquad : AlgorithmTemplate {
        public:
            explicit Biquad() : AlgorithmTemplate(true, Error()) {}
            explicit Biquad(const std::array<T, 3>& a, const std::array<T, 3>& b) :
                    AlgorithmTemplate(true, Error()),
                    m_a(a),
                    m_b(b)
            {
            }
            ~Biquad() override = default;
            const std::vector<T>& compute(const std::vector<T>&a) {
                return a;
            }

            inline const std::array<T, 3>& a() { return m_a; }
            inline const std::array<T, 3>& b() { return m_b; }
            inline T a0() const { return m_a[0]; }
            inline T a1() const { return m_a[1]; }
            inline T a2() const { return m_a[2]; }

            inline T b0() const { return m_a[0]; }
            inline T b1() const { return m_b[1]; }
            inline T b2() const { return m_b[2]; }

            void setA(const std::array<T, 3>& tmp) { std::copy(tmp.begin(), tmp.end(), m_a.begin()); }
            void setB(const std::array<T, 3>& tmp) { std::copy(tmp.begin(), tmp.end(), m_b.begin()); }

            void setA_0(T value) { m_a[0] = value; }
            void setA_1(T value) { m_a[1] = value; }
            void setA_2(T value) { m_a[2] = value; }

            void setB_0(T value) { m_b[0] = value; }
            void setB_1(T value) { m_b[1] = value; }
            void setB_2(T value) { m_b[2] = value; }

        private:
            std::array<T, 3> m_a;
            std::array<T, 3> m_b;
        };
    }
EDSP_END_NAMESPACE
#endif //EDSP_BIQUAD_H
