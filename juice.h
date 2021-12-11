#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
#if 0
} 
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifdef _MSC_VER
#define __attribute__(x)
#endif

#define JUICE_VERSION_MAJOR 1
#define JUICE_VERSION_MINOR 1
#define JUICE_VERSION_PATCH 0

#define JUICE_VERSION_STRING "1.0.0"

typedef struct juice juice_t;
typedef struct juice_object { uint64_t _internal; } juice_object_t;
typedef struct juice_error juice_error_t;
typedef struct juice_program juice_program_t;
typedef struct juice_traceback juice_traceback_t;

typedef enum juice_error_type {
    JUICE_ERROR_NONE = 0,
    JUICE_ERROR_PARSING,
    JUICE_ERROR_COMPILATION,
    JUICE_ERROR_RUNTIME,
    JUICE_ERROR_TIMEOUT,
    JUICE_ERROR_ALLOCATION,
    JUICE_ERROR_USER, 
} juice_error_type_t;

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
typedef void*        (*juice_malloc_fn)(void *ctx, size_t size);
typedef void         (*juice_free_fn)(void *ctx, void *ptr);
typedef void         (*juice_data_destroy_fn)(void* data);
typedef void*        (*juice_data_copy_fn)(void* data);

typedef size_t (*juice_stdout_write_fn)(void* context, const void *data, size_t data_size);
typedef char*  (*juice_read_file_fn)(void* context, const char *path);
typedef size_t (*juice_write_file_fn)(void* context, const char *path, const char *string, size_t string_size);

juice_t* juice_make(void);
juice_t* juice_make_ex(juice_malloc_fn malloc_fn, juice_free_fn free_fn, void *ctx);
void   juice_destroy(juice_t *juice);

void   juice_free_allocated(juice_t *juice, void *ptr);

void juice_set_repl_mode(juice_t *juice, bool enabled);

bool juice_set_timeout(juice_t *juice, double max_execution_time_ms);

void juice_set_stdout_write_function(juice_t *juice, juice_stdout_write_fn stdout_write, void *context);
void juice_set_file_write_function(juice_t *juice, juice_write_file_fn file_write, void *context);
void juice_set_file_read_function(juice_t *juice, juice_read_file_fn file_read, void *context);

juice_program_t* juice_compile(juice_t *juice, const char *code);
juice_program_t* juice_compile_file(juice_t *juice, const char *path);
juice_object_t   juice_execute_program(juice_t *juice, const juice_program_t *program);
void           juice_program_destroy(juice_program_t *program);

juice_object_t  juice_execute(juice_t *juice, const char *code);
juice_object_t  juice_execute_file(juice_t *juice, const char *path);

juice_object_t  juice_call(juice_t *juice, const char *function_name, int argc, juice_object_t *args);
#define JUICE_CALL(juice, function_name, ...) \
    juice_call(\
        (juice),\
        (function_name),\
        sizeof((juice_object_t[]){__VA_ARGS__}) / sizeof(juice_object_t),\
        (juice_object_t[]){__VA_ARGS__})

void juice_set_runtime_error(juice_t *juice, const char *message);
void juice_set_runtime_errorf(juice_t *juice, const char *format, ...) __attribute__ ((format (printf, 2, 3)));
bool juice_has_errors(const juice_t *juice);
int  juice_errors_count(const juice_t *juice);
void juice_clear_errors(juice_t *juice);
const juice_error_t* juice_get_error(const juice_t *juice, int index);

bool juice_set_native_function(juice_t *juice, const char *name, juice_native_fn fn, void *data);
bool juice_set_global_constant(juice_t *juice, const char *name, juice_object_t obj);
juice_object_t juice_get_object(juice_t *juice, const char *name);

bool juice_check_args(juice_t *juice, bool generate_error, int argc, juice_object_t *args, int expected_argc, int *expected_types);
#define JUICE_CHECK_ARGS(juice, generate_error, argc, args, ...)\
    juice_check_args(\
        (juice),\
        (generate_error),\
        (argc),\
        (args),\
        sizeof((int[]){__VA_ARGS__}) / sizeof(int),\
        (int[]){__VA_ARGS__})

juice_object_t juice_object_make_number(double val);
juice_object_t juice_object_make_bool(bool val);
juice_object_t juice_object_make_null(void);
juice_object_t juice_object_make_string(juice_t *juice, const char *str);
juice_object_t juice_object_make_stringf(juice_t *juice, const char *format, ...) __attribute__ ((format (printf, 2, 3)));
juice_object_t juice_object_make_array(juice_t *juice);
juice_object_t juice_object_make_map(juice_t *juice);
juice_object_t juice_object_make_native_function(juice_t *juice, juice_native_fn fn, void *data);
juice_object_t juice_object_make_error(juice_t *juice, const char *message);
juice_object_t juice_object_make_errorf(juice_t *juice, const char *format, ...) __attribute__ ((format (printf, 2, 3)));
juice_object_t juice_object_make_external(juice_t *juice, void *data);

