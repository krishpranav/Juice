#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "juice.h"

#define PROMPT ">> "

static void print_errors(juice_t *juice, const char *line);
static juice_object_t exit_repl(juice_t *juice, void *data, int argc, juice_object_t *args);

#ifdef JUICE_REPL_MAIN
int main(int argc, char *argv[]) {
#else
void repl_start() {
#endif
#if 0
} // unconfuse xcode
#endif
    bool exit = false;

    juice_t *juice = juice_make();

    juice_set_repl_mode(juice, true);
    juice_set_timeout(juice, 100.0);

    juice_set_native_function(juice, "exit", exit_repl, &exit);

    while (!exit) {
        printf("%s", PROMPT);
        char *line = NULL;
        size_t len = 0;
        getline(&line, &len, stdin);
        if (!line) {
            continue;
        }
        line[strlen(line) - 1] = '\0'; // removes last \n

        juice_object_t res = juice_execute(juice, line);
        if (juice_has_errors(juice)) {
            print_errors(juice, line);
            free(line);
            continue;
        }

        char *object_str = juice_object_serialize(juice, res);
        puts(object_str);
        free(object_str);
    }

    juice_destroy(juice);
}

// INTERNAL
static void print_errors(juice_t *juice, const char *line) {
    int count = juice_errors_count(juice);
    for (int i = 0; i < count; i++) {
        const juice_error_t *err = juice_get_error(juice, i);
        char *err_str = juice_error_serialize(juice, err);
        puts(err_str);
        free(err_str);
    }
}

static juice_object_t exit_repl(juice_t *juice, void *data, int argc, juice_object_t *args) {
    bool *exit_repl = (bool*)data;
    *exit_repl = true;
    return juice_object_make_null();
}