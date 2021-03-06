#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

//max number of characters allowed for a person
#define MAX_NAME 256
//the size of the table
#define TABLE_SIZE 10

//creating a variable called "person"
//Has three different fields: a character array (string) called "name", an integer for their "age", 
//and calling typedef struct within itself, titled "next", to allow the code to "point" to another person
typedef struct person
{
    char name[MAX_NAME];
    int age;
    struct person *next;
} person;

//Initializing an array of pointers person
person * hash_table[TABLE_SIZE];

//inputs a name, hashes it, and returns a number
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

//inserts a person into a table (i.e. hash_table[]) to index them
bool hash_table_insert(person *p)
{
    if (p == NULL) return false;
    int index = hash(p->name);
    p->next = hash_table[index];
    hash_table[index] = p;
    return true;
}

//Look up a person in the table by their name
person *hash_table_lookup(char *name)
{
    int index = hash(name);
    person *tmp = hash_table[index];
    while (tmp != NULL && strcmp(tmp->name, name))
    {
        tmp = tmp->next;
    }
    return tmp;
}

//Deletes a person from the table
person *hash_table_delete(char *name)
{
    int index = hash(name);
    person *tmp = hash_table[index];
    person *prev = NULL;
    while (tmp != NULL && strcmp(tmp->name, name))
    {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL) return NULL;
    if (prev == NULL)
    {
        //deleting the head
        hash_table[index] = tmp->next;
    }
    else
    {
        prev->next = tmp->next;
    }
    return tmp;
}

void print_table()
{
    printf("Start\n");
    //cycles through the table in order to print out the correct information
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else
        {
            printf("\t%i\t", i);
            person *tmp = hash_table[i];
            while (tmp != NULL)
            {
                printf("%s - ", tmp->name);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    printf("End\n");
    return;
}

int main()
{
    //creating a bunch of "person"'s
    person jacob = {.name = "Jacob", .age = 25};
    person cameron = {.name = "Cameron", .age = 333};
    person nya = {.name = "Nya", .age = 2};
    person sam = {.name = "Sam", .age = 42};
    person dez = {.name = "Dez", .age = 75};
    person ash = {.name = "Ash", .age = 5};
    person emily = {.name = "Emily", .age = 89};
    person che = {.name = "Che", .age = 765};
    person steve = {.name = "Steve", .age = 345};

    //inserting each person into the table
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

    //to show that a name not in the table cannot be found
    tmp = hash_table_lookup("James");
    if (tmp == NULL)
    {
        printf("Name not found\n");
    }
    else
    printf("Found %s\n", tmp->name);

    //deleted Jacob from the table
    hash_table_delete("Jacob");
    //Returns "Name not found" since Jacob has been deleted
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