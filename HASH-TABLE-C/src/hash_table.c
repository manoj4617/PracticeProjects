#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "hash_table.h"
#include "prime.h"
#include "ht_resize.h"

#define HT_PRIME_1 151
#define HT_PRIME_2 161


/*
It calls the resizable hash creation function
*/
h_hash_table* ht_new(){
    return ht_resizeable(HT_INITIAL_BASE_SIZE);
}


static h_item* ht_new_item(
    const char* key,
    const char* value
)
{
    h_item* new_item = malloc(sizeof(h_item));
    new_item->value = strdup(value);
    new_item->key = strdup(key);

    return new_item;
}

/*
Deleting the items from the hash table
*/
static void ht_delete_item(h_item* item){
    free(item->key);
    free(item->value);
    free(item);
}

void ht_delete_hash_table(h_hash_table* ht){
    for(int i = 0; i < ht->size; ++i){
        h_item* itm = ht->items[i];
        if(itm != NULL){
            ht_delete_item(itm);
        }
    }
    free(ht->items);
    free(ht);
}

/*
Hash function
For any given string the below function returns an int value
*/

static int ht_hash(
    const char* s,
    const int a,
    const int m
)
{
    long hash = 0;
    const int len = strlen(s);

    for(int i = 0; i < len; ++i){
        hash += (long)(pow(a,len-(i+1)) * s[i]);
        hash %= m;
    }
    
    return (int)hash;
}

/*
Handling collision with open addressing with double hashing
*/
static int ht_get_hash(
    const char* s,
    const int num_buckets,
    const int attempts
)
{
    const int hash_a = ht_hash(s,HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s,HT_PRIME_2, num_buckets);

    return (hash_a + (attempts * (hash_b + 1))) % num_buckets;
}

/*
Inserting value into the hash
*/
void ht_insert(
    h_hash_table* ht,
    const char* key,
    const char* value
)
{
    const int load = ht->count * 100 / ht->size;
    if(load > 70){
        ht_resize_up(ht);
    }

    h_item* item = ht_new_item(key,value);
    int index = ht_get_hash(item->key, ht->size,0);

    h_item* current = ht->items[index];
    int i = 1;
    while(current != NULL && current != &HT_DELETED_ITEM){

        if(strcmp(current->key, key) == 0){
            ht_delete_item(current);
            ht->items[index] = item;
            return;
        }

        index = ht_get_hash(item->key, ht->size, i);
        current = ht->items[index];
        i++;
    }

    ht->items[index] = item;
    ht->count++;
}

/*
Searching
*/

char* ht_search(
    h_hash_table* ht, 
    const char* key)
{
    int index = ht_get_hash(key, ht->size, 0);
    h_item* item = ht->items[index];
    int i = 0;

    while(item != NULL){
        if(item != &HT_DELETED_ITEM){
            if(strcmp(item->key, key) == 0){
                return item->key;
            }
        }
        index = ht_get_hash(key, ht->size,i);
        item = ht->items[index];
        i++;
    }

    return NULL;
}


void ht_delete(
    h_hash_table* ht,
    const char* key
)
{
    const int load = ht->count * 100 / ht->size;
    if(load < 10){
        ht_resize_down(ht);
    }

    int index = ht_get_hash(key, ht->size, 0);
    h_item* item = ht->items[index];

    int i = 1;
    while(item != NULL){
        if(item != &HT_DELETED_ITEM){
            if(strcmp(item->key, key) == 0){
                ht_delete_item(item);
                ht->items[index] = &HT_DELETED_ITEM;
            }
        }
        index = ht_get_hash(key, ht->size, i);
        item = ht->items[index];
        i++;
    }
    ht->count--;
}

