//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_LINEARPREDICTIVECODING_H
#define EDSP_LINEARPREDICTIVECODING_H


#include "config.h"
#include "transforms/fft.hpp"
#include "autocorrelation.hpp"

EDSP_BEGING_NAMESPACE
    namespace Frequency {

        template<typename T>
        class LinearPredictiveCode {
        public:
            explicit LinearPredictiveCode<T>::LinearPredictiveCode(eDSP::int16 order, size_t size = 1024) :
                    m_order(order),
                    xcorr(),
                    m_reflection(std::vector<T>(static_cast<unsigned long>(order + 1))),
                    lpc(std::vector<T>(static_cast<unsigned long>(order + 1)))
            {
            }
            virtual ~LinearPredictiveCode() = default;
            const std::vector<T>& reflection() { return m_reflection; }
            int16 order() const { return m_order; }
            T lpc_error() const { return m_error; }



            const std::vector<T>& compute(const std::vector<T>& input) {
                static std::vector<T> temp(static_cast<unsigned long>(m_order));
                const std::vector<T>& correlation = xcorr.compute(input);


                T k;
                m_error = correlation[0];
                lpc[0] = 1;

                for (size_t i = 1, size = lpc.size(); i < size; i++) {
                    k = correlation[i];

                    for (size_t j = 1; j < i; j++) {
                        k += correlation[i - j] *  lpc[j];
                    }

                    k /= m_error;

                    m_reflection[i-1] = k;
                    lpc[i] = -k;

                    for (size_t j = 1; j < i; j++) {
                        temp[j] = lpc[j] - k * lpc[i - j];
                    }

                    for (size_t j = 1; j < i; j++) {
                        lpc[j] = temp[j];
                    }

                    m_error *= (1 - k * k);
                }
                return lpc;
            }

        private:
            AutoCorrelation<T> xcorr{};
            std::vector<T> lpc{};
            std::vector<T> m_reflection{};
            int16          m_order{0};
            T              m_error{0};
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_LINEARPREDICTIVECODING_H
