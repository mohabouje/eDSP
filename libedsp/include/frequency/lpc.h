//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_LINEARPREDICTIVECODING_H
#define EDSP_LINEARPREDICTIVECODING_H


#include "config.h"
#include "fft.h"
#include "autocorrelation.h"
#include <array>

EDSP_BEGIN_NAMESPACE
    namespace frequency {

        template<typename T>
        class LinearPredictiveCode {
        public:
            explicit LinearPredictiveCode() = default;
            virtual ~LinearPredictiveCode() = default;
            const auto& reflection() { return m_reflection; }
            std::size_t order() const { return m_order; }
            T lpc_error() const { return m_error; }

            void set_order(const std::size_t order) {
                if (order != m_order) {
                    m_lpc.resize(m_order + 1);
                    m_reflection.resize(m_order + 1);
                    m_tmp.resize(m_order + 1);
                }
            }

            template<class InputIterator>
            std::tuple<T, std::vector<T>, std::vector<T>> compute(InputIterator first, InputIterator last) {
                const auto size = std::distance(first, last);
                if (buffer.size() != size) { buffer.resize(size); }

                m_xcorr.compute(first, last, std::begin(buffer));
                m_error = buffer[0];
                m_lpc[0] = 1;
                for (int i = 1, _size = m_lpc.size(); i < _size; ++i) {
                    T k = buffer[i];

                    for (auto j = 1; j < i; ++j) {
                        k += buffer[i - j] *  m_lpc[j];
                    }

                    k /= m_error;

                    m_reflection[i-1] = k;
                    m_lpc[i] = -k;

                    for (auto j = 1; j < i; ++j) {
                        m_tmp[j] = m_lpc[j] - k * m_lpc[i - j];
                    }

                    for (auto j = 1; j < i; ++j) {
                        m_lpc[j] = m_tmp[j];
                    }

                    m_error *= (1 - k * k);
                }
                return std::tuple<T, std::vector<T>, std::vector<T>>(m_error, m_lpc, m_reflection);
            }

        private:
            AutoCorrelation             m_xcorr{};
            std::vector<T>              buffer;
            std::vector<T>              m_lpc{};
            std::vector<T>              m_reflection{};
            std::vector<T>              m_tmp{};
            std::size_t                 m_order{0};
            T                           m_error{0};
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_LINEARPREDICTIVECODING_H
