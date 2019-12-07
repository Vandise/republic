#ifndef __REPUBLIC_COMMON__
#define __REPUBLIC_COMMON__ 1

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "util/memory.h"

#define PROJECT_MEMORY_DEBUG 1
#define PROJECT_MEMORY_DEBUG_VERBOSE 1
#define PROJECT_OUTPUT_VERBOSE 0

typedef enum {
    FALSE, TRUE,
} BOOLEAN;

#endif