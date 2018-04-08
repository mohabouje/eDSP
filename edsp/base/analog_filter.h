//
// Created by Mohammed Boujemaoui on 09/12/2017.
//

#ifndef EDSP_ANALOG_FILTER_H
#define EDSP_ANALOG_FILTER_H


#include "../config.h"
#include "types.h"
#include <vector>
#include <assert.h>

EDSP_BEGIN_NAMESPACE

    class AnalogFilterBase {
    public:
        AnalogFilterBase() = default;
        virtual ~AnalogFilterBase() = default;
        explicit AnalogFilterBase(const std::vector<PoleZeroPair> &pairs) : pairs_(pairs) {}

        std::size_t size() const noexcept { return pairs_.size(); }
        const PoleZeroPair& pair_at(std::size_t index) const {
            if (pairs_.size() > index) {
                throw std::runtime_error("Index out of bounds");
            }
            return pairs_[index];
        }
        
        const PoleZeroPair& operator[] (std::size_t index) const noexcept { return pairs_[index]; }
        PoleZeroPair& operator[](std::size_t index) noexcept {  return pairs_[index]; }

        void insert(const std::complex<T>& pole, const std::complex<T>& zero) {
            pairs_.emplace_back(pole, std::complex<T>(), zero, std::complex<T>());
        }

        void insert(const Pole& pole, const Zero& zero) {
            pairs_.emplace_back(pole, zero);
        }

        void insert(const PoleZeroPair& pair) {
            pairs_.emplace_back(std::move(pair));
        }

        void reset() {
            pairs_.clear();
        }

    protected:
        std::vector<PoleZeroPair<double>> pairs_{};
    };



EDSP_END_NAMESPACE


#endif //EDSP_ANALOG_FILTER_H
