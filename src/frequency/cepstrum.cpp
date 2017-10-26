//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#include "cepstrum.h"
#include "math/math_util.h"
#include "math/container.h"

using namespace eDSP::Math::Frequency;
template <typename T>
Cepstrum<T>::Cepstrum(size_t size) :
        AlgorithmTemplate(true, Error()),
        fft(size),
        ifft(size),
        data(std::vector<T>(size))
{
}

template <typename T>
const std::vector<T> &Cepstrum<T>::compute(const std::vector<T>& input) {
    std::vector<std::complex<T>> fft_data = fft.compute(input);

    std::transform(fft_data.begin(), fft_data.end(), fft_data.begin(), [](std::complex<T>& value) {
        return std::complex<T>( 2 * std::log(std::abs(value)), 0);
    });

    fft_data = ifft.compute(fft_data);

    std::transform(fft_data.begin(), fft_data.end(), data.begin(), [](const std::complex<T>& value) {
        return value.real();
    });

    return data;
}

template <typename T>
Cepstrum<T>::~Cepstrum() {
    AlgorithmTemplate::~AlgorithmTemplate();
}

EDSP_DCL_TEMPLATE(eDSP::Math::Frequency::Cepstrum, double);