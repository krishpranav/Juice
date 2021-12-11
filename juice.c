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

#endif
