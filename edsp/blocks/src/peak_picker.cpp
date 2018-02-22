//
// Created by mohabouje on 18/02/18.
//
#include "blocks/peak_picker.h"

using namespace edsp::blocks;

PeakPicker::PeakPicker(double threshold)
        : m_threshold(threshold) {

}

bool PeakPicker::is_peak(const std::size_t index) const {
    return (onset_peek[index] > onset_peek[index - 1] &&
            onset_peek[index] > onset_peek[index + 1] &&
            onset_peek[index] > 0.);
}

void PeakPicker::reset() {
    m_biquad.reset();
    m_last_peak = 0;
}
