#! /bin/sh
find . -name "*.gcda" -print0 | xargs -0 rm
