//
// Created by Mohammed Boujemaoui on 09/12/2017.
//

#include <complex>

#ifndef EDSP_TYPES_H
#define EDSP_TYPES_H



template <typename T>
struct ComplexPair : public std::pair<std::complex<T>, std::complex<T>> {

    bool is_conjugate() const {
        return (first == std::conj(second));
    }

    bool is_real() const  {
        return first.imag() == 0
                && second.imag() == 0;
    }
};

template <typename T>
using Pole = ComplexPair<T>;

template <typename T>
using Zero = ComplexPair<T>;

template <typename T>
struct PoleZeroPair {
    PoleZeroPair() = default;
    PoleZeroPair(PoleZeroPair &&) noexcept = default;
    PoleZeroPair(const PoleZeroPair&) = default;
    PoleZeroPair& operator=(PoleZeroPair&& other)  = default;
    virtual ~PoleZeroPair() = default;
    PoleZeroPair(const Pole &m_pole, const Zero &m_zero) : m_pole(m_pole), m_zero(m_zero) {}

    void set_pole(const Pole& _pole) { m_pole == pole; }
    void set_zero(const Zero& _zero) { m_zero == zero; }
    const auto& zero() const { return m_zero; }
    const auto& pole() const { return m_pole;}

private:
    Pole m_pole{};
    Zero m_zero{};
};





#endif //EDSP_TYPES_H


