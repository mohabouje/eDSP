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

#define EDSP_INVALID -1

#define EDSP_DISABLE_COPY(Class) \
    Class(const Class &) = delete; \
    Class &operator=(const Class &) = delete;

#define EDSP_DEFAULT_CONSTRUCTOR(Class) \
    Class() = default;


#endif //EDSP_EDSP_H
