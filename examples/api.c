#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "juice.h"

static juice_object_t external_add(juice_t *juice, void *data, int argc, juice_object_t *args);

int main() {
    juice_t *juice = juice_make();

    juice_execute(juice, "fn add(a, b) { return a + b }");    
    juice_object_t res = JUICE_CALL(juice, "add", juice_object_make_number(42), juice_object_make_number(42));
    assert(juice_object_get_number(res) == 84);

    juice_set_native_function(juice, "external_add", external_add, NULL);
    juice_execute(juice, "assert(external_add(42, 42) == 84)");
    assert(!juice_has_errors(juice));

    juice_execute(juice, "external_add()");
    assert(juice_has_errors(juice));
    for (int i = 0; i < juice_errors_count(juice); i++) {
        const juice_error_t *err = juice_get_error(juice, i);
        char *err_string = juice_error_serialize(juice, err);
        puts(err_string);
        juice_free_allocated(juice, err_string);
    }

    juice_destroy(juice);
    return 0;
}

static juice_object_t external_add(juice_t *juice, void *data, int argc, juice_object_t *args) {
    if (!JUICE_CHECK_ARGS(juice, true, argc, args, JUICE_OBJECT_NUMBER, JUICE_OBJECT_NUMBER)) {
        return juice_object_make_null();
    }

    double a = juice_object_get_number(args[0]);
    double b = juice_object_get_number(args[1]);

    return juice_object_make_number(a + b);
}