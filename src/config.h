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
#define EDSP_END_NAMESPCE      }

#define UNUSED(X)     (void*)X

#define ENABLE_IF_ARITHMETIC(T)     typename T2 = typename std::enable_if<std::is_arithmetic<T>::value>::type
#define TEMPLATE_CONTAINER(T)       template <typename T> class Container

#endif //EDSP_EDSP_H
