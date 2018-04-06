//
// Created by mohabouje on 18/02/18.
//
#include "blocks/fadeout.h"
using namespace edsp::blocks;

FadeOut::FadeOut(double samplerate, double duration) :
        m_samplerate(samplerate),
        m_duration(duration) {

}

void FadeOut::set_samplerate(double samplerate) {
    m_samplerate = samplerate;
    m_increment = 1.0 / samplerate;
}
