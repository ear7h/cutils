cat << EOF > test.c
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
EOF

./gcc.sh -E -nostdinc "$@" | grep -v '^#' | clang-format >> test.c


