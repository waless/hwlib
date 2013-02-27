#include "hwu/debug/internal/assert_log.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>
#include "hwu/platform.h"
#include "hwu/debug/internal/debug_log.h"

#ifdef HWU_DEBUG

static const char* ASSERT_LINE_BEGIN = "/*----------------------------------------------\n";
static const char* ASSERT_LINE_END   = "----------------------------------------------*/\n";
static const char* ASSERT_MESSAGE    = "ASSERT ERROR\n\n";

static void append_message(char* out, const char* name, const char* message);

void hwu_assert_put_message(const char* exp, const char* file, const int line, const char* format, ...) 
{
    char    out[1024]         = {0};
    char    line_string[32]   = {0};
    char    user_message[256] = {0};
    va_list user_args;

    strcat(out, ASSERT_LINE_BEGIN);
    strcat(out, ASSERT_MESSAGE);
    append_message(out, "exp     :", exp);
    append_message(out, "file    :", file);

    append_message(out, "line    :", itoa(line, line_string, 8));

    va_start(user_args, format);
    vsprintf(user_message, format, user_args);
    va_end(user_args);
    append_message(out, "user    :", user_message);
    strcat(out, ASSERT_LINE_END);

    hwu_debug_print(out);
}

void append_message(char* out, const char* name, const char* message) {
    strcat(out, name);
    if(message != NULL){
        strcat(out, message);
        strcat(out, "\n");
    }
}

#endif  /* HWU_DEBUG */

