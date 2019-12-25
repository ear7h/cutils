#ifndef CUTILS_MAP
#define CUTILS_MAP

#include "array.h"
#include <stdlib.h>
#include <string.h>

#define kv(k, v) struct { \
	int tomb; \
	int hash; \
	k key; \
	v val; \
}

#define NUM_BUCKETS 8

#define MAP_FREE_KEY 1
#define MAP_FREE_VAL 2
#define MAP_FREE_KEYVAL 3

#define map(k, v) struct { \
	array(struct { \
		int tomb; \
		unsigned int hash; \
		k key; \
		v val; \
	}) (* buckets)[NUM_BUCKETS]; \
	char memflag; \
	unsigned int (*hash)(k); \
	int (*eq)(k, k); \
}

#define makem(t, _memflag, _hash, _eq) { \
	.buckets = (typeof(((t){0}).buckets)) calloc(1, sizeof(*((t){0}).buckets)), \
	.memflag = _memflag, \
	.hash = _hash, \
	.eq = _eq, \
}

#define emptym(_emptym_m) do { \
	typeof(_emptym_m) __emptym_m = _emptym_m; \
	for (size_t i = 0; i < NUM_BUCKETS; i++) { \
		emptya((*__emptym_m.buckets)[i]); \
	} \
\
	free(__emptym_m.buckets); \
	__emptym_m.buckets = NULL; \
} while(0)

#define typeofmk(m) typeof(idx((*m.buckets)[0], 0).key)
#define typeofmv(m) typeof(idx((*m.buckets)[0], 0).val)
#define typeofmkv(m) typeof(idx((*m.buckets)[0], 0))

#define getm(_m, _key) ({ \
	assert(_m.buckets && "must initialize map"); \
\
	typeof(_m) m = _m; \
	typeofmk(m) key = _key; /* side effects */ \
\
	unsigned int hash = m.hash(key); \
	typeof((*m.buckets)[0]) bucket = (*m.buckets)[hash % NUM_BUCKETS]; \
	typeofmv(m) * ret = NULL; \
\
	for rangea(i, bucket) { \
		typeofmkv(m) kv = idx(bucket, i); \
		if (kv.tomb && \
				hash == m.hash(kv.key) && \
				m.eq(key, kv.key)) { \
			ret = &kv.val; \
			break; \
		} \
	} \
	ret;\
})

#define delm(_m, _key) ({ \
	assert(_m.buckets && "must initialize map"); \
\
	typeof(_m) m = _m; \
	typeofmk(m) key = _key; /* side effects */ \
\
	size_t hash = m.hash(key); \
	typeof((*m.buckets)[0]) bucket = (*m.buckets)[hash % NUM_BUCKETS]; \
\
	for rangea(i, bucket) { \
		typeofmkv(m) kv = idx(bucket, i); \
\
		if (kv.tomb && \
				hash == m.hash(kv.key) && \
				m.eq(key, kv.key)) { \
\
			kv.tomb = 0; \
			kv.hash = 0; \
\
			if (m.memflag & MAP_FREE_KEY) { \
				free(kv.key); \
			} \
			if (m.memflag & MAP_FREE_VAL) { \
				free(kv.val); \
			} \
\
			memset(&kv.val, 0, sizeof(kv.val)); \
			memset(&kv.key, 0, sizeof(kv.key)); \
			break; \
		} \
	} \
})

#define setm(_m, _key, _val) ({ \
	assert(_m.buckets && "must initialize map"); \
\
	typeof(_m) m = _m; \
	typeofmk(_m) key = _key; /* side effects */ \
\
	unsigned int hash = m.hash(key); \
	typeof((*m.buckets)[0]) * bucket = &(*m.buckets)[m.hash(key) % NUM_BUCKETS]; \
	typeofmkv(m) * ret = NULL; \
\
	for rangea(i, *bucket) { \
		typeofmkv(m) kv = idx(*bucket, i); \
\
		if (kv.tomb && \
				hash == m.hash(kv.key) && \
				m.eq(key, kv.key)) { \
\
			ret = &kv; \
			break; \
		} \
	} \
\
	if (ret == NULL) { \
		for rangea(i, *bucket) { \
			typeofmkv(m) kv = idx(*bucket, i); \
			if (!kv.tomb) { \
				ret = &kv; \
				break; \
			} \
		} \
\
		if (ret == NULL) { \
			append(*bucket, (typeof(idx(*bucket, 0))) {0}); \
			ret = &idx(*bucket, len(*bucket) - 1); \
		}\
\
		ret->tomb = 1; \
		ret->hash = hash;\
	} \
	ret->key = _key; \
	ret->val = _val; \
})

#endif
