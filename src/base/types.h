//
// Created by Mohammed Boujemaoui on 08/10/2017.
//

#ifndef EDSP_E_TYPES_H
#define EDSP_E_TYPES_H

#include <vector>
#include <array>
#include <string>
#include <complex>
#include <memory>
#include <type_traits>

#include "config.h"

E_BEGING_NAMESPACE

    using float32  = float;
    using float64  = double;
    using int8   = int8_t;
    using int16  = int16_t;
    using int32  = int32_t;
    using int64  = int64_t;
    using uint8   = uint8_t;
    using uint16  = uint16_t;
    using uint32  = uint32_t;
    using uint64  = uint64_t;

    using Real = float;
    template <typename T>
    constexpr bool isReal(const T&) const {
        return std::is_same<T, Real>::value;
    }

    using String = std::string;
    template <typename T>
    constexpr bool isString(const T&) const {
        return std::is_same<T, String>::value;
    }

    template <typename T>
    using Complex = std::complex<T>;

    template <typename T>
    using Vector = std::vector<T>;

    template <typename T, size_t N>
    using Array = std::array<T, N>;

    template <class T>
    using UniquePtr = std::unique_ptr<T>;

    template <class T>
    using SharedPtr = std::shared_ptr<T>;


E_END_NAMESPCE

#endif //EDSP_E_TYPES_H
