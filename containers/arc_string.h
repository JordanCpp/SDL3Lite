/**
 * Arcanum String - Simple string handling
 * Compatible with C++98 and old compilers
 */

#ifndef ARC_STRING_H
#define ARC_STRING_H

#include "../core/arcanum.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char* data;
    arc_u32 length;
    arc_u32 capacity;
} arc_string;

/* String creation and destruction */
arc_string* arc_string_create(void);
arc_string* arc_string_create_from(const char* str);
arc_string* arc_string_create_with_capacity(arc_u32 capacity);
void arc_string_destroy(arc_string* str);

/* String operations */
arc_result arc_string_assign(arc_string* str, const char* value);
arc_result arc_string_append(arc_string* str, const char* value);
arc_result arc_string_append_char(arc_string* str, char c);
arc_result arc_string_prepend(arc_string* str, const char* value);

/* String access */
const char* arc_string_c_str(const arc_string* str);
char arc_string_at(const arc_string* str, arc_u32 index);
arc_result arc_string_set_at(arc_string* str, arc_u32 index, char c);

/* String properties */
arc_u32 arc_string_length(const arc_string* str);
arc_u32 arc_string_capacity(const arc_string* str);
arc_bool arc_string_empty(const arc_string* str);

/* String manipulation */
void arc_string_clear(arc_string* str);
arc_result arc_string_reserve(arc_string* str, arc_u32 capacity);
arc_result arc_string_resize(arc_string* str, arc_u32 length, char fill);

/* String comparison */
int arc_string_compare(const arc_string* str1, const arc_string* str2);
int arc_string_compare_c(const arc_string* str, const char* cstr);
arc_bool arc_string_equals(const arc_string* str1, const arc_string* str2);
arc_bool arc_string_equals_c(const arc_string* str, const char* cstr);

/* String search */
arc_s32 arc_string_find(const arc_string* str, const char* substr);
arc_s32 arc_string_find_char(const arc_string* str, char c);
arc_s32 arc_string_rfind(const arc_string* str, const char* substr);
arc_s32 arc_string_rfind_char(const arc_string* str, char c);

/* String substring */
arc_string* arc_string_substr(const arc_string* str, arc_u32 start, arc_u32 length);
arc_result arc_string_substr_into(const arc_string* str, arc_u32 start, arc_u32 length, arc_string* dest);

/* String formatting (simple sprintf-like) */
arc_result arc_string_format(arc_string* str, const char* format, ...);
arc_result arc_string_format_append(arc_string* str, const char* format, ...);

/* Utility functions */
arc_result arc_string_to_upper(arc_string* str);
arc_result arc_string_to_lower(arc_string* str);
arc_result arc_string_trim(arc_string* str);
arc_result arc_string_trim_left(arc_string* str);
arc_result arc_string_trim_right(arc_string* str);

/* Number conversion */
arc_s32 arc_string_to_int(const arc_string* str);
double arc_string_to_double(const arc_string* str);
arc_result arc_string_from_int(arc_string* str, arc_s32 value);
arc_result arc_string_from_double(arc_string* str, double value, int precision);

/* File path utilities */
arc_string* arc_string_get_directory(const arc_string* path);
arc_string* arc_string_get_filename(const arc_string* path);
arc_string* arc_string_get_extension(const arc_string* path);
arc_result arc_string_change_extension(arc_string* path, const char* new_ext);

#ifdef __cplusplus
}
#endif

#endif /* ARC_STRING_H */