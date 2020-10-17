#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define MAX_NAME 256
#define TABLE_SIZE 10
#define DELETED_NODE (person*)(0xFFFFFFFFFFFFFFFFUL)

typedef struct
{
    char name[MAX_NAME];
    int age;
} person;

person * hash_table[TABLE_SIZE];

unsigned int hash(char *name)
{
    int length = strlen(name);
    unsigned int hash_value = 0;
    for (int i = 0; i < length; i++)
    {
        hash_value += name[i];
        hash_value = (hash_value * name[i]) % TABLE_SIZE;
    }
    return hash_value;
}

bool hash_table_insert(person *p)
{
    if (p == NULL) return false;
    int index = hash(p->name);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (i + index) % TABLE_SIZE;
        if (hash_table[try] == NULL || hash_table[try] == DELETED_NODE)
        {
            hash_table[try] = p;
            return true;
        }
    }
    return false;
}

//Look up a person in the table by their name
person *hash_table_lookup(char *name)
{
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] == NULL) return false; //not here
        if (hash_table[try] == DELETED_NODE) continue;
        if (strcmp(hash_table[try]->name, name) == 0)
        {
            return hash_table[try];
        }
    }
    return NULL;
}

person *hash_table_delete(char *name)
{
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        int try = (index + i) % TABLE_SIZE;
        if (hash_table[try] == NULL) return NULL;
        if (hash_table[try] == DELETED_NODE) continue;
        if (strcmp(hash_table[try]->name, name) == 0)
        {
            person *tmp = hash_table[try];
            hash_table[try] = DELETED_NODE;
            return tmp;
        }
    }
    return NULL;
}

void print_table()
{
    printf("Start\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else if (hash_table[i] == DELETED_NODE)
        {
            printf("\t%i\t---<deleted>\n", i);
        }
        else
        {
            printf("\t%i\t%s\n", i, hash_table[i]->name);
        }
    }
    printf("End\n");
    return;
}

int main()
{
    //init_hash_table();
    //print_table();

    person jacob = {.name = "Jacob", .age = 25};
    person cameron = {.name = "Cameron", .age = 333};
    person nya = {.name = "Nya", .age = 2};
    person sam = {.name = "Sam", .age = 42};
    person dez = {.name = "Dez", .age = 75};
    person ash = {.name = "Ash", .age = 5};
    person emily = {.name = "Emily", .age = 89};
    person che = {.name = "Che", .age = 765};
    person steve = {.name = "Steve", .age = 345};

    hash_table_insert(&jacob);
    hash_table_insert(&cameron);
    hash_table_insert(&nya);
    hash_table_insert(&sam);
    hash_table_insert(&dez);
    hash_table_insert(&ash);
    hash_table_insert(&emily);
    hash_table_insert(&che);
    hash_table_insert(&steve);

    print_table();

    person *tmp = hash_table_lookup("Jacob");
    if (tmp == NULL)
    {
        printf("Name not found\n");
    }
    else
    printf("Found %s\n", tmp->name);

    tmp = hash_table_lookup("James");
    if (tmp == NULL)
    {
        printf("Name not found\n");
    }
    else
    printf("Found %s\n", tmp->name);

    hash_table_delete("Jacob");
    tmp = hash_table_lookup("Jacob");
    if (tmp == NULL)
    {
        printf("Name not found\n");
    }
    else
    printf("Found %s\n", tmp->name);

    print_table();

    return 0;
}