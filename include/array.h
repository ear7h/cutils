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

#define idx(_idx_s, _idx_i) (*({ \
	typeof(_idx_s) __idx_s = _idx_s; \
	typeof(_idx_i) __idx_i = _idx_i; \
	&__idx_s.p[_idxCheck(__idx_i, __idx_s.l)]; \
}))

size_t _idxCheck(size_t i, size_t l) {
    assert(i >= 0 && i < l);
    return i;
}

#define len(s) ((s).l)
#define cap(s) ((s).c)

#define makea(t, _makea_n) ({ \
	size_t __makea_n = _makea_n; \
	(t) { \
		.p = (typeof(((t){0}).p)) calloc(__makea_n, sizeof(*((t){0}).p)), \
		.l = __makea_n, \
		.c = __makea_n, \
	}; \
})

#define emptya(_emptya_s) do { \
	typeof(_emptya_s) __emptya_s = _emptya_s; \
	free(__emptya_s.p); \
	__emptya_s.p = NULL; \
	__emptya_s.l = 0; \
	__emptya_s.c = 0; \
} while(0)


// TODO(ear7h): safe temps
#define copya(s1, s2) do { \
	if (0) { s1.p = s2.p; } /* "type check" */ \
	assert(sizeof(s1.p[0]) == sizeof(s2.p[0])); /* at least don't overflow */ \
	size_t l = s1.l < s2.l ? s1.l : s2.l; \
	memcpy(s1.p, s2.p, l * sizeof(s1.p[0])); \
} while(0)

#define append(s, el) _append((s), (el))

#define _append(s, el) do { \
	if (s.l + 1 > s.c) { \
		s.p = realloc(s.p, (s.c + 1) * 2 * sizeof(s.p[0])); \
		assert(s.p); \
		s.c = (s.c + 1) * 2; \
	} \
	s.l++; \
	idx(s, s.l - 1) = el; \
} while(0)

#define rangea(i, s) (size_t i = 0; i < len((s)); i++)

#endif
