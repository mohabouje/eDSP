//
// Created by mohabouje on 18/02/18.
//
#include "filters/fir.h"
#include "utility/vector.h"

using namespace edsp::filters;

void FIR::reset() noexcept {
    utility::set(std::begin(m_inputs), std::end(m_inputs), 0);
}

FIR::FIR(const std::vector<double> &m_b) :
        m_b(m_b),
        m_inputs(m_b.size(), 0) {

}
