//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#ifndef EDSP_LINEARPREDICTIVECODING_H
#define EDSP_LINEARPREDICTIVECODING_H


#include "autocorrelation.h"
#include <tuple>
#include <functional>

EDSP_BEGIN_NAMESPACE
    namespace frequency {

        class LinearPredictiveCode {
        public:
            explicit LinearPredictiveCode(std::size_t order);;
            ~LinearPredictiveCode() = default;

            const auto& reflection() noexcept { return m_reflection; }
            std::size_t order() const noexcept { return m_order; }
            double lpc_error() const noexcept { return m_error; }
            void set_order(const std::size_t order) noexcept ;

            template<class InputIterator>
            std::tuple<double, std::vector<double>, std::vector<double>> compute(InputIterator first, InputIterator last) {
                const auto size = std::distance(first, last);
                if (buffer.size() != size) { buffer.resize(size); }

                m_xcorr.compute(first, last, std::begin(buffer));
                m_error = buffer[0];
                m_lpc[0] = 1;
                for (std::size_t i = 1, _size = m_lpc.size(); i < _size; ++i) {
                    double k = buffer[i];

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
                return std::make_tuple(m_error, m_lpc, m_reflection);
            }

            private:
                AutoCorrelation m_xcorr{};
                std::vector<double> buffer{};
                std::vector<double> m_lpc{};
                std::vector<double> m_reflection{};
                std::vector<double> m_tmp{};
                std::size_t m_order{0};
                double m_error{0};
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_LINEARPREDICTIVECODING_H
