#include "modules/scanner/module.h"

static void get_character(Scanner* scanner) {
  scanner->current_char = fgetc(scanner->source_file);
}

static BOOLEAN open_source_file(Scanner *scanner) {
  scanner->source_file = fopen(scanner->file_name, "r");

  if (errno != 0) {
    scanner->errored = TRUE;
    return FALSE;
  }

  get_character(scanner);

  return TRUE;
}

static void populate_char_table(Scanner *scanner) {
  int ch;

  for (ch = 0;   ch < 256;  ++ch) scanner->char_table[ch] = SPECIAL;
  for (ch = '0'; ch <= '9'; ++ch) scanner->char_table[ch] = DIGIT;
  for (ch = 'A'; ch <= 'Z'; ++ch) scanner->char_table[ch] = UPPERCASE_LETTER;
  for (ch = 'a'; ch <= 'z'; ++ch) scanner->char_table[ch] = LETTER;
  scanner->char_table['\''] = APOSTROPHE;
  scanner->char_table['-'] = HYPHEN;
  scanner->char_table['_'] = UNDERSCORE;
  scanner->char_table[scanner->word_terminator] = WORD_TERMINATOR;
  scanner->char_table[EOF_CHAR] = EOF_CODE;
}

void skip_specials(Scanner* scanner) {
  while(scanner->current_char == ' ' || CHAR_CODE(scanner) == SPECIAL || CHAR_CODE(scanner) == WORD_TERMINATOR) {
    get_character(scanner);
  }
}

Scanner* init_scanner(char *file_name, int word_terminator) {
  errno = 0;

  Scanner* scanner = __MALLOC__(sizeof(Scanner));

  strcpy(scanner->file_name, file_name);

  scanner->word_terminator = (char)word_terminator;
  scanner->current_char = '\0';
  scanner->wordp = scanner->word_string;

  scanner->errored = FALSE;

  populate_char_table(scanner);

  if (open_source_file(scanner) == FALSE) {
    __FREE__(scanner);
    return NULL;
  }

  return scanner;
}

void get_word(Scanner* scanner) {
  skip_specials(scanner);

  scanner->wordp = scanner->word_string;

  while(
    CHAR_CODE(scanner) == LETTER ||
    CHAR_CODE(scanner) == UPPERCASE_LETTER ||
    CHAR_CODE(scanner) == UNDERSCORE ||
    CHAR_CODE(scanner) == APOSTROPHE ||
    CHAR_CODE(scanner) == HYPHEN ||
    CHAR_CODE(scanner) == DIGIT) {

    *(scanner->wordp)++ = scanner->current_char;
    get_character(scanner);

  }

  *(scanner->wordp) = '\0';
}

void exit_scanner(Scanner* scanner) {
  if (scanner->source_file != NULL) {
    fclose(scanner->source_file);
  }

  __FREE__(scanner);
}