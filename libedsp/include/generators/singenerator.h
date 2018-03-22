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
#ifndef EDSP_GENERATORS_SINGENERATOR_H
#define EDSP_GENERATORS_SINGENERATOR_H

#include "periodic_generator.h

EDSP_BEGIN_NAMESPACE
class SinGenerator : public PeriodicGenerator {
public:
    SinGenerator();
    ~SinGenerator() override;

    value_type generate() EDSP_NOEXCEPT override ;
};

EDSP_END_NAMESPACE

#endif //EDSP_SINGENERATOR_H
