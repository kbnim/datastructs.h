#include <stdio.h>
#include "../../src/cstring.h"

void test_string_overwrite(string* str, const char* s);
void test_string_concatenation(string* str1, string* str2);
void test_string_substring(string* str, size_t fst, size_t lst);
void test_string_letter_cases(string* str);
void test_string_truncation(string* str);

int main(void) {
    puts("===== CSTRING data type unit tests - Mutative functions =====");

    string* str01 = new_string("original");
    test_string_overwrite(str01, "new");
    
    string* str02 = new_string(" and then some");
    test_string_concatenation(str01, str02);
    test_string_substring(str01, 1, 8);

    string* str03 = new_string("sArCaStIc");
    test_string_letter_cases(str03);

    string* str04 = new_string("  whitespaces  ");
    test_string_truncation(str04);

    delete_string(str01);
    delete_string(str02);
    delete_string(str03);
    delete_string(str04);
    
    return 0;
}

void test_string_overwrite(string* str, const char* s) {
    printf("\n===== Test: overwriting (\"%s\") =====\n", string_get_data(str));
    printf("\"%s\" (%lu) -> ", string_get_data(str), string_get_length(str));
    string_mut_overwrite(str, s);
    printf("\"%s\" (%lu)\n", string_get_data(str), string_get_length(str));
}

void test_string_concatenation(string* str1, string* str2) {
    printf("\n===== Test: concatenation (\"%s\", \"%s\") =====\n", string_get_data(str1), string_get_data(str2));
    printf("\"%s\" (%lu) + ", string_get_data(str1), string_get_length(str1));
    printf("\"%s\" (%lu) -> ", string_get_data(str2), string_get_length(str2));
    string_mut_concatenate(str1, str2);
    printf("\"%s\" (%lu)\n", string_get_data(str1), string_get_length(str1));
}

void test_string_substring(string* str, size_t fst, size_t lst) {
    printf("\n===== Test: creating substring (\"%s\") =====\n", string_get_data(str));
    printf("\"%s\" (%lu) -> ", string_get_data(str), string_get_length(str));
    string_mut_to_substring(str, fst, lst);
    printf("\"%s\" (%lu)\n", string_get_data(str), string_get_length(str));
}

void test_string_letter_cases(string* str) {
    printf("\n===== Test: upper case, lower case, capitalisation (\"%s\") =====\n", string_get_data(str));
    printf("\"%s\" (%lu) -> ", string_get_data(str), string_get_length(str));
    string_mut_to_upper_case(str);
    printf("\"%s\" (%lu) -> ", string_get_data(str), string_get_length(str));
    string_mut_to_lower_case(str);
    printf("\"%s\" (%lu) -> ", string_get_data(str), string_get_length(str));
    string_mut_capitalise(str);
    printf("\"%s\" (%lu)\n", string_get_data(str), string_get_length(str));
}

void test_string_truncation(string* str) {
    printf("\n===== Test: truncation (\"%s\") =====\n", string_get_data(str));

    string* cpy01 = string_copy(str);
    string* cpy02 = string_copy(str);

    printf("\"%s\" (%lu) -> ", string_get_data(str), string_get_length(str));
    string_mut_truncate(str);
    printf("\"%s\" (%lu)\n", string_get_data(str), string_get_length(str));

    printf("\"%s\" (%lu) -> ", string_get_data(cpy01), string_get_length(cpy01));
    string_mut_truncate_left(cpy01);
    printf("\"%s\" (%lu)\n", string_get_data(cpy01), string_get_length(cpy01));

    printf("\"%s\" (%lu) -> ", string_get_data(cpy02), string_get_length(cpy02));
    string_mut_truncate_right(cpy02);
    printf("\"%s\" (%lu)\n", string_get_data(cpy02), string_get_length(cpy02));

    delete_string(cpy01);
    delete_string(cpy02);
}