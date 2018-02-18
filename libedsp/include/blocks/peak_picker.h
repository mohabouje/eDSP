//
// Created by Mohammed Boujemaoui on 10/12/2017.
//

#ifndef EDSP_PEAK_PICKER_H
#define EDSP_PEAK_PICKER_H

#include <vector>
#include "filters/biquad.h"
#include "math/stats.h"

EDSP_BEGIN_NAMESPACE
    namespace blocks {


        class PeakPicker {

        public:
            explicit PeakPicker(double threshold);

            template <typename T>
            bool compute(const T input) {
                // store onset in onset_keep
                // shift all elements but last, then write last
                std::rotate(std::begin(onset_keep), std::begin(onset_keep) + 1, std::end(onset_keep));
                std::copy(std::begin(onset_keep), std::end(onset_keep) - 1, std::begin(onset_proc));
                onset_keep[length - 1] = input;
                onset_proc[length - 1] = input;

                // filter onset_proc
                m_biquad.compute(std::begin(onset_proc), std::end(onset_proc), std::begin(onset_proc));

                // calculate mean and median for onset_proc
                const auto mean = math::stats::mean(std::begin(onset_proc), std::end(onset_proc));
                const auto median = math::stats::median(std::begin(onset_proc), std::end(onset_proc));

                // shift peek array
                for (std::size_t j = 0 ; j < 3 - 1; ++j) {
                    onset_peek[j] = onset_peek[j + 1];
                }

                // calculate new peek value
                onset_peek[2] =  (onset_proc[win_post] - median - mean * m_threshold);

                return is_peak(1);
            }


            double threshold() const { return m_threshold; }
            double last_peak() const { return m_last_peak; }
            void set_threshold(double threshold) { m_threshold = threshold; }
            void reset();

        protected:
            bool is_peak(const std::size_t index) const;


        private:
            static constexpr std::size_t win_post{5};
            static constexpr std::size_t win_pre{1};
            static constexpr std::size_t length = win_post + win_pre + 1;

            std::array<double, length>  onset_keep{};
            std::array<double, length>  onset_proc{};
            std::array<double, 3>       onset_peek{};
            filters::Biquad m_biquad{{1, -0.5949,0.2348}, {0.1600,0.3200,0.1600}};
            double m_threshold{0.01};
            double m_last_peak{0.};



        };
    }

EDSP_END_NAMESPACE
#endif //EDSP_PEAK_PICKER_H
