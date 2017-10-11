//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_E_ERROR_H
#define EDSP_E_ERROR_H

#include "config.h"
#include "base/error.h"
#include "base/types.h"


EDSP_BEGING_NAMESPACE
class IErrorNotifier {
    virtual const std::string& errorDescription() const = 0;
    virtual const Error& error() const = 0;
    virtual inline int16 errorId() const = 0;
    virtual void setError(const Error& error) = 0;
    virtual bool hasError() const = 0;
};

EDSP_END_NAMESPCE

#endif //EDSP_E_ERROR_H
