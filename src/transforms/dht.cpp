//
// Created by Mohammed Boujemaoui on 16/10/2017.
//

#include "dht.h"
#include "math/container.h"
#include <assert.h>

using namespace eDSP::transforms;


template<typename T>
DHT<T>::~DHT() {
    fftw_destroy_plan(fftwPlan);
}

template <typename T>
DHT<T>::DHT(size_t size) : AlgorithmTemplate(true, Error()) {
    setSize(size);
}

template <typename T>
void DHT<T>::setSize(size_t size) {
    input.resize(size);
    output.resize(size);
    fftwPlan = fftw_plan_r2r_1d(size,
                                &input[0],
                                &output[0],
                                FFTW_DHT,
                                FFTW_MEASURE);
    Math::Container::set(input, std::complex<T>(0,0));
    Math::Container::set(output, std::complex<T>(0,0));
}

template <typename T>
const std::vector<T> &DHT<T>::compute(const std::vector<T> &data) {
    assert(data.size() <= input.size());
    std::copy(data.begin(), data.end(), input.begin());
    fftw_execute(fftwPlan);
    return output;
}

