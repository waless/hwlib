#ifndef HW_STRING_H_
#define HW_STRING_H_

#include "hw/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hw_string_t {
    char* buffer;
    hwu32 capacity;
    hwu32 length;
} hw_string_t;

extern void hw_string_initialize(hw_string_t* state, char* buffer, hwu32 size);
extern void hw_string_finalize(hw_string_t* state);
extern char hw_string_at(const hw_string_t* state, hwu32 index);
extern char* hw_string_get_pointer(hw_string_t* state, hwu32 index);
extern const char* hw_string_get_const_pointer(const hw_string_t* state, hwu32 index);
extern void hw_string_clear(hw_string_t* state);
extern void hw_string_copy_string(hw_string_t* lhs, const hw_string_t* rhs);
extern void hw_string_copy_cstring(hw_string_t* lhs, const char* p);
extern void hw_string_copy_buffer(hw_string_t* lhs, const char* buffer, hwu32 size);
extern void hw_string_append_string(hw_string_t* state, const hw_string_t* rhs);
extern void hw_string_append_char(hw_string_t* state, char c);
extern void hw_string_append_cstring(hw_string_t* state, const char* p);
extern void hw_string_append_buffer(hw_string_t* state, const char* buffer, hwu32 size);
extern hwbool hw_string_find_char(hwu32* out_index, const hw_string_t* state, char c);
extern hwbool hw_string_find_string(hwu32* out_index, const hw_string_t* state, const hw_string_t* string);
extern hwbool hw_string_find_cstring(hwu32* out_index, const hw_string_t* state, const char* p);
extern hwbool hw_string_find_buffer(hwu32* out_index, const hw_string_t* state, const char* buffer, hwu32 size);
extern hwbool hw_string_substring_to_string(hw_string_t* out, const hw_string_t* state, hwu32 begin_index, hwu32 length);
extern hwbool hw_string_substring_to_buffer(char* buffer, hwu32 buffer_size, const hw_string_t* state, hwu32 begin_index, hwu32 length);
extern hwu32 hw_string_get_split_count(const hw_string_t* state, char separete);
extern hwu32 hw_string_split(hw_string_t out_array[], hwu32 out_array_count, const hw_string_t* state, char separete);

#ifdef __cplusplus
}
#endif

#endif

