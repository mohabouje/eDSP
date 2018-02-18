//
// Created by mohabouje on 18/02/18.
//

#include "blocks/echo.h"
using namespace edsp::blocks;

Echo::Echo(std::size_t maximum_delay) :
        delay_(maximum_delay/3, maximum_delay)
{
    reset();
}
