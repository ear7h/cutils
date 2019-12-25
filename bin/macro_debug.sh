cat include/*.h include/*.c | grep '#include <' | sort | uniq > test.c

./bin/gcc.sh -E -nostdinc "$@" | grep -v '^#' | clang-format >> test.c


