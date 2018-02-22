//
// Created by mohabouje on 18/02/18.
//

#include "blocks/envelope_detector.h"
using namespace edsp::blocks;

EnvelopeDetector::EnvelopeDetector(const double attack, const double release, const double sample_rate) :
        m_samplerate(sample_rate),
        m_attack(attack),
        m_release(release),
        m_gain_attack(std::exp(-1.0 / (sample_rate * attack))),
        m_gain_release(std::exp(-1.0 / (sample_rate * release)))
{

}

void EnvelopeDetector::set_attack_time(const double value) {
    m_attack = value;
    m_gain_attack = std::exp(-1. / (m_samplerate * m_attack));
}

void EnvelopeDetector::set_release_time(const double value) {
    m_release = value;
    m_gain_release = std::exp(-1. / (m_samplerate * m_release));
}

void EnvelopeDetector::set_samplerate(const double value) {
    m_samplerate = value;
    set_attack_time(m_attack);
    set_release_time(m_release);
}
