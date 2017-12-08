//
// Created by Mohammed Boujemaoui on 08/12/2017.
//

#ifndef EDSP_SFINAE_H
#define EDSP_SFINAE_H

#include <type_traits>
#include <complex>

template<class T>
struct is_complex : std::false_type {};
template<class T>
struct is_complex<std::complex<T>> : std::true_type {};

#endif //EDSP_SFINAE_H