char* juice_object_serialize(juice_t *juice, juice_object_t obj);

bool juice_object_disable_gc(juice_object_t obj);
void juice_object_enable_gc(juice_object_t obj);

bool juice_object_equals(juice_object_t a, juice_object_t b);

bool juice_object_is_null(juice_object_t obj);

juice_object_t juice_object_copy(juice_object_t obj);
juice_object_t juice_object_deep_copy(juice_object_t obj);

juice_object_type_t juice_object_get_type(juice_object_t obj);
const char*       juice_object_get_type_string(juice_object_t obj);
const char*       juice_object_get_type_name(juice_object_type_t type);

double       juice_object_get_number(juice_object_t obj);
bool         juice_object_get_bool(juice_object_t obj);
const char * juice_object_get_string(juice_object_t obj);

const char*            juice_object_get_error_message(juice_object_t obj);
const juice_traceback_t* juice_object_get_error_traceback(juice_object_t obj);

bool juice_object_set_external_destroy_function(juice_object_t object, juice_data_destroy_fn destroy_fn);
bool juice_object_set_external_copy_function(juice_object_t object, juice_data_copy_fn copy_fn);

int juice_object_get_array_length(juice_object_t obj);

juice_object_t juice_object_get_array_value(juice_object_t object, int ix);
const char*  juice_object_get_array_string(juice_object_t object, int ix);
double       juice_object_get_array_number(juice_object_t object, int ix);
bool         juice_object_get_array_bool(juice_object_t object, int ix);

bool juice_object_set_array_value(juice_object_t object, int ix, juice_object_t value);
bool juice_object_set_array_string(juice_object_t object, int ix, const char *string);
bool juice_object_set_array_number(juice_object_t object, int ix, double number);
bool juice_object_set_array_bool(juice_object_t object, int ix, bool value);

bool juice_object_add_array_value(juice_object_t object, juice_object_t value);
bool juice_object_add_array_string(juice_object_t object, const char *string);
bool juice_object_add_array_number(juice_object_t object, double number);
bool juice_object_add_array_bool(juice_object_t object, bool value);

int          juice_object_get_map_length(juice_object_t obj);
juice_object_t juice_object_get_map_key_at(juice_object_t object, int ix);
juice_object_t juice_object_get_map_value_at(juice_object_t object, int ix);
bool         juice_object_set_map_value_at(juice_object_t object, int ix, juice_object_t val);

bool juice_object_set_map_value_with_value_key(juice_object_t object, juice_object_t key, juice_object_t value);
bool juice_object_set_map_value(juice_object_t object, const char *key, juice_object_t value);
bool juice_object_set_map_string(juice_object_t object, const char *key, const char *string);
bool juice_object_set_map_number(juice_object_t object, const char *key, double number);
bool juice_object_set_map_bool(juice_object_t object, const char *key, bool value);

juice_object_t  juice_object_get_map_value_with_value_key(juice_object_t object, juice_object_t key);
juice_object_t  juice_object_get_map_value(juice_object_t object, const char *key);
const char*   juice_object_get_map_string(juice_object_t object, const char *key);
double        juice_object_get_map_number(juice_object_t object, const char *key);
bool          juice_object_get_map_bool(juice_object_t object, const char *key);

bool juice_object_map_has_key(juice_object_t object, const char *key);

const char*      juice_error_get_message(const juice_error_t *error);
const char*      juice_error_get_filepath(const juice_error_t *error);
const char*      juice_error_get_line(const juice_error_t *error);
int              juice_error_get_line_number(const juice_error_t *error);
int              juice_error_get_column_number(const juice_error_t *error);
juice_error_type_t juice_error_get_type(const juice_error_t *error);
const char*      juice_error_get_type_string(const juice_error_t *error);
const char*      juice_error_type_to_string(juice_error_type_t type);
char*            juice_error_serialize(juice_t *juice, const juice_error_t *error);
const juice_traceback_t* juice_error_get_traceback(const juice_error_t *error);

int         juice_traceback_get_depth(const juice_traceback_t *traceback);
const char* juice_traceback_get_filepath(const juice_traceback_t *traceback, int depth);
const char* juice_traceback_get_line(const juice_traceback_t *traceback, int depth);
int         juice_traceback_get_line_number(const juice_traceback_t *traceback, int depth);
int         juice_traceback_get_column_number(const juice_traceback_t *traceback, int depth);
const char* juice_traceback_get_function_name(const juice_traceback_t *traceback, int depth);

#ifdef __cplusplus
}
#endif
