#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ARRAY_LEN(array) (int)(sizeof(array) / sizeof(array[0]))
#include "juice.h"

static bool execute_file(const char *filename, bool must_succeed);
static void *counted_malloc(void *ctx, size_t size);
static void counted_free(void *ctx, void *ptr);
static void print_juice_errors(juice_t *juice);

typedef struct alloc_data {
    int malloc_count;
    int total_malloc_count; 
} alloc_data_t;

#ifdef JUICE_BENCHMARKS_MAIN
int main(int argc, char *argv[]) {
    int tests_len = argc - 1;
    char **tests = argv + 1;
#else
    int benchmarks_main() {
        const char *tests[] = {
            "strings.juice",
            "mergesort.juice",
            "raytracer_profile.juice",
            "raytracer_profile_optimised.juice",
            "primes.juice",
            "fibonacci.juice",
        };
        int tests_len = ARRAY_LEN(tests);
#endif
#if 0
    } 
#endif

    for (int i = 0; i < tests_len; i++) {
        const char *test = tests[i];
        g_alloc_data.malloc_count = 0;
        g_alloc_data.total_malloc_count = 0;
        printf("Benchmarking %s: \n", test);
        clock_t start = clock();
        execute_file(test, true);
        clock_t end = clock();
        float seconds = (float)(end - start) / CLOCKS_PER_SEC;
        printf("\tTime: %1.3g seconds\n", (double)seconds);
        printf("\tAllocations: %1.0f k\n", g_alloc_data.total_malloc_count / 1000.0);
        assert(g_alloc_data.malloc_count == 0);
        puts("OK");
    }
    return 0;
}