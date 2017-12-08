//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_LINEARPREDICTIVECODING_H
#define EDSP_LINEARPREDICTIVECODING_H


#include "config.h"
#include "fft.h"
#include "autocorrelation.h"
#include <array>

EDSP_BEGING_NAMESPACE
    namespace frequency {

        template<typename T, std::size_t Order>
        class LinearPredictiveCode {
        public:
            explicit LinearPredictiveCode() = default;
            virtual ~LinearPredictiveCode() = default;
            const std::array<T, Order + 1>& reflection() { return m_reflection; }
            int16_t order() const { return m_order; }
            T lpc_error() const { return m_error; }

            template<class InputIterator>
            const std::array<T, Order + 1>& compute(InputIterator __first, InputIterator __last) {
                const auto size = std::distance(__first, __last);
                if (buffer.size() != size) { buffer.resize(size); }

                std::array<T, Order> temp;
                m_xcorr.compute(__first, __last, std::begin(buffer));

                T k;
                m_error = buffer[0];
                m_lpc[0] = 1;

                for (auto i = 1, _size = m_lpc.size(); i < _size; ++i) {
                    k = buffer[i];

                    for (auto j = 1; j < i; ++j) {
                        k += buffer[i - j] *  m_lpc[j];
                    }

                    k /= m_error;

                    m_reflection[i-1] = k;
                    m_lpc[i] = -k;

                    for (auto j = 1; j < i; ++j) {
                        temp[j] = m_lpc[j] - k * m_lpc[i - j];
                    }

                    for (auto j = 1; j < i; ++j) {
                        m_lpc[j] = temp[j];
                    }

                    m_error *= (1 - k * k);
                }
                return m_lpc;
            }

        private:
            std::vector<std::complex<T>> buffer;
            AutoCorrelation             m_xcorr{};
            std::array<T, Order + 1>    m_lpc{};
            std::array<T, Order + 1>    m_reflection{};
            int16_t                     m_order{0};
            T                           m_error{0};
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_LINEARPREDICTIVECODING_H
