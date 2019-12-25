#include "slice.h"
#include <stdio.h>

typedef array(int) T;

int main() {

    T x = makea(T, 0);
	append(x, 10);
	printf("%d\n", idx(x, 0));

	T y = makea(T, 10);
	copya(x, y);

	printf("%d\n", idx(x, 0));
	printf("%d\n", idx(x, 0));
	for rangea(i, y) {
		idx(y, i) = i;
	}

	for rangea(i, y) {
		printf("%d\n", idx(y, i));
	}

	emptya(x);
	emptya(y);

    return 0;
}
