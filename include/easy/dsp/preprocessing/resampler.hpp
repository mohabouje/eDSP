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
 * Filename: resampler.hpp
 * Created at: 09/06/18
 * Created by: Mohammed Boujemaoui
 */

#ifndef EASYDSP_RESAMPLER_HPP
#define EASYDSP_RESAMPLER_HPP


#include <easy/meta/meta.hpp>
#include <samplerate.h>

namespace easy { namespace dsp {

    class E_EXPORT ReSampler {
    public:
        enum class ConverterType { BestQuality = 0, MediumQuality, Fastest, ZeroOrderHold, Linear };
        E_EXPORT ReSampler(float input_sr, float output_sr, euint8 channels,
                           ConverterType type = ConverterType::BestQuality);
        E_EXPORT ~ReSampler();

        template <typename InputIterator, typename OutputIterator>
        E_EXPORT inline void apply(InputIterator first, InputIterator last, OutputIterator first_out,
                                   OutputIterator last_out);

        template <typename Container>
        E_EXPORT inline void apply(const Container& input, Container& output);

        E_EXPORT euint8 channels() const noexcept;
        E_EXPORT void set_channels(euint8 channels) noexcept;

        E_EXPORT ConverterType type() const noexcept;
        E_EXPORT void set_type(ConverterType type) noexcept;

        E_EXPORT float input_samplerate() const noexcept;
        E_EXPORT void set_input_samplerate(float input_samplerate) noexcept;

        E_EXPORT float output_samplerate() const noexcept;
        E_EXPORT void set_output_samplerate(float output_samplerate) noexcept;

    private:
        float input_samplerate_{8000};
        float output_samplerate_{8000};
        euint8 channels_{1};
        ConverterType type_{ConverterType::BestQuality};
        SRC_STATE* state_ = nullptr;
        SRC_DATA data_;

        void initialize();
        void configure(const float* input, std::size_tinput_sz, float* output, std::size_toutput_sz);
        void process();
    };

    template <typename InputIterator, typename OutputIterator>
    inline void ReSampler::apply(InputIterator first, InputIterator last, OutputIterator first_out,
                                 OutputIterator last_out) {
        const auto input_sz  = std::distance(first, last);
        const auto output_sz = std::distance(first_out, last_out);
        configure(&(*first), input_sz, &(*first_out), output_sz);
        process();
    }

    template <typename Container>
    void ReSampler::apply(const Container& input, Container& output) {
        const auto ratio = output_samplerate_ / input_samplerate_;
        output.resize(static_cast<std::size_t>(ratio * size(input) + 0.5));
        configure(data(input), size(input), data(output), size(output));
        process();
    }

    ReSampler::ReSampler(float input_sr, float output_sr, euint8 channels, ReSampler::ConverterType type) :
        input_samplerate_(input_sr),
        output_samplerate_(output_sr),
        channels_(channels),
        type_(type) {
        initialize();
    }

    ReSampler::~ReSampler() {
        if (state_ != nullptr) {
            src_delete(state_);
        }
    }

    euint8 ReSampler::channels() const noexcept {
        return channels_;
    }

    void ReSampler::set_channels(euint8 channels) noexcept {
        channels_ = channels;
        initialize();
    }

    ReSampler::ConverterType ReSampler::type() const noexcept {
        return type_;
    }

    void ReSampler::set_type(ReSampler::ConverterType type) noexcept {
        type_ = type;
        initialize();
    }

    float ReSampler::input_samplerate() const noexcept {
        return input_samplerate_;
    }

    void ReSampler::set_input_samplerate(float input_samplerate) noexcept {
        input_samplerate_ = input_samplerate;
    }

    float ReSampler::output_samplerate() const noexcept {
        return output_samplerate_;
    }

    void ReSampler::set_output_samplerate(float output_samplerate) noexcept {
        output_samplerate_ = output_samplerate;
    }

    void ReSampler::initialize() {
        if (state_ != nullptr) {
            src_delete(state_);
        }

        int error = 0;
        state_    = src_new(static_cast<std::underlying_type<ConverterType>::type>(type_), channels_, &error);
        if (meta::isnull(state_)) {
            eError() << "Error while configuring libsamplerate. Error:" << src_strerror(error);
        }
    }

    void ReSampler::configure(const float* input, std::size_tinput_sz, float* output, std::size_toutput_sz) {
        E_EXPECTS(meta::notnull(input) && meta::notnull(output));
        const auto ratio       = output_samplerate_ / input_samplerate_;
        const auto expected_sz = static_cast<std::size_t>(ratio * input_sz + 0.5);
        if (expected_sz != output_sz) {
            eError() << "Error: output size does not match. Expected: " << output_sz;
        }

        data_.data_in       = const_cast<float*>(input);
        data_.input_frames  = input_sz / channels_;
        data_.data_out      = output;
        data_.output_frames = output_sz / channels_;
        data_.src_ratio     = ratio;
    }

    void ReSampler::process() {
        if (auto error = src_process(state_, &data_) != 0) {
            eError() << "Error while executing libsamplerate. Error: " << src_strerror(error);
        }

        if (data_.output_frames_gen != data_.output_frames) {
            eWarning() << "Error while performing re-sampling process. Expected output "
                          "with size "
                       << data_.output_frames << "but only" << data_.output_frames_gen << "samples has been generated";
        }
    }


}} // namespace easy::dsp

#endif // EASYDSP_RESAMPLER_HPP
