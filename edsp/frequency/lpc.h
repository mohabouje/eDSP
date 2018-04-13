/*
 * eDSP, A cross-platform DSP framework written in C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef EDSP_LINEARPREDICTIVECODING_H
#define EDSP_LINEARPREDICTIVECODING_H

#include "autocorrelation.h"
#include <tuple>
#include <functional>

EDSP_BEGIN_NAMESPACE
class LinearPredictiveCode {
public:
    explicit LinearPredictiveCode(std::size_t order) :
        m_xcorr(512),
        m_lpc(order + 1),
        m_reflection(order + 1),
        m_order(order)
    {
    }

    EDSP_INLINE const std::vector<edsp::real_t>& reflection() EDSP_NOEXCEPT;
    EDSP_INLINE std::size_t order() const EDSP_NOEXCEPT;
    EDSP_INLINE double lpc_error() const EDSP_NOEXCEPT;
    EDSP_INLINE void set_order(std::size_t order);

    template<class InputIterator>
    EDSP_INLINE std::tuple<double, std::vector<double>, std::vector<double>> compute(InputIterator first, InputIterator last);

    private:
        AutoCorrelation m_xcorr;
        std::vector<edsp::real_t> buffer{};
        std::vector<edsp::real_t> m_lpc{};
        std::vector<edsp::real_t> m_reflection{};
        std::vector<edsp::real_t> m_tmp{};
        std::size_t m_order{0};
        edsp::real_t m_error{0};
};

const std::vector<edsp::real_t>& LinearPredictiveCode::reflection() EDSP_NOEXCEPT {
    return m_reflection;
}

std::size_t LinearPredictiveCode::order() const EDSP_NOEXCEPT {
    return m_order;
}

double LinearPredictiveCode::lpc_error() const EDSP_NOEXCEPT {
    return m_error;
}

void LinearPredictiveCode::set_order(const std::size_t order) {
    if (order != m_order) {
        m_lpc.resize(m_order + 1);
        m_reflection.resize(m_order + 1);
        m_tmp.resize(m_order + 1);
    }
}

template<class InputIterator>
std::tuple<double, std::vector<double>, std::vector<double>> LinearPredictiveCode::compute(InputIterator first, InputIterator last) {
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

EDSP_END_NAMESPACE

#endif //EDSP_LINEARPREDICTIVECODING_H
