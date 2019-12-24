#ifndef CUTILS_MAP
#define CUTILS_MAP

#include "slice.h"

#define kv(k, v) struct { \
	int tomb; \
	int hash; \
	k key; \
	v val; \
}

#define NUM_BUCKETS 8

#define map(k, v) struct { \
	kv(k, v) _kv; \
	array(kv(k, v)) buckets[NUM_BUCKETS]; \
	int (*hash)(k); \
	int (*eq)(k, k); \
}

#define get(m, _key) ((typeof(m._kv.val) *) ({ \
	size_t b = m.hash(_key) % NUM_BUCKETS; \
	typeof(m._kv.val) * ret = NULL; \
	for (size_t i = 0; i < len(m.buckets[b]); i++) { \
		if (m.hash(_key) == m.hash(idx(m.buckets[b], i).key) && \
			m.eq(_key, idx(m.buckets[b], i).key)) { \
			ret = &idx(m.buckets[b], i).val; \
			break; \
		} \
	} \
	ret;\
}))

#endif
