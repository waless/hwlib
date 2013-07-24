#include "hw/string/string.h"
#include "hw/types.h"

void hw_string_initialize(hw_string_t* state, char* buffer, hwu32 size)
{
}

void hw_string_finalize(hw_string_t* state)
{
}

char hw_string_at(const hw_string_t* state, hwu32 index)
{
}

char* hw_string_get_pointer(hw_string_t* state, hwu32 index)
{
}

const char* hw_string_get_const_pointer(const hw_string_t* state, hwu32 index)
{
}

void hw_string_clear(hw_string_t* state)
{
}

void hw_string_copy_string(hw_string_t* lhs, const hw_string_t* rhs)
{
}

void hw_string_copy_buffer(hw_string_t* lhs, const char* buffer, hwu32 size)
{
}

void hw_string_append_string(hw_string_t* state, const hw_string_t* rhs);
void hw_string_append_char(hw_string_t* state, char c);
void hw_string_append_buffer(hw_string_t* state, const char* buffer, hwu32 size);
hwbool hw_string_find_char(hwu32* char_index, const hw_string_t* state);
hwbool hw_string_find_string(hwu32* string_index, hwu32* string_size, const hw_string_t* state, const hw_string_t* string);
hwbool hw_string_find_buffer(hwu32* string_index, hwu32* string_size, const hw_string_t* state, const char* buffer, hwu32 size);
hwbool hw_string_substring_to_string(hw_string_t* out, const hw_string_t* state, hwu32 begin_index, hwu32 length);
hwbool hw_string_substring_to_buffer(char* buffer, hwu32 buffer_size, const hw_string_t* state, hwu32 begin_index, hwu32 length);
hwu32 hw_string_get_split_count(const hw_string_t* state, char separete);
hwu32 hw_string_split(hw_string_t out_array[], hwu32 out_array_count, const hw_string_t* state, char separete);
