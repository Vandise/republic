#ifndef __SCANNER_MODULEH
#define _SCANNER_MODULEH 1

#include "common.h"
#include "word_array.h"

#define CHAR_CODE(scanner) scanner->char_table[scanner->current_char]

typedef enum {
    LETTER, UPPERCASE_LETTER, DIGIT, APOSTROPHE, UNDERSCORE, HYPHEN, SPECIAL, WORD_TERMINATOR, EOF_CODE
} CHAR_CODE;

typedef struct WordScanner {
  char word_terminator;
  char file_name[250];
  char current_char;
  char word_string[250];
  char *wordp;

  CHAR_CODE char_table[256];

  char *current_word;
  FILE *source_file;

  BOOLEAN errored;
} Scanner;

Scanner* init_scanner(char *file_name, int word_terminator);
void get_word(Scanner* scanner);
void exit_scanner(Scanner* scanner);

#endif