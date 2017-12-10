//
// Created by Mohammed Boujemaoui on 10/12/2017.
//

#ifndef EDSP_FIR_H
#define EDSP_FIR_H

#include "config.h"
#include "utility/vector.h"
#include <vector>

EDSP_BEGIN_NAMESPACE
    namespace filters {

        template <typename T>
        class FIR  {
        public:
            explicit FIR(const std::vector<T> &m_b) :
                    m_b(m_b),
                    m_inputs{m_b.size(), 0} {

            }

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

            void set_gain(const T value) {
                m_gain = value;
            }

            T gain() const {
                return m_gain;
            }

            void reset() {
                utility::set(std::begin(m_inputs), std::end(m_inputs), 0);
            }
        private:
            T               m_gain{};
            std::vector<T>  m_b{};
            std::vector<T>  m_inputs{};
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_FIR_H
