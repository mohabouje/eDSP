//
// Created by Mohammed Boujemaoui on 08/12/2017.
//

#ifndef EDSP_TRANSFORM_H
#define EDSP_TRANSFORM_H

#include "config.h"
#include <fftw3.h>

EDSP_BEGIN_NAMESPACE
    class BaseTransform {
    public:
        BaseTransform() = default;
        virtual ~BaseTransform() {
            if (plan != nullptr) fftw_destroy_plan(plan);
        }
    protected:
        fftw_plan plan{nullptr};
        long size{0};
    };
#define PTR(X) &(*X)



EDSP_END_NAMESPACE


#endif //EDSP_TRANSFORM_H
