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
 * Filename: CrossCorrelation.hpp
 * Created at: 10/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_CROSSCORRELATION_HPP
#define EASYDSP_CROSSCORRELATION_HPP

#include <easy/dsp/transform/internal/fftw_impl.hpp>
#include <easy/meta/expects.hpp>
#include <easy/meta/advance.hpp>
#include <algorithm>
#include <vector>

namespace easy { namespace dsp {

    template <typename T, typename Allocator = std::allocator<std::complex<T>>>
    class CrossCorrelation {
    public:
        using size_type  = std::size_t;
        using value_type = T;

        enum class ScaleOpt { None, Biased };
        inline explicit CrossCorrelation(size_type sz, ScaleOpt opt = ScaleOpt::None);
        inline size_type size() const noexcept;

        template <typename InputIterator, typename OutputIterator>
        inline void compute(InputIterator first_x, InputIterator last_x, InputIterator first_y, OutputIterator out);

        template <typename Container>
        inline void compute(const Container& left, const Container& right, Container& output);

    private:
        std::vector<std::complex<value_type>, Allocator> fft_data_left_{};
        std::vector<std::complex<value_type>, Allocator> fft_data_right_{};
        fftw_plan<value_type> fft_{};
        fftw_plan<value_type> ifft_{};
        size_type size_{0};
        ScaleOpt scale_{ScaleOpt::None};
    };

    template <typename T, typename Allocator>
    inline CrossCorrelation<T, Allocator>::CrossCorrelation(size_type sz, ScaleOpt opt) :
        fft_data_left_(make_fft_size(sz)),
        fft_data_right_(make_fft_size(sz)),
        size_(sz),
        scale_(opt) {}

    template <typename T, typename Allocator>
    inline typename CrossCorrelation<T, Allocator>::size_type CrossCorrelation<T, Allocator>::size() const noexcept {
        return size_;
    }

    template <typename T, typename Allocator>
    template <typename Container>
    inline void CrossCorrelation<T, Allocator>::compute(const Container& left, const Container& right,
                                                        Container& output) {
        meta::expects(left.size() == size_ && right.size() == size_ && output.size() == size_, "Buffer size mismatch");
        compute(std::cbegin(left), std::cend(left), std::cbegin(right), std::begin(output));
    }

    template <typename T, typename Allocator>
    template <typename InputIterator, typename OutputIterator>
    inline void CrossCorrelation<T, Allocator>::compute(InputIterator first_x, InputIterator last_x,
                                                        InputIterator first_y, OutputIterator out) {
        static_assert(std::is_same<typename std::iterator_traits<InputIterator>::value_type, T>::value &&
                          std::is_same<typename std::iterator_traits<OutputIterator>::value_type, T>::value,
                      "Iterator does not math the value type. No implicit conversion is allowed");
        meta::expects(static_cast<size_type>(std::distance(first_x, last_x)) == size_, "Buffer size mismatch");
        fft_.dft(fftw_cast(&(*first_x)), fftw_cast(fft_data_left_.data()), size_);
        fft_.dft(fftw_cast(&(*first_y)), fftw_cast(fft_data_right_.data()), size_);

        std::transform(
            std::cbegin(fft_data_left_), std::cend(fft_data_left_), std::cbegin(fft_data_right_),
            std::begin(fft_data_right_),
            [](const std::complex<double> left, const std::complex<double> right) { return left * std::conj(right); });

        ifft_.idft(fftw_cast(fft_data_right_.data()), fftw_cast(&(*out)), size_);

        // Scale the ifft & cross correlation scale option (Biased, Unbiased or None)
        const auto factor = static_cast<value_type>(size_ * (scale_ == ScaleOpt::Biased ? size_ : 1));
        std::transform(out, meta::advance(out, size_), out, [factor](value_type val) { return val / factor; });
    }

    template <typename InputIterator, typename OutputIterator,
              typename value_type = typename std::iterator_traits<InputIterator>::value_type>
    inline void xcorr(
        InputIterator first_x, InputIterator last_x, InputIterator first_y, OutputIterator out,
        typename CrossCorrelation<value_type>::ScaleOpt scale_opt = CrossCorrelation<value_type>::ScaleOpt::None) {
        meta::expects(std::distance(first_x, last_x) > 0, "Not expecting empty input");
        CrossCorrelation<value_type> correlator(std::distance(first_x, last_x), scale_opt);
        correlator.compute(first_x, last_x, first_y, out);
    }

}} // namespace easy::dsp

#endif // EASYDSP_CROSSCORRELATION_HPP
