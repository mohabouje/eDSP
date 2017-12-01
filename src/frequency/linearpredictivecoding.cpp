//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#include "linearpredictivecoding.h"
#include "math/math.hpp"
#include "math/container.hpp"

using namespace eDSP::Frequency;
template <typename T>
LinearPredictiveCode<T>::LinearPredictiveCode(eDSP::int16 order, size_t size) :
    AlgorithmTemplate(true, Error()),
    m_order(order),
    xcorr(size),
    m_reflection(std::vector<T>(static_cast<unsigned long>(order + 1))),
    lpc(std::vector<T>(static_cast<unsigned long>(order + 1)))
{
}

template <typename T>
const std::vector<T> &LinearPredictiveCode<T>::compute(const std::vector<T>& input) {
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


template <typename T>
LinearPredictiveCode<T>::~LinearPredictiveCode() {
}



EDSP_DCL_TEMPLATE(eDSP::Frequency::LinearPredictiveCode, double);