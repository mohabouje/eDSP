//
// Created by Mohammed Boujemaoui on 22/10/2017.
//

#include "autocorrelation.h"
#include "math/math_util.h"
#include "math/container.h"

using namespace eDSP::Frequency;

template <typename T>
AutoCorrelation<T>::AutoCorrelation(size_t size) :
    AlgorithmTemplate(true, Error()),
    fft(size),
    ifft(size),
    data(std::vector<T>(size))
{
}

template <typename T>
const std::vector<T> &AutoCorrelation<T>::compute(const std::vector<T>& input) {
    std::vector<std::complex<T>> fft_data = fft.compute(input);

    std::transform(fft_data.begin(), fft_data.end(), fft_data.begin(), [](std::complex<T>& value) {
        auto tmp = static_cast<T>(std::abs(value));
        return std::complex<T>(tmp * tmp, 0);
    });

    fft_data = ifft.compute(fft_data);

    std::transform(fft_data.begin(), fft_data.end(), data.begin(), [](const std::complex<T>& value) {
        return value.real();
    });

    return data;
}

template <typename T>
AutoCorrelation<T>::~AutoCorrelation() {
    AlgorithmTemplate::~AlgorithmTemplate();
}

EDSP_DCL_TEMPLATE(eDSP::Frequency::AutoCorrelation, double);