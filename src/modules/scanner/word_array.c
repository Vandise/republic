#include "modules/scanner/word_array.h"

WordArray* init_word_array() {
  WordArray* arr = __MALLOC__(sizeof(WordArray));
  arr->count = 0;
  arr->root = NULL;
  arr->current_word = NULL;

  return arr;
}

Word* init_word(char *value) {
  Word* w = __MALLOC__(sizeof(Word));
  w->value = value;
  w->next = NULL;

  return w;
}

void add_word(WordArray* arr, char *value) {
  if (arr->root == NULL) {
    arr->root = init_word(value);
    arr->current_word = arr->root;
    arr->count += 1;
    return;
  }

  while(arr->current_word->next != NULL) {
    arr->current_word = arr->current_word->next;
  }

  arr->current_word->next = init_word(value);
  arr->current_word = arr->current_word->next;
  arr->count += 1;
}

void add_unique_word(WordArray* arr, char *value) {
  if (word_exists(arr, value)) {
    printf("\n [Warning] word \"%s\" already exists.\n", value);
    return;
  }

  add_word(arr, value);
}

BOOLEAN word_exists(WordArray* arr, char *value) {
  Word* tmp = arr->root;

  while(tmp != NULL) {
    if (strcmp(tmp->value, value) == 0) {
      return TRUE;
    }
    tmp = tmp->next;
  }

  return FALSE;
}

void free_word_array(WordArray* arr) {
  Word* tmp;
  while(arr->root != NULL) {
    tmp = arr->root;
    arr->root = arr->root->next;
    __FREE__(tmp);
  }
  __FREE__(arr);
  arr = NULL;
}