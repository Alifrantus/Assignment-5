#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUCKETS 1000
#define MULTIPLIER 31
#define MAXLEN 100

struct wordrec
{
    char* word;
    unsigned long count;
    struct wordrec* next;
};

struct wordrec* walloc(const char* str)
{
    struct wordrec* p = (struct wordrec*)malloc(sizeof(struct wordrec));
    if(p != NULL)
    {
        p -> count = 0;
        p -> word = strdup(str);
        p -> next = NULL;
    }
    return p;
}

struct wordrec* table[MAXLEN];

unsigned long hashstring(const char* str)
{
    unsigned long hash = 0;
    while (*str) 
    {
        hash = hash * MULTIPLIER + *str;
        str ++;
    }
    return  hash%MAX_BUCKETS;
}

struct wordrec* lookup(const char* str, int create)
{
    unsigned long hash = hashstring(str);
    struct wordrec* wp = table[hash];
    struct wordrec* curr = NULL;
    for(curr = wp; curr != NULL; curr = curr -> next)
        if(strcmp(curr -> word, str) == 0) return curr;
    if(create)
    {
        curr = (struct wordrec*)malloc(sizeof(struct wordrec));
        curr -> word = strdup(str);
    }
}