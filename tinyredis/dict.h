//
// Created by ss on 2020/6/28.
//

#ifndef TINYREDIS_DICT_H
#define TINYREDIS_DICT_H
#include <stdlib.h>

typedef struct dictEntry{
    void *key;
    union {
        void *val;
        uint64_t u64;
        int64_t s64;
        double d
    } v;
    struct dictEntry *next;
} entry_t;


typedef struct dictType {
    uint64_t (*hashfunction)(const void *key);
    int (*keyCompare)(void *privateData, const void *key1,const void *key2);

} dictType_t;

struct entry_type {



};

struct dictht {
    dictEntry *table;
    unsighted long size;
    unsighted long used;
} dictht;


struct dict{
    dictType_t *type;
    void *privateData;
    dictht ht;
};


#endif //TINYREDIS_DICT_H
