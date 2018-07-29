/*
 * EasyDSP, A cross-platform Digital Signal Processing library written in modern C++.
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
 * You should have received a copy of the GNU General Public License along withº
 * this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * Filename: autocorrelation.hpp
 * Created at: 10/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_AUTOCORRELATION_HPP
#define EASYDSP_AUTOCORRELATION_HPP

#include "easymeet/dsp/transform/fftw_impl.hpp"
#include <easymeet/base/base.hpp>
#include <vector>

namespace easy { namespace dsp {

    template <typename T, typename Allocator = std::allocator<std::complex<T>>>
    class AutoCorrelation {
    public:
        using size_type  = std::size_t;
        using value_type = T;

        enum class ScaleOpt { None, Biased };
        inline explicit AutoCorrelation(size_type sz, ScaleOpt opt = ScaleOpt::None);
        inline size_type size() const noexcept;

        template <typename InputIterator, typename OutputIterator>
        inline void compute(InputIterator first, InputIterator last, OutputIterator out);

        template <typename Container>
        inline void compute(const Container& input, Container& output);

    private:
        std::vector<std::complex<value_type>, Allocator> fft_data_{};
        fftw_plan<value_type> fft_{};
        fftw_plan<value_type> ifft_{};
        size_type size_{0};
        ScaleOpt scale_{ScaleOpt::None};
    };

    template <typename T, typename Allocator>
    inline AutoCorrelation<T, Allocator>::AutoCorrelation(size_type sz, ScaleOpt opt) :
        fft_data_(static_cast<size_type>(std::floor(sz / 2) + 1)),
        size_(sz),
        scale_(opt) {}

    template <typename T, typename Allocator>
    inline typename AutoCorrelation<T, Allocator>::size_type AutoCorrelation<T, Allocator>::size() const noexcept {
        return size_;
    }

    template <typename T, typename Allocator>
    template <typename Container>
    inline void AutoCorrelation<T, Allocator>::compute(const Container& input, Container& output) {
        E_EXPECTS_MSG(input.size() == size_ && output.size() == size_, "Buffer size mismatch");
        compute(std::cbegin(input), std::cend(input), std::cbegin(output));
    }

    template <typename T, typename Allocator>
    template <typename InputIterator, typename OutputIterator>
    inline void AutoCorrelation<T, Allocator>::compute(InputIterator first, InputIterator last, OutputIterator out) {
        static_assert(std::is_same<typename std::iterator_traits<InputIterator>::value_type, T>::value &&
                          std::is_same<typename std::iterator_traits<OutputIterator>::value_type, T>::value,
                      "Iterator does not math the value type. No implicit conversion is allowed");
        E_EXPECTS_MSG(std::distance(first, last) == size_, "Buffer size mismatch");
        fft_.dft(fftw_cast(&(*first)), fftw_cast(fft_data_.data()), size_);

        std::transform(std::cbegin(fft_data_), std::cend(fft_data_), std::begin(fft_data_),
                       [](std::complex<value_type> val) -> std::complex<value_type> {
                           const auto tmp = std::abs(val);
                           return {tmp * tmp, 0};
                       });

        ifft_.idft(fftw_cast(fft_data_.data()), fftw_cast(&(*out)), size_);

        const auto factor = size_ * (scale_ == ScaleOpt::Biased ? size_ : 1);
        auto last_out     = out;
        std::advance(last_out, size_);
        std::transform(out, last_out, out, [factor](value_type val) { return val / factor; });
    }
}}     // namespace easy::dsp
#endif // EASYDSP_AUTOCORRELATION_HPP
