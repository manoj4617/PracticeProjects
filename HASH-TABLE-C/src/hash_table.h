/*
This is the basic structure of the hash table
key and value, defined in a struct;
*/

#define HT_INITIAL_BASE_SIZE 50

static h_item HT_DELETED_ITEM = {NULL, NULL};

typedef struct {
    char* key;
    char* value;
} h_item;

/*
Meta data about the hash table,such as size and count of the elemensts, 
has to be tracked which is taken care by the below struct;
*/
typedef struct {
    int count;
    int size;
    int base_size;
    h_item** items;
}h_hash_table;


void ht_delete_hash_table(h_hash_table* ht);
void ht_insert(h_hash_table* ht, const char* key, const char* value);
char* ht_search(h_hash_table* ht, const char* key);
void ht_delete(h_hash_table* ht, const char* key);
