#include "fa_cache.h"

void *fa_cache_find_entry(fa_cache_t *cache, u64 key)
{
	int i;

	for (i = 0; i < NUM_FA_CACHE_ENTRIES; i++) {
		if (cache->entries[i].key == key &&
			cache->entries[i].valid == 1) {
			return cache->entries[i].data;
		}
	}

	return NULL;
}

void fa_cache_insert_entry(fa_cache_t *cache, u64 key, void *data)
{
	cache_entry_t new_entry = {.key = key, .valid = 1, .data = data};
	int i;

	for (i = 0; i < NUM_FA_CACHE_ENTRIES; i++) {
		if (cache->entries[i].valid == 0) {
			cache->entries[i] = new_entry;
			return;
		}
	}

	(*(cache->swap_out_cb))(cache->entries[cache->cursor].data);
	cache->entries[cache->cursor] = new_entry;
	cache->cursor = (cache->cursor + 1) % NUM_FA_CACHE_ENTRIES;
}

void fa_cache_delete_entry(fa_cache_t *cache, u64 key)
{
	int i;

	for (i = 0; i < NUM_FA_CACHE_ENTRIES; i++) {
		if (cache->entries[i].key == key &&
			cache->entries[i].valid == 1) {
			cache->entries[i].valid = 0;
			return;
		}
	}
}

