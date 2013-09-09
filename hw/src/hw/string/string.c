#include "hw/string/string.h"
#include <stddef.h>
#include <string.h>
#include "hw/types.h"
#include "hw/error.h"
#include "hw/debug/assert.h"

void hw_string_initialize(hw_string_t* state, char* buffer, hwu32 capacity)
{
    state->buffer   = buffer;
    state->capacity = capacity;
    state->length   = 0;

    if(buffer != NULL && capacity > 0) {
        hwu32 length = strnlen(buffer, capacity);

        /* 長さが容量以上の場合は未初期化のバッファとみなして
         * 長さを設定しない */
        if(length < capacity) {
            state->length = length;
        }
        else {
            memset(buffer, 0, capacity);
        }
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

hwu32 hw_string_get_length(const hw_string_t* state)
{
    return state->length;
}

void hw_string_clear(hw_string_t* state)
{
    if(state->buffer != NULL && state->capacity > 0) {
        memset(state->buffer, 0, sizeof(char) * state->capacity);
        state->length = 0;
    }
}

void hw_string_copy_string(hw_string_t* lhs, const hw_string_t* rhs)
{
    hw_string_copy_buffer(lhs, rhs->buffer, rhs->length);
}

void hw_string_copy_cstring(hw_string_t* lhs, const char* p)
{
    HW_NULL_ASSERT(p);
    hw_string_copy_buffer(lhs, p, strlen(p));
}

void hw_string_copy_buffer(hw_string_t* lhs, const char* buffer, hwu32 size)
{
    HW_NULL_ASSERT(buffer);
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

hwbool hw_string_append_char(hw_string_t* state, char c)
{
    if(state->length < (state->capacity - 1)) {
        state->buffer[state->length++] = c;
        return HW_TRUE;
    }

    return HW_FALSE;
}

hwbool hw_string_append_string(hw_string_t* state, const hw_string_t* rhs)
{
    return hw_string_append_buffer(state, rhs->buffer, rhs->length);
}

hwbool hw_string_append_cstring(hw_string_t* state, const char* p)
{
    HW_NULL_ASSERT(p);
    return hw_string_append_buffer(state, p, strlen(p));
}

hwbool hw_string_append_buffer(hw_string_t* state, const char* buffer, hwu32 size)
{
    hwu32 capacity  = state->capacity - state->length;

    if(buffer != NULL) {
        if(capacity > size) {
            memcpy(state->buffer, buffer, size);
            state->length += size;

            return hw_string_append_char(state, '\0');
        }
    }

    return HW_FALSE;
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

hwbool hw_string_find_cstring(hwu32* out_index, const hw_string_t* state, const char* p)
{
    HW_NULL_ASSERT(p);
    return hw_string_find_buffer(out_index, state, p, strlen(p));
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

hwbool hw_string_replace_ext_string(hw_string_t* state, const hw_string_t* ext)
{
    return hw_string_replace_ext_buffer(state, ext->buffer, ext->length);
}

hwbool hw_string_replace_ext_cstring(hw_string_t* state, const char* ext)
{
    HW_NULL_ASSERT(ext);
    return hw_string_replace_ext_buffer(state, ext, strlen(ext));
}

hwbool hw_string_replace_ext_buffer(hw_string_t* state, const char* ext, hwu32 size)
{
    hwu32 ext_index;
    hwu32 growed_length;

    if(ext != NULL && size > 0) {
        if(hw_string_find_char(&ext_index, state, '.')) {
            growed_length = ext_index + size;

            if(growed_length < state->capacity) {
                char* p = hw_string_get_pointer(state, ext_index);
                if(p != NULL) {
                    memcpy(p, ext, size);
                    return HW_TRUE;
                }
            }
        }
        else {
            if(hw_string_append_char(state, '.')) {
                return hw_string_append_buffer(state, ext, size);
            }
        }
    }

    return HW_FALSE;
}

