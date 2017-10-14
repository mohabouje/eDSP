//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#include "fft.h"
#include "math/container.h"
#include <fftw3.h>
using namespace eDSP::transforms;


template<typename T>
class FFT<T>::Pimpl {
public:
    Pimpl() = default;
    virtual ~Pimpl() {
        fftw_destroy_plan(fftwPlan);
    }

    fftw_plan fftwPlan{nullptr};
    std::vector<std::complex<T>> input;
    std::vector<std::complex<T>> fft;
};


template <typename T>
FFT<T>::FFT() : pimpl(new Pimpl()), AlgorithmTemplate() {

}

template<typename T>
FFT<T>::~FFT() {

}


template <typename T>
FFT<T>::FFT(size_t size) : pimpl(new Pimpl()), AlgorithmTemplate(true, Error()) {
    setSize(size);
}

template<typename T>
size_t FFT<T>::size() const {
    return pimpl->input.size();
}

template <typename T>
void FFT<T>::setSize(size_t size) {
    pimpl->input.resize(size);
    pimpl->fft.resize(size);
    pimpl->fftwPlan = fftw_plan_dft_1d(size,
                                       reinterpret_cast<fftw_complex*>(&pimpl->input[0]),
                                       reinterpret_cast<fftw_complex*>(&pimpl->fft[0]), FFTW_FORWARD, FFTW_ESTIMATE);
    Math::Container::set(pimpl->input, std::complex<T>(0,0));
    Math::Container::set(pimpl->fft, std::complex<T>(0,0));
}

template<typename T>
const std::vector<std::complex<T>> &FFT<T>::compute(const std::vector<T> &data) {
    static_assert(data.size() > pimpl->input.size(), "Input size should be equal or less than fft size");

    Math::Container::set(pimpl->input, std::complex<T>(0,0));
    for (size_t i = 0, size = data.size(); i < size; i++) {
        pimpl->input[i][0] = data[i];
    }

    fftw_execute(pimpl->fftwPlan);
    return pimpl->fft;
}

template<typename T>
const std::vector<std::complex<T>> &FFT<T>::compute(const std::vector<std::complex<T>> &data) {
    static_assert(data.size() > pimpl->input.size(), "Input size should be equal or less than fft size");
    std::copy(data.begin(), data.end(), pimpl->input);
    fftw_execute(pimpl->fftwPlan);
    return pimpl->fft;
}


