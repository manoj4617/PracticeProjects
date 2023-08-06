#include "hash_table.h"

static h_hash_table* ht_resizeable(const int base_size);
static void ht_resize(h_hash_table* ht,const int base_size);
static void ht_resize_up(h_hash_table* ht);
static void ht_resize_down(h_hash_table* ht);