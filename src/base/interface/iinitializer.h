//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_IINITIALIZER_H
#define EDSP_IINITIALIZER_H

#include "config.h"

EDSP_BEGING_NAMESPACE
class IInitializer {
public:
    virtual bool isInitialized() const = 0;
    virtual void initialize(bool state) = 0;
};
EDSP_END_NAMESPCE

#endif //EDSP_IINITIALIZER_H
