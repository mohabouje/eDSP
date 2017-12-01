//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_LINEARPREDICTIVECODING_H
#define EDSP_LINEARPREDICTIVECODING_H


#include "config.h"
#include "transforms/fft.hpp"
#include "autocorrelation.hpp"

EDSP_BEGING_NAMESPACE
    namespace frequency {

        template<typename T, std::size_t Order, std::size_t N = 1024>
        class LinearPredictiveCode {
        public:
            explicit LinearPredictiveCode() = default;
            virtual ~LinearPredictiveCode() = default;
            const std::array<T, Order + 1>& reflection() { return m_reflection; }
            int16 order() const { return m_order; }
            T lpc_error() const { return m_error; }

            template<typename Container>
            typename std::enable_if<std::is_same<typename Container::value_type,
                    T>::value,const std::array<T, Order + 1>&>::type
            compute(const Container& input) {
                std::array<T, Order> temp;
                auto correlation = m_xcorr.compute(input);

                T k;
                m_error = correlation[0];
                m_lpc[0] = 1;

                for (size_t i = 1, size = m_lpc.size(); i < size; i++) {
                    k = correlation[i];

                    for (size_t j = 1; j < i; j++) {
                        k += correlation[i - j] *  m_lpc[j];
                    }

                    k /= m_error;

                    m_reflection[i-1] = k;
                    m_lpc[i] = -k;

                    for (size_t j = 1; j < i; j++) {
                        temp[j] = m_lpc[j] - k * m_lpc[i - j];
                    }

                    for (size_t j = 1; j < i; j++) {
                        m_lpc[j] = temp[j];
                    }

                    m_error *= (1 - k * k);
                }
                return m_lpc;
            }

        private:
            AutoCorrelation<T, N>       m_xcorr{};
            std::array<T, Order + 1>    m_lpc{};
            std::array<T, Order + 1>    m_reflection{};
            int16                       m_order{0};
            T                           m_error{0};
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_LINEARPREDICTIVECODING_H
