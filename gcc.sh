#!/usr/bin/env sh

gcc -Werror \
    -Wall \
    -Wextra \
    -pedantic \
    -Wno-language-extension-token \
    -Wno-gnu-statement-expression "$@"
