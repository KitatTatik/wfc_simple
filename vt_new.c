#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef enum {
    FALSE = 0,
    TRUE = 1
} Bool;

#define DICT_SIZE 512
#define MAX_WORD_SIZE 150

typedef struct { 
    char mot[MAX_WORD_SIZE];
    size_t  fois;
} diction;

int cmprfun (const void *a, const void *b) {
    int ndiff =  (((diction *)a)->fois < ((diction *)b)->fois) - 
                (((diction *)a)->fois > ((diction *)b)->fois);
    if (ndiff)
        return ndiff;
    return strcmp (((diction *)a)->mot, ((diction *)b)->mot);
}

void* add_word( diction* slovar, const char* word, size_t *plus, size_t *maxnumber);
void *alloc (void *ptr, size_t pool, size_t *numb);

int main (int argc, char** argv) {
    Bool in_word = FALSE;
    Bool is_truncated = FALSE;
    char word[MAX_WORD_SIZE];
    int  c = 0,
         count_c = 0,
         count_w = 0,
         count_l = 0;
    size_t plus = 0; 
    size_t maxnumber = DICT_SIZE;
    diction *slovar = NULL;
    in_word = FALSE;
    int i = 0;
    slovar = calloc (maxnumber, sizeof *slovar);
    do {
        if ((c = getchar()) != EOF && isalpha(c)) {
            if (i >= (MAX_WORD_SIZE - 1)) {
                if (!is_truncated) {
                    fprintf(stderr, "WARN: word buffer overflow, truncating to this: '%s'\n", word);
                    is_truncated = TRUE;
                }
            } else {
                word[i++] = tolower(c);
                word[i] = '\0';
            }
            if (!in_word) {
                  in_word = TRUE;
                  count_w++;
            } 
        } else {
            in_word = FALSE;
            is_truncated = FALSE;
            if(i) {
                slovar = add_word( slovar, word, &plus, &maxnumber );
                i = 0;
            }
        }
        if (c == '\n')
            count_l++;
        count_c++;
    } while (c != EOF);
    printf("%d %d %d\n", count_c, count_w, count_l);
    qsort ( slovar, plus, sizeof *slovar, cmprfun );  
    size_t j = 0;
    for ( j = 0; j < 20; j++ ) {
        printf( "%s\t\t  %5zu\n", slovar[j].mot, slovar[j].fois );
    }
    free(slovar);
}

void* add_word( diction* slovar, const char* word, size_t *plus, size_t *maxnumber) {
    size_t i;
    for (i = 0; i < *plus; i++) {
        if (!strcmp(slovar[i].mot, word)) {
            slovar[i].fois++;
            return slovar;
        }
    }
    if (*plus < *maxnumber) {
        strcpy(slovar[*plus].mot, word);
        slovar[*plus].fois++;
        (*plus)++;
    } else {
        slovar = alloc (slovar, sizeof *slovar, maxnumber );
        strcpy (slovar[*plus].mot, word);
        slovar[(*plus)++].fois++;
    }
    return slovar;
}

void *alloc (void *ptr, size_t pool, size_t *numb) {
    void *memptr = realloc ((char *)ptr, *numb * 2 * pool);
    if (!memptr) {
        perror ("realloc(): virtual memory exhausted.");
        exit (EXIT_FAILURE);
    }  
    memset ((char *)memptr + *numb * pool, 0, *numb * pool);
    *numb *= 2;
    return memptr;
}

