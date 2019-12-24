#include "slice.h"
#include <stdio.h>

typedef array(int) T;
#define makeT(n) makea(int, n)

typedef array(double) K;
#define makeK(n) makea(double, n)

int main() {
    T x = makeT(0);
	append(x, 10);
	printf("%d\n", idx(x, 0));

	T y = makeT(10);
	copya(x, y);

	printf("%d\n", idx(x, 0));
	printf("%d\n", idx(x, 0));

	dela(x);
	dela(y);

    return 0;
}
