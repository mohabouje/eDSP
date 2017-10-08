//
// Created by Mohammed Boujemaoui on 08/10/2017.
//

#ifndef EDSP_VERSION_H
#define EDSP_VERSION_H

#include "base/types.h
E_BEGING_NAMESPACE
    constexpr int VersionMajor           = E_VERSION_MAJOR;
    constexpr int VersionMinor           = E_VERSION_MINOR;
    constexpr int VersionBuild           = E_VERSION_BUILD;

    inline static constexpr String version() {
        return  std::to_string(VersionMajor)
                + "."
                + std::to_string(VersionMinor)
                + "."
                + std::to_string(VersionBuild)
                + E_VERSION_LABEL;
    }

E_END_NAMESPCE


#endif //EDSP_VERSION_H
