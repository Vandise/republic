#ifndef __SCANNER_WORDARRAY_MODULEH
#define __SCANNER_WORDARRAY_MODULEH 1

#include "common.h"

typedef struct WordArrayStruct {
  int count;

  struct WordStruct *root;
  struct WordStruct *current_word;

} WordArray;

typedef struct WordStruct {
  char *value;
  int position;
  struct WordStruct *next;
} Word;


WordArray* init_word_array();
Word* init_word(char *value);
void add_word(WordArray* arr, char *value);
void add_unique_word(WordArray* arr, char *value);
BOOLEAN word_exists(WordArray* arr, char *value);
void free_word_array(WordArray* arr);

#endif