//
// Created by Mohammed Boujemaoui on 10/12/2017.
//

#ifndef EDSP_FADEOUT_H
#define EDSP_FADEOUT_H

#include "config.h"

#include "config.h"
#include <iterator>

EDSP_BEGIN_NAMESPACE
    namespace blocks {
        class FadeOut {
        public:
            FadeOut(double samplerate, double duration);

            template <class InputIterator, class OutputIterator>
            void compute(InputIterator first, InputIterator last, OutputIterator out) {
                for (; first != last; ++first, ++out) {
                    compute(*first, *out);
                };
            }

            template <typename T>
            void compute(const T in, T& out) {
                if (m_timestamp < m_duration) {
                    out = in * (1 - m_timestamp / m_duration);
                    m_timestamp += m_increment;
                } else {
                    out = in;
                }
            }

            void set_duration(double duration) { m_duration = duration; }
            void set_samplerate(double samplerate);
            void reset() { m_timestamp = 0.; }
        private:
            double m_samplerate{0.};
            double m_duration{0.};
            double m_increment{0.};
            double m_timestamp{0.};
        };
    }
EDSP_END_NAMESPACE


#endif //EDSP_FADEOUT_H
