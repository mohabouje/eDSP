//
// Created by Mohammed Boujemaoui on 10/12/2017.
//

#ifndef EDSP_ENVELOPE_DETECTOR_H
#define EDSP_ENVELOPE_DETECTOR_H

#include "config.h"
#include <cmath>

EDSP_BEGIN_NAMESPACE
    namespace blocks {

        class EnvelopeDetector {
        public:
            EnvelopeDetector(const double attack,
                             const double release,
                             const double sample_rate);

            template <class InputIterator, class OutputIterator>
            void compute(InputIterator first, InputIterator last, OutputIterator out) {
                for (; first != last; ++first, ++out) {
                    compute(*first, *out);
                }
            }

            template <typename T>
            void compute(const T input, T& out) {
                const auto actual = std::abs(input);
                if (m_envelope > actual) {
                    m_envelope *= m_gain_attack;
                    m_envelope += (1 - m_gain_attack) * actual;
                } else {
                    m_envelope *= m_gain_release;
                    m_envelope += (1 - m_gain_release) * actual;
                }
                out = m_envelope;
            }

            double samplerate() const { return m_samplerate; }
            double attack_time() const { return m_attack; }
            double release_time() const { return m_release; }

            void set_attack_time(const double value);
            void set_release_time(const double value);
            void set_samplerate(const double value);

            void reset() {
                m_envelope = 0;
            }
        private:
            double m_samplerate{0};
            double m_attack{0};
            double m_release{0};
            double m_gain_attack{0};
            double m_gain_release{0};
            double m_envelope{0};
        };
    }
EDSP_END_NAMESPACE

#endif //EDSP_ENVELOPE_DETECTOR_H
