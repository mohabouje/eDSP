//
// Created by Mohammed Boujemaoui on 10/12/2017.
//

#ifndef EDSP_FIR_H
#define EDSP_FIR_H

#include "config.h"
#include <vector>

EDSP_BEGIN_NAMESPACE
    namespace filters {

        class FIR  {
        public:
            FIR() = default;
            explicit FIR(const std::vector<double> &m_b);
            ~FIR() = default;

            template <class InputIterator, class OutputIterator>
            void compute(const InputIterator first, const InputIterator last, OutputIterator out) {
                for (; first != last; ++first, ++out) {
                    m_inputs[0] = (*first * m_gain);
                    *out = 0;
                    *out +=  m_b[0] * m_inputs[0];
                    for (auto i = m_b.size() - 1; i > 0; --i) {
                        *out += m_b[i] * m_inputs[i];
                        m_inputs[i] = m_inputs[i-1];
                    }
                }
            };

            void set_gain(const double value) noexcept { m_gain = value; }
            double gain() const noexcept { return m_gain; }
            void reset() noexcept;
        private:
            double               m_gain{1};
            std::vector<double>  m_b{};
            std::vector<double>  m_inputs{};
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_FIR_H
