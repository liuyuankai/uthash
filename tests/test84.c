#include "uthash.h"
#include <stdio.h>
#include <stdlib.h>  /* malloc */

typedef struct person_t {
    char *first_name;
    int id;
    UT_hash_handle hh;
} person_t;

int main(int argc, char*argv[]) {
    person_t *people=NULL, *person, *new_person, *tmp;
    const char **name;
    const char * names[] = { "bob", "jack", "gary", "ty", "bo", "phil", "art",
                      "gil", "buck", "ted", NULL };
    int id=0;

    for(name=names; *name; name++) {
        if ( (person = (person_t*)malloc(sizeof(person_t))) == NULL) exit(-1);
        person->first_name = malloc(10);
        strncpy(person->first_name, *name,10);
        person->id = id++;
        HASH_ADD_STR(people,first_name,person);
        printf("added %s (id %d)\n", person->first_name, person->id);
    }

    person=NULL;
    person_t **p=&person;

    for(name=names; *name; name++) {
        HASH_FIND_STR(people,*name,*p);
        if (person) {
            printf("found %s (id %d)\n", person->first_name, person->id);
            new_person  = malloc(sizeof(person_t));
            new_person->first_name = malloc(10);
            strncpy(new_person->first_name, person->first_name,10);
            new_person->id = person->id*10;
            HASH_REPLACE_STR(people,first_name,new_person,tmp);
            printf("replaced (%c) with %s (id %d)\n", tmp?'y':'n', new_person->first_name, new_person->id);
            if (tmp) {free(tmp->first_name); free(tmp);}
        } else {
            printf("failed to find %s\n", *name);
        }
    }

    printf("traversing... \n");
    HASH_ITER(hh, people, person, tmp) {
        printf("%s (id %d)\n", person->first_name, person->id);
        HASH_DEL(people,person);
        free(person->first_name);
        free(person);
    }
   return 0;
}
