//
// Created by Mohammed Boujemaoui on 10/12/2017.
//

#ifndef EDSP_DELAY_H
#define EDSP_DELAY_H

#include "config.h"
#include "utility/vector.h"
#include <vector>
#include <assert.h>

EDSP_BEGIN_NAMESPACE
    namespace algorithm {
        class Delay {
        public:
            Delay() = default;
            Delay(std::size_t delay, std::size_t maximum_delay) :
                    delay_(delay),
                    max_delay_(maximum_delay_),
                    buffer_{std::vector<double>(maximudelay_, 0.)}
            {
            }

            template <class InputIterator, class OutputIterator>
            void compute(InputIterator first, InputIterator last, OutputIterator out) {
                for (; first != last; ++first, ++out) {
                    compute(*first, *out);
                };
            }

            template <typename T>
            void compute(const T in, T& out) {
                buffer_[input_point_++] = in * gain_;
                out = buffer_[output_point_++];
                if (input_point_ == max_delay_) input_point_ = 0;
                if (output_point_ == max_delay_) output_point_ = 0;
            }

            std::size_t delay() const noexcept { return delay_; }
            std::size_t maximum_delay() const noexcept { return max_delay_; }
            double gain() const noexcept { return gain_; }

            void set_gain(const double value) noexcept { gain_ = value; }
            void set_delay(const std::size_t value) noexcept {  delay_ = value; }
            void set_maximum_delay_(const std::size_t value) {
                if (max_delay_ != value) {
                    max_delay_ = value;
                    buffer_.resize(value);
                    reset();
                }
            }

            void reset() {
                utility::set(std::begin(buffer_), std::end(buffer_), 0);
                input_point_ = 0;
                output_point_ = 0;
            }

        private:
            double      gain_{1.};
            std::size_t delay_{0};
            std::size_t max_delay_{1};
            std::size_t input_point_{0};
            std::size_t output_point_{0};
            std::vector<double> buffer_;
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_DELAY_H
