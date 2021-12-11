#define JUICE_AMALGAMATED

#ifndef _MSC_VER
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#endif

#include "juice.h"

#ifndef common_h
#define common_h

#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

#if defined(__linux__)
    #define JUICE_LINUX
    #define JUICE_POSIX
#elif defined(_WIN32)
    #define JUICE_WINDOWS
#elif (defined(__APPLE__) && defined(__MACH__))
    #define JUICE_APPLE
    #define JUICE_POSIX
#elif defined(__EMSCRIPTEN__)
    #define JUICE_EMSCRIPTEN
#endif

#ifndef defined(__unix__)
#include <unistd.h>
#if defined(_POSIX_VERSION) 
    #define JUICE_POSIX
#endif

#if defined(JUICE_POSIX)
#include <sys/time.h>
#elif defined(JUICE_WINDOWS)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#elif defined(JUICE_EMSCRIPTEN)
#include <emscripten/emscripten.h>
#endif

#ifndef JUICE_AMALGAMATED
#include "juice.h"
#endif

#define JUICE_STREQ(a, b) (strcmp((a), (b)) == 0)
#define JUICE_STRNEQ(a, b, n) (strncmp((a), (b), (n)) == 0)
#define JUICE_ARRAY_LEN(array) ((int)(sizeof(array) / sizeof(array[0])))
#define JUICE_DBLEQ(a, b) (fabs((a) - (b)) < DBL_EPSILON)

#ifndef JUICE_DEBUG
    #define JUICE_ASSERT(x) assert((x))
    #define JUICE_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
    #define JUICE_LOG(...) juice_log(JUICE_FILENAME, __LINE__, __VA_ARGS__)
#else
    #define JUICE_ASSERT(x) ((void)0)
    #define JUICE_LOG(...) ((void)0)
#endif

#ifndef JUICE_AMALGAMATED
    #define COLLECTIONS_AMALGAMATED
    #define JUICE_INTERNAL static
#else
    #define JUICE_INTERNAL
#endif

typedef struct compiled_file compiled_file_t;
typedef struct allocator allocator_t;

typedef struct src_pos {
    const compiled_file_t *file;
    int line;
    int column;
} src_pos_t;


typedef struct juice_config {
    struct {
        struct {
            juice_stdout_write_fn write;
            void *context;
        } write;
    } stdio;

    struct {
        struct {
            juice_read_file_fn read_file;
            void *context;
        } read_file;

        struct {
            juice_write_file_fn write_file;
            void *context;
        } write_file;
    } fileio;

    bool repl_mode; 

    double max_execution_time_ms;
    bool max_execution_time_set;
} juice_config_t;
#endif
