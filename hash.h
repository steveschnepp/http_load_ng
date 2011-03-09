/* Code edited from 
   http://stackoverflow.com/questions/1234514/very-simple-map-implemention-in-c-for-caching-purpose 
*/
#ifndef __HASH_H__
#define __HASH_H__

#define NR_BUCKETS 1024

struct StrHashNode {
    char *key;
    void *value;
    struct StrHashNode *next;
};

struct StrHashTable {
    struct StrHashNode *buckets[NR_BUCKETS];
    void (*free_key)(char *);
    void (*free_value)(void*);
    unsigned int (*hash)(const char *key);
    int (*cmp)(const char *first, const char *second);
};

void *hash_get(struct StrHashTable *table, const char *key);
void *hash_insert(struct StrHashTable *table, char *key, void *value);

unsigned int hash_strhash(const char *str);

#endif // __HASH_H__
