#ifndef CUTILS_ARRAY
#define CUTILS_ARRAY

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define array(t) struct { \
    t * p; \
    size_t l; \
	size_t c; \
}

#define idx(s, i) s.p[_idxCheck(i, s.l)]

size_t _idxCheck(size_t i, size_t l) {
    assert(i >= 0 && i < l);
    return i;
}

#define len(s) (s.l)
#define cap(s) (s.c)

#define makea(t, n) { \
    .p = (t *) calloc(n, sizeof(t)), \
    .l = n, \
	.c = n, \
}

#define dela(s) do { \
	free(s.p); \
	s.p = NULL; \
	s.l = 0; \
	s.c = 0; \
} while(0)

#define copya(s1, s2) do { \
	if (0) { s1.p = s2.p; } /* "type check" */ \
	assert(sizeof(s1.p[0]) == sizeof(s2.p[0])); /* at least don't overflow */ \
	size_t l = s1.l < s2.l ? s1.l : s2.l; \
	memcpy(s1.p, s2.p, l * sizeof(s1.p[0])); \
} while(0)

#define append(s, el) do { \
	if (s.l + 1 == s.c) { \
		s.p = realloc(s.p, (s.c + 1) * 2 * sizeof(s.p[0])); \
		s.c = (s.c + 1) * 2; \
	} \
	s.l++; \
	idx(s, s.l - 1) = el; \
} while(0)

#endif
