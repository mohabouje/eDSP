//
// Created by Mohammed Boujemaoui on 09/12/2017.
//


#ifndef EDSP_TYPES_H
#define EDSP_TYPES_H

#include "../config.h"
#include <complex>


EDSP_BEGIN_NAMESPACE
    using ecomplex = std::complex<double>;
    struct ComplexPair : public std::pair<ecomplex, ecomplex> {

        bool is_conjugate() const {
            return (first == std::conj(second));
        }

        bool is_real() const  {
            return first.imag() == 0
                   && second.imag() == 0;
        }
    };

    using Pole = ComplexPair;
    using Zero = ComplexPair;

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

EDSP_END_NAMESPACE
#endif //EDSP_TYPES_H


