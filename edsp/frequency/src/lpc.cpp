//
// Created by mohabouje on 18/02/18.
//
#include "frequency/lpc.h"
using namespace edsp::frequency;

void LinearPredictiveCode::set_order(const std::size_t order) noexcept {
    if (order != m_order) {
        m_lpc.resize(m_order + 1);
        m_reflection.resize(m_order + 1);
        m_tmp.resize(m_order + 1);
    }
}

LinearPredictiveCode::LinearPredictiveCode(std::size_t order) :
        m_order(order),
        m_reflection(order + 1),
        m_lpc(order + 1)
{
}