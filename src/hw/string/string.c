#include "hw/string/string.h"
#include <stddef.h>
#include <string.h>
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
    return (index < state->length) ? state->buffer[index] : '\0';
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
        memcpy(lhs->buffer, buffer, size);
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

hwbool hw_string_find_char(hwu32* out_index, const hw_string_t* state, char c)
{
    const char* p = strchr(state->buffer, c);
    if(p != NULL) {
        if(out_index != NULL) {
            *out_index = (hwu32)(p - state->buffer);
        }

        return HW_TRUE;
    }

    return HW_FALSE;
}

hwbool hw_string_find_string(hwu32* out_index, const hw_string_t* state, const hw_string_t* string)
{
    return hw_string_find_buffer(out_index, state, string->buffer, string->length);
}

hwbool hw_string_find_buffer(hwu32* out_index, const hw_string_t* state, const char* buffer, hwu32 size)
{
    if(buffer != NULL && size > 0) {
        const char* p = strstr(state->buffer, buffer);
        if(p != NULL) {
            if(out_index != NULL) {
                *out_index = (hwu32)(p - state->buffer);
            }

            return HW_TRUE;
        }
    }

    return HW_FALSE;
}

hwbool hw_string_substring_to_string(hw_string_t* out, const hw_string_t* state, hwu32 begin_index, hwu32 length)
{
    return hw_string_substring_to_buffer(out->buffer, out->capacity, state, begin_index, length);
}

hwbool hw_string_substring_to_buffer(char* buffer, hwu32 buffer_size, const hw_string_t* state, hwu32 begin_index, hwu32 length)
{
    if(length > 0) {
        if(buffer != NULL &&
           buffer_size > (length + 1) &&
           state->length < begin_index &&
           (begin_index + length) < state->length) {
            memcpy(buffer, state->buffer + begin_index, length);
            buffer[length] = '\0';

            return HW_TRUE;
        }
    }

    return HW_FALSE;
}

hwu32 hw_string_get_split_count(const hw_string_t* state, char separete)
{
    hwu32 count = 0;

    if(state->length > 0) {
        hwu32 i;

        for(i = 0; i < state->length; ++i) {
            if(state->buffer[i] == separete) {
                ++count;
            }
        }
        ++count;
    }

    return count;
}

hwu32 hw_string_split(hw_string_t out_array[], hwu32 out_array_count, const hw_string_t* state, char separete)
{
    hwu32        count = 0;
    hwu32        pos   = 0;
    hw_string_t* out   = NULL;
    hwu32        i;

    if(out_array == NULL) {
        return 0;
    }

    if(out_array_count <= 0) {
        return 0;
    }

    if(state->length <= 0) {
        return 0;
    }

    out = out_array + 0;
    for(i = 0; i < state->length; ++i) {
        if(state->buffer[i] == separete) {
            ++count;
            out = out_array + count;
            pos = 0;
        }
        else {
            out->buffer[pos++] = state->buffer[i];
        }
    }
    ++count;

    return count;
}

