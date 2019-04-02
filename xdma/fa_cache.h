#ifndef _FA_CACHE_H_
#define _FA_CACHE_H_

/*
 * Simple fully associative cache.
 * Can't use NULL as data and
 * behavior is undefined with duplicated key.
 */

#include <linux/types.h>

#define NUM_FA_CACHE_ENTRIES 256

typedef struct cache_entry {
	u64 key;
	u8 valid;
	void *data;
} cache_entry_t;

typedef struct fa_cache {
	cache_entry_t entries[NUM_FA_CACHE_ENTRIES];
	u32 cursor;
	void (*swap_out_cb)(void *);
} fa_cache_t;

void *fa_cache_find_entry(fa_cache_t *cache, u64 key);
void fa_cache_insert_entry(fa_cache_t *cache, u64 key, void *data);
void fa_cache_delete_entry(fa_cache_t *cache, u64 key);

#endif /* _FA_CACHE_H_ */
