#include "map.h"

#include <stdio.h>

typedef map(int, int) T;

int X;

struct W {
	typeof(X) x;
};

unsigned int int_hash(int i) { return i; }
int int_eq(int a, int b) {return a == b; }

int main() {
	T x = makem(T, 0, int_hash, int_eq);
	setm(x, 1, 1);
	printf("%d\n", *getm(x, 1));
	int z = *getm(x, 1);

	emptym(x);

	return z;
}
