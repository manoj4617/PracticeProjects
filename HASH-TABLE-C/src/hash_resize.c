#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "hash_table.h"


/*
The below function is marked static because it will
only be accessed internally by the has table
*/

static h_hash_table* ht_resizeable(const int base_size){
    h_hash_table* ht = malloc(sizeof(h_hash_table));
    ht->base_size = base_size;

    ht->size = next_prime(ht->base_size);
    ht->count = 0;
    ht->items = calloc((size_t)ht->size,sizeof(h_item*));
    return ht;
}

/*
Resizing funciton
*/
static void ht_resize(
    h_hash_table* ht,
    const int base_size
)
{
    //if the size of the hash tabel goes below the minimum just return
    if(base_size < HT_INITIAL_BASE_SIZE){
        return;
    }

    //create a new hash table of the base size
    h_hash_table* new_hash = ht_resizeable(base_size);

    //copy all the items from old hash to old one
    for(int i=0;i<ht->size;++i){
        h_item* item = ht->items[i];
        if(item != NULL && item != &HT_DELETED_ITEM){
            ht_insert(new_hash,item->key,item->value);
        }
    }

    //swapping the hash table attributes
    ht->base_size = new_hash->base_size ;
    ht->count = new_hash->count;
    
    const int temp = ht->size;
    ht->size = new_hash->size;
    new_hash->size = ht->size;

    h_item** tmp_items = ht->items;
    ht->items = new_hash->items;
    new_hash->items = tmp_items;

    //deleting the new hash table
    ht_delete_hash_table(new_hash);
}

static void ht_resize_up(h_hash_table* ht){
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}

static void ht_resize_down(h_hash_table* ht){
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}
