//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#include "fft.h"
#include "math/container.h"
#include <assert.h>

using namespace eDSP::transforms;


template<typename T>
FFT<T>::~FFT() {
    fftw_destroy_plan(fftwPlan);
}

template <typename T>
FFT<T>::FFT(size_t size) : AlgorithmTemplate(true, Error()) {
    setSize(size);
}

template <typename T>
void FFT<T>::setSize(size_t size) {
    input.resize(size);
    output.resize(size);
    fftwPlan = fftw_plan_dft_1d(size,
                                 reinterpret_cast<fftw_complex *>(&input[0]),
                                 reinterpret_cast<fftw_complex *>(&output[0]),
                                 FFTW_FORWARD, FFTW_ESTIMATE);

    Math::Container::set(input, std::complex<T>(0,0));
    Math::Container::set(output, std::complex<T>(0,0));
}

template<typename T>
const std::vector<std::complex<T>> &FFT<T>::compute(const std::vector<T> &data) {
    assert(data.size() <= input.size());

    Math::Container::set(input, std::complex<T>(0,0));
    for (size_t i = 0, size = data.size(); i < size; i++) {
        input[i].real(data[i]);
    }

    fftw_execute(fftwPlan);
    return output;
}

template<typename T>
const std::vector<std::complex<T>> &FFT<T>::compute(const std::vector<std::complex<T>> &data) {
    assert(data.size() <= input.size());
    std::copy(data.begin(), data.end(), input.begin());
    fftw_execute(fftwPlan);
    return output;
}

EDSP_DCL_TEMPLATE(eDSP::transforms::FFT, double);
