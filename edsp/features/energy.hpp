/*
 * eDSP, A cross-platform DSP framework written in C++.
 * Copyright (C) 2018 Mohammed Boujemaoui Boulaghmoudi
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef EDSP_FEATURES_ENERGY_H
#define EDSP_FEATURES_ENERGY_H


#include <numeric>
#include "feature.hpp"
EDSP_BEGIN_NAMESPACE

/**
 * @brief Extracts the energy of a signal
 *
 * The energy of a discrete-time signal is defined as:
 *
 *  \f[
 *     e = \sum_{n = 0}^{N-1} \left| x(n) \right| ^ 2
 *  \f]
 */
class Energy : public Feature {
    EDSP_DECLARE_ALL_IMPLICITS(Energy)
public:
    Energy();
    ~Energy() EDSP_OVERRIDE;
protected:
    EDSP_INLINE void extract_implementation(_In_ const value_type *input, _In_ size_type size, _Out_ value_type *output) EDSP_OVERRIDE;
};

Energy::Energy() = default;

Energy::~Energy() = default;

void Energy::extract_implementation(_In_ const Feature::value_type *input, _In_ Feature::size_type size, _Out_ Feature::value_type *output) {
    *output = std::inner_product(input, input + size, input, static_cast<value_type >(0));
}

EDSP_END_NAMESPACE
#endif //EDSP_FEATURES_ENERGY_H
