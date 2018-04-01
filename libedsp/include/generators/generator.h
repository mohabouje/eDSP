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
#ifndef EDSP_GENERATOR_H
#define EDSP_GENERATOR_H


#include "config.h"
EDSP_BEGIN_NAMESPACE
    class Generator {
    public:
        using value_type = double;
        Generator();
        explicit Generator(value_type amplitude);
        virtual ~Generator();

        EDSP_INLINE value_type amplitude() const EDSP_NOEXCEPT;
        void set_amplitude(value_type amplitude) EDSP_NOEXCEPT;

    private:
        value_type amplitude_{1};
    };

    Generator::Generator() = default;
    Generator::~Generator() = default;
    Generator::Generator(Generator::value_type amplitude) : amplitude_(amplitude) {

    }

    Generator::value_type Generator::amplitude() const EDSP_NOEXCEPT {
        return amplitude_;
    }

    void Generator::set_amplitude(Generator::value_type amplitude) EDSP_NOEXCEPT {
        amplitude_ = amplitude;
    }

EDSP_END_NAMESPACE

#endif //EDSP_GENERATOR_H
