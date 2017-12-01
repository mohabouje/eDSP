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

#if defined(_MSC_VER)
    //  Microsoft
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#else
    //  do nothing and hope for the best?
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif


#define EDSP_EXPORT EXPORT

#define EDSP_DISABLE_COPY(Class) \
    Class(const Class &) = delete; \
    Class &operator=(const Class &) = delete;

#define EDSP_DISABLE_DEFAULT(Class) \
    Class() = delete;

#define EDSP_DCL_TEMPLATE(X, Type) \
    template class X<Type>;



#define USE_FFTWD 1


#endif //EDSP_EDSP_H
