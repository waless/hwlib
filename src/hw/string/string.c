#include "hw/string/string.h"
#include <stddef.h>
#include "hw/types.h"

void hw_string_initialize(hw_string_t* state, char* buffer, hwu32 size)
{
    state->buffer   = buffer;
    state->capacity = size;
    state->length   = 0;

    if(buffer != NULL && size > 0) {
        state->length = strlen(buffer);
    }
}

void hw_string_finalize(hw_string_t* state)
{
    state->buffer   = NULL;
    state->capacity = 0;
    state->length   = 0;
}

char hw_string_at(const hw_string_t* state, hwu32 index)
{
    return (index < state->length) ? state->buffer[index] : "\0";
}

char* hw_string_get_pointer(hw_string_t* state, hwu32 index)
{
    return (index < state->length) ? state->buffer + index : NULL;
}

const char* hw_string_get_const_pointer(const hw_string_t* state, hwu32 index)
{
    return (index < state->length) ? state->buffer + index : NULL;
}

void hw_string_clear(hw_string_t* state)
{
    if(state->buffer != NULL && state->capacity > 0) {
        memset(state->buffer, 0, sizeof(char) * state->capacity);
    }
}

void hw_string_copy_string(hw_string_t* lhs, const hw_string_t* rhs)
{
    hw_string_copy_buffer(lhs, rhs->buffer, rhs->length);
}

void hw_string_copy_buffer(hw_string_t* lhs, const char* buffer, hwu32 size)
{
    if(size < lhs->capacity) {
        memcpy(lhs->buffer, rhs->buffer, size);
        lhs->buffer[size] = '\0';
        lhs->length = size;
    }
    else {
        memcpy(lhs->buffer, buffer, lhs->capacity);
        lhs->buffer[lhs->capacity - 1] = '\0';
        lhs->length = lhs->capacity - 1;
    }
}

void hw_string_append_string(hw_string_t* state, const hw_string_t* rhs)
{
    hw_string_append_buffer(state, rhs->buffer, rhs->length);
}

void hw_string_append_char(hw_string_t* state, char c)
{
    if(state->length < (state->capacity - 1)) {
        state->buffer[state->length++] = c;
    }
}

void hw_string_append_buffer(hw_string_t* state, const char* buffer, hwu32 size)
{
    hwu32 capacity  = state->capacity - state->length;
    hwu32 copy_size = size;

    if(buffer != NULL) {
        if(capacity < (size + 1)) {
            copy_size = capacity;
        }

        if(copy_size > 0) {
            memcpy(state->buffer, buffer, copy_size);
        }
    }
}

hwbool hw_string_find_char(hwu32* char_index, const hw_string_t* state, char c)
{
    const char* p = strchr(state->buffer, c);
    if(p != NULL) {
        if(char_index != NULL) {
            *char_index = (hwu32)(p - state->buffer);
        }

        return HW_TRUE;
    }
    else {
        if(char_index != NULL) {
            *char_index = 0;
        }

        return HW_FALSE;
    }
}

hwbool hw_string_find_string(hwu32* string_index, hwu32* string_size, const hw_string_t* state, const hw_string_t* string)
{
    const char* p = strstr(state->buffer, string-buffer);
    if(p != NULL) {
        if(string_idex) {
        }
    }
    else {
    }
}

hwbool hw_string_find_buffer(hwu32* string_index, hwu32* string_size, const hw_string_t* state, const char* buffer, hwu32 size)
{
}

hwbool hw_string_substring_to_string(hw_string_t* out, const hw_string_t* state, hwu32 begin_index, hwu32 length)
{
}

hwbool hw_string_substring_to_buffer(char* buffer, hwu32 buffer_size, const hw_string_t* state, hwu32 begin_index, hwu32 length)
{
}

hwu32 hw_string_get_split_count(const hw_string_t* state, char separete)
{
}

hwu32 hw_string_split(hw_string_t out_array[], hwu32 out_array_count, const hw_string_t* state, char separete)
{
}

