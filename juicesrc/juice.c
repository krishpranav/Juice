#include <stdio.h>
#include <stdlib.h>
#include "juice.h"

void banner();

int main(int argc, char *argv[]) {
    if (argc < 2) {
        banner();
        return 1;
    }
    juice_t *juice = juice_make();

    juice_object_t args_array = juice_object_make_array(juice);
    for (int i = 1; i < argc; i++) {
        juice_object_add_array_string(args_array, argv[i]);
    }
    juice_set_global_constant(juice, "args", args_array);

    juice_execute_file(juice, argv[1]);
    bool ok = !juice_has_errors(juice);
    if (!ok) {
        int count = juice_errors_count(juice);
        for (int i = 0; i < count; i++) {
            const juice_error_t *err = juice_get_error(juice, i);
            char *err_str = juice_error_serialize(juice, err);
            fprintf(stderr, "%s", err_str);
            juice_free_allocated(juice, err_str);
        }
    }
    juice_destroy(juice);
    return ok;
}

void banner() {
    const char juice[] = "Juice Programming Language";
    printf(juice);
    printf("\n");
    
    const char license[] = "License: Apache-2.0 2021";
    printf(license);
    printf("\n");

    const char repo[] = "Repo: https://github.com/krishpranav/juice";
    printf(repo);
    printf("\n");

    const char author[] = "Author: krishpranav";
    printf(author);
    printf("\n");

    const char args[] = "./juice file.juice";
    printf(args);
    printf("\n");
}