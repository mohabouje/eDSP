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
#ifndef EDSP_LOUDNESS_H
#define EDSP_LOUDNESS_H


#include <numeric>
#include <cmath>
#include "feature.hpp"
EDSP_BEGIN_NAMESPACE

/**
 *  @brief Extracts the loudness of an audio signal
 *
 *  In acoustics, loudness is the subjective perception of sound pressure. The loudness orders the sound on
 *  a scale extending from quiet to loud. It's usually specified in dB.
 *
 *  \f[
 *     l = \left( \sum_{n = 0}^{N-1} x(n) ^ 2 \right)^{\alpha}
 *
 *  \f]
 *
 *  This class uses the Steven's  power law factor ( \$[ \alpha = 0.67 \$])  by default.
 */
class Loudness : public Feature {
public:
    /**
     * \brief Creates a loudness feature extractor object with the given \$[ \alpha \$]
     * @param alpha Exponential factor
     */
    explicit Loudness(_In_ value_type alpha);
    Loudness();
    ~Loudness() EDSP_OVERRIDE;

    /**
     * \brief Set the exponential factor \$[ \alpha \$]
     * @param factor Exponential factor \$[ \alpha \$]
     */
    EDSP_INLINE void set_alpha(_In_ value_type factor) EDSP_NOEXCEPT;

    /**
     * \brief Returns the exponential factor \$[ \alpha \$]
     * @return Exponential factor \$[ \alpha \$]
     */
    EDSP_INLINE value_type alpha() EDSP_NOEXCEPT;
private:
    EDSP_INLINE void extract_implementation(_In_ const value_type *input, _In_ size_type size, _Out_ value_type *output) EDSP_OVERRIDE;
    value_type _alpha = 0.67;
};

void Loudness::extract_implementation(_In_ const Feature::value_type *input, _In_ Feature::size_type size, _Out_ Feature::value_type *output) {
    *output = std::inner_product(input, input + size, input, static_cast<value_type>(0));
    std::pow(*output, _alpha);
}

Loudness::Loudness() = default;

Loudness::~Loudness() = default;

Loudness::Loudness(_In_ Feature::value_type _alpha) : _alpha(_alpha) {}

void Loudness::set_alpha(_In_ Feature::value_type alpha) EDSP_NOEXCEPT {
    _alpha = alpha;
}

Feature::value_type Loudness::alpha() EDSP_NOEXCEPT {
    return _alpha;
}

EDSP_END_NAMESPACE
#endif //EDSP_LOUDNESS_H
