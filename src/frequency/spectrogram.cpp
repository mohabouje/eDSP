//
// Created by Mohammed Boujemaoui on 26/10/2017.
//

#include "spectrogram.h"
#include "math/math_util.h"
#include "math/container.h"

using namespace eDSP::Math::Frequency;
template <typename T>
Spectrogram<T>::Spectrogram(size_t size) :
        AlgorithmTemplate(true, Error()),
        fft(size),
        data(std::vector<T>(size))
{
}

template <typename T>
const std::vector<T> &Spectrogram<T>::compute(const std::vector<T>& input) {
    std::vector<std::complex<T>> fft_data = fft.compute(input);
    std::transform(fft_data.begin(), fft_data.end(), data.begin(), [](const std::complex<T>& value) {
        auto tmp = static_cast<T>(std::abs(value));
        return  (tmp * tmp);
    });
    return data;
}


template <typename T>
Spectrogram<T>::~Spectrogram() {
    AlgorithmTemplate::~AlgorithmTemplate();
}

EDSP_DCL_TEMPLATE(eDSP::Math::Frequency::Spectrogram, double);