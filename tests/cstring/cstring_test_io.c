#include "../../src/cstring.h"

#define FILENAME     "cstring_test_io_file.txt"
#define FOPEN_ERRMSG "Error: file could not be opened.
#define COUNT_MAX    5

int main(void) {
    puts("===== CSTRING data type unit tests - I/O operations =====");
    FILE* file = fopen(FILENAME, "w");

    if (!file) {
        fprintf(stderr, "%s\n", FOPEN_ERRMSG);
        exit(1);
    }

    string* str;
    size_t count = 0;

    while (count < COUNT_MAX) {

        count++;
    }

    fclose(file);
    return 0;
}

void test_string_read_line(FILE* file) {
    printf("\n===== Test: string_read_line(), string_write_line() =====\n");
    string* str, num;
    size_t count = 0;

    while (count < COUNT_MAX) {
        str = string_read_line();
        num = new_string("");
        str = string_mut_concatenate(str, num);
        string_write_line(file, str);
        delete_string(str);
        delete_string(num);
        count++;
    }
}