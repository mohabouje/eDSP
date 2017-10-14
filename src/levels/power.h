//
// Created by Mohammed Boujemaoui on 13/10/2017.
//

#ifndef EDSP_POWER_H
#define EDSP_POWER_H

#include "base/algoritmtemplate.h"

EDSP_BEGING_NAMESPACE
namespace levels {
    template<typename T>
    class Power : public AlgorithmTemplate {
    public:
        Power() : AlgorithmTemplate(true, Error()) { }
        ~Power() override = default;
        inline T compute(const std::vector<T>& data) const;
    };


}
EDSP_END_NAMESPACE
#endif //EDSP_POWER_H
