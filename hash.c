/* Code copy-pasted from 
   http://stackoverflow.com/questions/1234514/very-simple-map-implemention-in-c-for-caching-purpose 
*/

#include "hash.h"

#include <string.h>
#include <stdlib.h>

void *hash_get(struct StrHashTable *table, const char *key)
{
    unsigned int bucket = table->hash(key)%NR_BUCKETS;
    struct StrHashNode *node;
    node = table->buckets[bucket];
    while(node) {
        if(table->cmp(key,node->key) == 0)
            return node->value;
        node = node->next;
    }
    return NULL;
}

void *hash_insert(struct StrHashTable *table,char *key,void *value)
{
    unsigned int bucket = table->hash(key)%NR_BUCKETS;
    struct StrHashNode **tmp;
    struct StrHashNode *node ;
    void *old_value = NULL;

    tmp = &table->buckets[bucket];
    while(*tmp) {
        if(table->cmp(key,(*tmp)->key) == 0)
            break;
        tmp = &(*tmp)->next;
    }
    if(*tmp) {
        if(table->free_key != NULL)
            table->free_key((*tmp)->key);
        if(table->free_value != NULL)
            table->free_value((*tmp)->value);
        node = *tmp;
	// Return the old value, to let the caller free it if needed
        old_value = node->value;
    } else {
        node = malloc(sizeof *node);
        if(node == NULL)
            return value;
        node->next = NULL;
        *tmp = node;
    }
    node->key = key;
    node->value = value;

    return old_value;
}

unsigned int hash_strhash(const char *str)
{
    unsigned int hash = 0;
    for(; *str; str++)
        hash = 31*hash + *str;
    return hash;
}

#ifdef IS_MAIN

#include <stdio.h>
int main(int argc,char *argv[])
{
    struct StrHashTable tbl = {{0},NULL,NULL,hash_strhash,strcmp};

    hash_insert(&tbl,"Test","TestValue");
    hash_insert(&tbl,"Test2","TestValue2");
    puts(hash_get(&tbl,"Test"));
    hash_insert(&tbl,"Test","TestValueReplaced");
    puts(hash_get(&tbl,"Test"));

    return 0;
}
#endif // IS_MAIN
