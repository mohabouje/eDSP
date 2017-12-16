//
// Created by Mohammed Boujemaoui on 10/12/2017.
//

#ifndef EDSP_ENVELOPE_DETECTOR_H
#define EDSP_ENVELOPE_DETECTOR_H

#include <cmath>
#include "config.h"

EDSP_BEGIN_NAMESPACE
    namespace algorithm {

        class EnvelopeDetector {
        public:
            EnvelopeDetector(const double attack, const double release, const double sample_rate) :
                    m_samplerate(sample_rate),
                    m_attack(attack),
                    m_release(release),
                    m_gain_attack(std::exp(-1.0 / (sample_rate * attack))),
                    m_gain_release(std::exp(-1.0 / (sample_rate * release)))
            {

            }

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

            void set_attack_time(const double value) {
                m_attack = value;
                m_gain_attack = std::exp(-1. / (m_samplerate * m_attack));
            }

            void set_release_time(const double value) {
                m_release = value;
                m_gain_release = std::exp(-1. / (m_samplerate * m_release));
            }

            void set_samplerate(const double value) {
                m_samplerate = value;
                set_attack_time(m_attack);
                set_release_time(m_release);
            }

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
