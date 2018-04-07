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

#ifndef EDSP_WINDOW_BATHANNWIN_H
#define EDSP_WINDOW_BATHANNWIN_H

#include "base/constants.h"
#include "window.hpp"
#include <cmath>

EDSP_BEGIN_NAMESPACE
/**
 * @brief Bartlett-Hann %window implementation.
 *
 * See also: Bartlett and Hann.
 *
 */
class BartHann : Window {
public:
  /**
   * @brief Creates and computes a Blackman %window with the given size.
   * @param size The number of elements to initially create.
   */
  explicit BartHann(_In_ size_type size);
  ~BartHann() EDSP_OVERRIDE;

  EDSP_INLINE void initialize() EDSP_OVERRIDE;
};

BartHann::BartHann(_In_ Window::size_type size) : Window(size) {}

BartHann::~BartHann() {

}

void BartHann::initialize() {
  for (size_type i = 0, sz = size(); i < sz; ++i) {
    data_[i] =
        0.62 - 0.48 * std::abs(i / (sz - 1) - 0.5) +
        0.38 * std::cos(2 * constants<value_type>::pi * (i / (sz - 1) - 0.5));
  }
}


EDSP_END_NAMESPACE
#endif // EDSP_WINDOW_BATHANNWIN_H
