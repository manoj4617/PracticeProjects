#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "hash_table.h"

#define HT_PRIME_1 151
#define HT_PRIME_2 161

/*
The below function is marked static because it will
only be accessed internally by the has table
*/
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
The below function initialises a new hash table of predefined size
calloc() fills array of items with NULL
*/
h_hash_table* ht_new(){
    h_hash_table* ht = malloc(sizeof(h_hash_table));

    ht->size = 64;
    ht->count = 0;
    ht->items = calloc((size_t)ht->size,sizeof(h_item));

    return ht;
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


