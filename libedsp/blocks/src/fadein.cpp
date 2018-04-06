//
// Created by mohabouje on 18/02/18.
//
#include "blocks/fadein.h"
using namespace edsp::blocks;

FadeIn::FadeIn(double samplerate, double duration) :
        m_samplerate(samplerate),
        m_duration(duration) {

}

void FadeIn::set_samplerate(double samplerate) {
    m_samplerate = samplerate;
    m_increment = 1.0 / samplerate;
}
