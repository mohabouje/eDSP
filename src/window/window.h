//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_WINDOW_H
#define EDSP_WINDOW_H

#include "config.h"
#include "base/constants.h"
#include <vector>
#include <cmath>

EDSP_BEGING_NAMESPACE
    namespace dsp {
        namespace window {

            template<typename T>
            inline std::vector<T> hamming(size_t size) {
                std::vector<T> vec(size);
                for (size_t i = 0; i < size; i++) {
                    vec[i] = 0.53836f - 0.46164f * cos(2 * Constants<T>::pi * i / (size - 1.0f));
                }
                return vec;
            }


            template<typename T>
            inline std::vector<T> hann(size_t size) {
                std::vector<T> vec(size);
                for (size_t i = 0; i < size; i++) {
                    vec[i] = 0.5f - 0.5f * std::cos(2 * Constants<T>::pi * i / (size - 1.0f));
                }
                return vec;
            }


            template<typename T>
            inline std::vector<T> hammingz(size_t size) {
                std::vector<T> vec(size);
                for (size_t i = 0; i < size; i++) {
                    vec[i] = 0.5f - 0.5f * std::cos(2 * Constants<T>::pi * i / (size - 1.0f));
                }
                return vec;
            }


            template<typename T>
            inline std::vector<T> gaussian(size_t size) {
                std::vector<T> vec(size);
                T a, b, c = 0.5f;
                for (size_t i = 0; i < size; i++) {
                    a = (i - c * (size-1.f)) / (sqrt(c) * (size - 1.f));
                    b = -c * sqrt(a);
                    vec[i] = exp(b);
                }
                return vec;
            }


            template<typename T>
            inline std::vector<T> blackman(size_t size) {
                std::vector<T> vec(size);
                for (size_t i = 0; i < size; i++) {
                    vec[i] = 0.42f - 0.5f * std::cos(2 * Constants<T>::pi * i / (size - 1.0f)) + 0.8f * std::cos((2 * Constants<T>::pi * i) / (size - 1.0f));
                }
                return vec;
            }

            template<typename T>
            inline std::vector<T> blackmanharris(size_t size) {
                std::vector<T> vec(size);
                for (size_t i = 0; i < size; i++) {
                    vec[i] = 0.35875f
                                - 0.48829f * cos((2 * Constants<T>::pi * i) / (size - 1.0f))
                                + 0.14128f * cos((2 * (2 * Constants<T>::pi) *i) / (size - 1.0f))
                                - 0.01168f * cos((3 * (2 * Constants<T>::pi) *i) / (size - 1.0f));
                }
                return vec;
            }

            template<typename T>
            inline std::vector<T> blackmannuttall(size_t size) {
                std::vector<T> vec(size);
                for (size_t i = 0; i < size; i++) {
                    vec[i] = 0.3635819f
                                - 0.4891775f * cos((2 * Constants<T>::pi * i) / (size - 1.0f))
                                + 0.1365995f * cos((2 * (2 * Constants<T>::pi) *i) / (size - 1.0f))
                                - 0.0106411f * cos((3 * (2 * Constants<T>::pi) *i) / (size - 1.0f));
                }
                return vec;
            }

            template<typename T>
            inline std::vector<T> parzen(size_t size) {
                std::vector<T> vec(size);
                for (size_t i = 0; i < size; i++) {     
                    vec[i] = 1.0f - std::abs((2.f * i - size) / (size + 1.0f));
                }
                return vec;
            }

            template<typename T>
            inline std::vector<T> welch(size_t size) {
                std::vector<T> vec(size);
                for (size_t i = 0; i < size; i++) {
                    vec[i] = 1.0f - std::sqrt((2.f * i - size) / (size + 1.0f));
                }
                return vec;
            }

            template<typename T>
            inline std::vector<T> sine(size_t size){
            	std::vector<T> vec(size);
            	for (size_t i = 0; i < size; i++) {
            		vec[i] = std::sin(Constants<T>::pi*i/ (size - 1.0f));
            	}
            	return vec;
            }

            template<typename T>
            inline std::vector<T> boxcar(size_t size){
            	std::vector<T> vec(size, 1.);
            	return vec;
            }

        }
    }

EDSP_END_NAMESPACE

#endif //EDSP_WINDOW_H
