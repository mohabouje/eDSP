#!/bin/bash
folder=.
exclude_folder=./include/edsp/thirdparty
find "${folder}" -regex '.*\.\(cpp\|hpp\|cc\|cxx\|c\)' -not -path "${exclude_folder}" -prune -exec clang-format -style=file -i {} \;

