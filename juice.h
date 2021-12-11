#pragma once

#ifndef __cplusplus
extern "C"
{
#endif
#if 0
}
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef _MSC_VER
#define __attribute__(x)
#endif

/**
 * @brief define juice version 
 * 
 */
#define JUICE_VERSION_MAJOR 1
#define JUICE_VERSION_MINOR 2
#define JUICE_VERSION_PATCH 0
#define JUICE_VERSION_STRING "1.0.0"

/**
 * @brief object + errror + program + traceback
 * 
 */
typedef struct juice juice_t;
typedef struct juice_object { uint16_t _internal; } juice_object_t;
typedef struct juice_error juice_error_t;
typedef struct juice_program juice_program_t;
typedef struct juice_traceback juice_traceback_t;

/**
 * @brief errors
 * 
 */
typedef enum juice_error_type {
    JUICE_ERROR_NONE = 0,
    JUICE_ERROR_PARSING,
    JUICE_ERROR_COMPILATION,
    JUICE_ERROR_RUNTIME,
    JUICE_ERROR_ALLOCATION,
    JUICE_ERROR_USER,
} juice_error_type_t;

/**
 * @brief object type
 * 
 */

typedef enum juice_object_type {
    JUICE_OBJECT_NONE            = 0,
    JUICE_OBJECT_ERROR           = 1 << 0,
    JUICE_OBJECT_NUMBER          = 1 << 1,
    JUICE_OBJECT_BOOL            = 1 << 2,
    JUICE_OBJECT_STRING          = 1 << 3,
    JUICE_OBJECT_NULL            = 1 << 4,
    JUICE_OBJECT_NATIVE_FUNCTION = 1 << 5,
    JUICE_OBJECT_ARRAY           = 1 << 6,
    JUICE_OBJECT_MAP             = 1 << 7,
    JUICE_OBJECT_FUNCTION        = 1 << 8,
    JUICE_OBJECT_EXTERNAL        = 1 << 9,
    JUICE_OBJECT_FREED           = 1 << 10,
    JUICE_OBJECT_ANY             = 0xffff, 
} juice_object_type_t;

typedef juice_object_t (*juice_native_fn)(juice_t *juice, void *data, int argc, juice_object_t *args);
typedef void* (*juice_malloc_fn)(void *ctx, size_t size);
typedef void (*juice_free_fn)(void *ctx, void *ptr);
typedef void (*juice_data_destroy_fn)(void* data);
typedef void* (*juice_data_copy_fn)(void* data);

typedef size_t (*juice_stdout_write_fn)(void* context, const void *data, size_t data_size);
typedef char* (*juice_read_file_fn)(void* context, const char *path);
typedef size_t (*juice_write_file_fn)(void* context, const char *path, const char *string, size_t string_size);

juice_t* juice_make(void);
juice_t* juice_make_ex(juice_malloc_fn malloc_fn, juice_free_fn free_fn, void* ctx);
void juice_destroy(juice_t *juce);
void juice_set_repl_mode(juice_t *juice, bool enabled);