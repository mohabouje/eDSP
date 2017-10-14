//
// Created by Mohammed Boujemaoui on 12/10/2017.
//

#ifndef EDSP_ENERGY_H
#define EDSP_ENERGY_H


#include "base/algoritmtemplate.h"

EDSP_BEGING_NAMESPACE
    namespace levels {
        template<typename T>
        class Energy : public AlgorithmTemplate {
        public:
            Energy() : AlgorithmTemplate(true, Error()) { }
            ~Energy() override = default;
            inline T compute(const std::vector<T>& data) const;
        };
    }
EDSP_END_NAMESPACE
#endif //EDSP_ENERGY_H
