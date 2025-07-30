/**
 * Arcanum Vector - Simple dynamic array
 * Compatible with C++98 and old compilers
 */

#ifndef ARC_VECTOR_H
#define ARC_VECTOR_H

#include "../core/arcanum.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void* data;
    arc_u32 size;
    arc_u32 capacity;
    arc_u32 element_size;
} arc_vector;

/* Vector operations */
arc_vector* arc_vector_create(arc_u32 element_size);
void arc_vector_destroy(arc_vector* vec);

arc_result arc_vector_push(arc_vector* vec, const void* element);
arc_result arc_vector_pop(arc_vector* vec);
void* arc_vector_get(arc_vector* vec, arc_u32 index);
arc_result arc_vector_set(arc_vector* vec, arc_u32 index, const void* element);

arc_result arc_vector_reserve(arc_vector* vec, arc_u32 capacity);
arc_result arc_vector_resize(arc_vector* vec, arc_u32 size);
void arc_vector_clear(arc_vector* vec);

arc_u32 arc_vector_size(const arc_vector* vec);
arc_u32 arc_vector_capacity(const arc_vector* vec);
arc_bool arc_vector_empty(const arc_vector* vec);

/* Type-safe macros for common types */
#define ARC_VECTOR_DECLARE(type, suffix) \
    typedef struct { \
        type* data; \
        arc_u32 size; \
        arc_u32 capacity; \
    } arc_vector_##suffix; \
    \
    arc_vector_##suffix* arc_vector_##suffix##_create(void); \
    void arc_vector_##suffix##_destroy(arc_vector_##suffix* vec); \
    arc_result arc_vector_##suffix##_push(arc_vector_##suffix* vec, type value); \
    type arc_vector_##suffix##_get(arc_vector_##suffix* vec, arc_u32 index); \
    arc_result arc_vector_##suffix##_set(arc_vector_##suffix* vec, arc_u32 index, type value);

#define ARC_VECTOR_DEFINE(type, suffix) \
    arc_vector_##suffix* arc_vector_##suffix##_create(void) { \
        arc_vector_##suffix* vec = (arc_vector_##suffix*)arc_malloc(sizeof(arc_vector_##suffix)); \
        if (vec) { \
            vec->data = NULL; \
            vec->size = 0; \
            vec->capacity = 0; \
        } \
        return vec; \
    } \
    \
    void arc_vector_##suffix##_destroy(arc_vector_##suffix* vec) { \
        if (vec) { \
            arc_free(vec->data); \
            arc_free(vec); \
        } \
    } \
    \
    arc_result arc_vector_##suffix##_push(arc_vector_##suffix* vec, type value) { \
        if (!vec) return ARC_ERROR_MEMORY; \
        \
        if (vec->size >= vec->capacity) { \
            arc_u32 new_capacity = vec->capacity > 0 ? vec->capacity * 2 : 4; \
            type* new_data = (type*)arc_malloc(new_capacity * sizeof(type)); \
            if (!new_data) return ARC_ERROR_MEMORY; \
            \
            if (vec->data) { \
                for (arc_u32 i = 0; i < vec->size; i++) { \
                    new_data[i] = vec->data[i]; \
                } \
                arc_free(vec->data); \
            } \
            \
            vec->data = new_data; \
            vec->capacity = new_capacity; \
        } \
        \
        vec->data[vec->size++] = value; \
        return ARC_OK; \
    } \
    \
    type arc_vector_##suffix##_get(arc_vector_##suffix* vec, arc_u32 index) { \
        if (vec && index < vec->size) { \
            return vec->data[index]; \
        } \
        type default_val = {0}; \
        return default_val; \
    } \
    \
    arc_result arc_vector_##suffix##_set(arc_vector_##suffix* vec, arc_u32 index, type value) { \
        if (!vec || index >= vec->size) return ARC_ERROR_MEMORY; \
        vec->data[index] = value; \
        return ARC_OK; \
    }

/* Common vector types */
ARC_VECTOR_DECLARE(arc_u8, u8)
ARC_VECTOR_DECLARE(arc_u16, u16)
ARC_VECTOR_DECLARE(arc_u32, u32)
ARC_VECTOR_DECLARE(arc_s16, s16)
ARC_VECTOR_DECLARE(arc_s32, s32)
ARC_VECTOR_DECLARE(void*, ptr)

#ifdef __cplusplus
}
#endif

#endif /* ARC_VECTOR_H */