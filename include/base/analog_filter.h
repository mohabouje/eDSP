//
// Created by Mohammed Boujemaoui on 09/12/2017.
//

#ifndef EDSP_ANALOG_FILTER_H
#define EDSP_ANALOG_FILTER_H


#include "config.h"
#include "types.h"
#include <vector>
#include <assert.h>

EDSP_BEGIN_NAMESPACE

    template <typename T>
    class AnalogFilterBase {
    public:
        AnalogFilterBase() = default;
        AnalogFilterBase(AnalogFilterBase &&) noexcept = default;
        AnalogFilterBase(const AnalogFilterBase&) = default;
        AnalogFilterBase& operator=(AnalogFilterBase&& other)  = default;
        virtual ~AnalogFilterBase() = default;
        explicit AnalogFilterBase(const std::vector<PoleZeroPair<T>> &m_pairs) : m_pairs(m_pairs) {}

        const PoleZeroPair& pair_at(std::size_t index) const {
            assert(m_pairs.size() > index);
            return m_pairs[index];
        }

        const PoleZeroPair& operator[] (std::size_t index) const {
            return pair_at(index);
        }


        void insert(const std::complex<T>& pole, const std::complex<T>& zero) {
            m_pairs.emplace_back(pole, std::complex<T>(), zero, std::complex<T>());
        }

        void insert(const Pole& pole, const Zero& zero) {
            m_pairs.emplace_back(pole, zero);
        }

        void insert(const PoleZeroPair& pair) {
            m_pairs.emplace_back(std::move(pair));
        }

        void reset() {
            m_pairs.clear();
        }

    protected:
        std::vector<PoleZeroPair<T>> m_pairs{};

    };



EDSP_END_NAMESPACE


#endif //EDSP_ANALOG_FILTER_H
