


/*
This is the basic structure of the hash table
key and value, defined in a struct;
*/
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
    h_item** items;
}h_hash_table;


void ht_delete_hash_table(h_hash_table*);


