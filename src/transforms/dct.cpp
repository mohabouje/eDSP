//
// Created by Mohammed Boujemaoui on 16/10/2017.
//

#include "dct.h"
#include "math/container.h"
#include <assert.h>

using namespace eDSP::transforms;


template<typename T>
DCT<T>::~DCT() {
    fftw_destroy_plan(fftwPlan);
    AlgorithmTemplate::~AlgorithmTemplate();
}

template <typename T>
DCT<T>::DCT(size_t size, DCT_Type t) : AlgorithmTemplate(true, Error()), t(t) {
    setSize(size);
}

template <typename T>
void DCT<T>::setType(DCT_Type t) {
    DCT::t = t;
    const fftw_r2r_kind_do_not_use_me format = [&]() {
        switch(DCT::t) {
            case Type_I: return FFTW_REDFT00;
            case Type_II: return FFTW_REDFT10;
            case Type_III: return FFTW_REDFT01;
            case Type_IV: return FFTW_REDFT11;
            default: return FFTW_REDFT00;
        }
    }();

    fftwPlan = fftw_plan_r2r_1d(static_cast<int>(input.size()),
                                &input[0],
                                &output[0],
                                format,
                                FFTW_MEASURE);
}


template <typename T>
void DCT<T>::setSize(size_t size) {
    input.resize(size);
    output.resize(size);
    setType(t);
    Math::Container::set(input, static_cast<T>(0));
    Math::Container::set(output, static_cast<T>(0));
}

template<typename T>
const std::vector<T> &DCT<T>::compute(const std::vector<T> &data) {
    assert(data.size() <= input.size());
    std::copy(data.begin(), data.end(), input.begin());
    fftw_execute(fftwPlan);
    return output;
}

EDSP_DCL_TEMPLATE(eDSP::transforms::DCT, double);
