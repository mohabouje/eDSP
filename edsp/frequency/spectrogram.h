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
#ifndef EDSP_SPECTROGRAM_H
#define EDSP_SPECTROGRAM_H

#include "dft.h"
EDSP_BEGIN_NAMESPACE
class  Spectrogram {
public:
    explicit Spectrogram(std::size_t size);
    EDSP_INLINE std::size_t size() const EDSP_NOEXCEPT;
    EDSP_INLINE void resize(std::size_t size);
    EDSP_INLINE void compute(const edsp::real_t* input, std::size_t size, edsp::real_t out);

    template <class InputIterator, class OutputIterator>
    EDSP_INLINE void compute(InputIterator first, InputIterator last, OutputIterator out);
private:
    DFT _fft;
    std::vector<std::complex<edsp::real_t>> _temporal;
};

Spectrogram::Spectrogram(std::size_t size) : _fft(size), _temporal(size) {

}

std::size_t Spectrogram::size() const EDSP_NOEXCEPT {
    return _temporal.size();
}

void Spectrogram::resize(std::size_t size) {
    _temporal.resize(size);
    _fft.resize(size);
}

template <class InputIterator, class OutputIterator>
void Spectrogram::compute(InputIterator first, InputIterator last, OutputIterator out) {
    const auto size = std::distance(first, last);
    compute(first, size, out);
}

void Spectrogram::compute(const real_t *input, std::size_t size, real_t out) {
    _fft.compute(input, size, _temporal.data());
    std::transform(std::begin(_temporal), std::end(_temporal), out, [](const auto& value) {
        const auto tmp = std::abs(value);
        return  (tmp * tmp);
    });
}

EDSP_END_NAMESPACE
#endif //EDSP_SPECTROGRAM_H
