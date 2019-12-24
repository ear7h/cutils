#include "map.h"

typedef map(int, int) T;

int X;

struct W {
	typeof(X) x;
};

int main() {
	int x;
	double y = -1.0;
	struct W w = { .x = (typeof(x)) y };
	T tester;

	void * z = get(tester, 1);

	z = &w;
	return w.x;
}
