//
// Created by Mohammed Boujemaoui on 08/10/2017.
//

#ifndef EDSP_VERSION_H
#define EDSP_VERSION_H

#include "base/types.h
EDSP_BEGING_NAMESPACE
    constexpr int VersionMajor           = EDSP_VERSION_MAJOR;
    constexpr int VersionMinor           = EDSP_VERSION_MINOR;
    constexpr int VersionBuild           = EDSP_VERSION_BUILD;

    inline static constexpr String version() {
        return  std::to_string(VersionMajor)
                + "."
                + std::to_string(VersionMinor)
                + "."
                + std::to_string(VersionBuild)
                + EDSP_VERSION_LABEL;
    }

EDSP_END_NAMESPCE


#endif //EDSP_VERSION_H
