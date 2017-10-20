//
// Created by Mohammed Boujemaoui on 08/10/2017.
//

#ifndef EDSP_EDSP_H
#define EDSP_EDSP_H

#define EDSP_VERSION_MAJOR     0
#define EDSP_VERSION_MINOR     0
#define EDSP_VERSION_BUILD     0
#define EDSP_VERSION_LABEL     ""

#define EDSP_BEGING_NAMESPACE  namespace eDSP {
#define EDSP_END_NAMESPACE      }

#define EDSP_INVALID (-1)

#define EDSP_DISABLE_COPY(Class) \
    Class(const Class &) = delete; \
    Class &operator=(const Class &) = delete;

#define EDSP_DCL_TEMPLATE(X, Type) \
    template class X<Type>;



#define USE_FFTWD 1


#endif //EDSP_EDSP_H
