//
// Created by Mohammed Boujemaoui on 11/10/2017.
//

#ifndef EDSP_ERROR_H
#define EDSP_ERROR_H

#include <utility>

#include "config.h"
#include "types.h"

EDSP_BEGING_NAMESPACE
class Error {
public:
    Error() = default;
    Error::Error(uint16 id, const std::string& description) : _id(id),  _description(description)  { }
    inline int16 id() const { return _id; }
    inline const std::string& description() const { return _description; }
    inline bool operator==(const Error &rhs) const {
        return _id == rhs._id && _description == rhs._description;
    }
    inline bool operator!=(const Error &rhs) const {
        return !(rhs == *this);
    }

private:
    int16      _id{EDSP_INVALID};
    std::string _description;
}
EDSP_END_NAMESPCE



#endif //EDSP_ERROR_H
