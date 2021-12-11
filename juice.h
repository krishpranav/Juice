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