#include <stdio.h>
#include "../../src/cstring.h"

void print_string_data(const string* str);
void print_string_copy(const string* str);
void print_string_concatenation(const string* s1, const string* s2);
void print_string_substring(const string* str);
void print_string_letter_cases(const string* str);
void print_string_truncation(const string* str);

int main(void) {
    puts("===== CSTRING data type unit tests - Immutative functions =====");

    string* str01 = new_string("under");
    string* str02 = new_string("stand");

    print_string_data(str01);
    print_string_data(str02);

    print_string_copy(str01);
    print_string_concatenation(str01, str02);
    print_string_substring(str02);

    string* concat = new_string("uNdErStAnD");
    print_string_letter_cases(concat);

    string* trunc = new_string("  understand  ");
    print_string_truncation(trunc);

    delete_string(trunc);
    delete_string(concat);
    delete_string(str01);
    delete_string(str02);

    return 0;
}

void print_string_data(const string* str) {
    printf("\n===== Test: getters, query methods (\"%s\") =====\n", string_get_data(str));
    printf("\"%s\" - %lu - ", string_get_data(str), string_get_length(str));
    string_isvalid(str) ? printf("valid - ") : printf("invalid - ");
    string_isempty(str) ? printf("empty\n") : printf("not empty\n");
}

void print_string_copy(const string* str) {
    printf("\n===== Test: copying (\"%s\") =====\n", string_get_data(str));
    string* copy = string_copy(str);

    printf("\"%s\";\t%lu;\t%p;\t%p;\t", string_get_data(str), string_get_length(str), (void*)str, (void*)string_get_data(str));
    string_isvalid(str) ? printf("valid;\t") : printf("invalid;\t");
    string_isempty(str) ? printf("empty\n") : printf("not empty\n");

    printf("\"%s\";\t%lu;\t%p;\t%p;\t", string_get_data(copy), string_get_length(copy), (void*)copy, (void*)string_get_data(copy));
    string_isvalid(copy) ? printf("valid;\t") : printf("invalid;\t");
    string_isempty(copy) ? printf("empty\n") : printf("not empty\n");

    bool result = string_areequal(str, copy);
    result ? printf("\"%s\" is equal to \"%s\"\n",     string_get_data(str), string_get_data(copy)) : 
             printf("\"%s\" is NOT equal to \"%s\"\n", string_get_data(str), string_get_data(copy));

    delete_string(copy);
}

void print_string_concatenation(const string* s1, const string* s2) {
    printf("\n===== Test: concatenation (\"%s\", \"%s\") =====\n", string_get_data(s1), string_get_data(s2));
    string* concat = string_concatenate(s1, s2);

    printf("\"%s\";\t%lu;\t", string_get_data(s1), string_get_length(s1));
    string_isvalid(s1) ? printf("valid;\t") : printf("invalid;\t");
    string_isempty(s1) ? printf("empty\n") : printf("not empty\n");

    printf("\"%s\";\t%lu;\t", string_get_data(s2), string_get_length(s2));
    string_isvalid(s2) ? printf("valid;\t") : printf("invalid;\t");
    string_isempty(s2) ? printf("empty\n") : printf("not empty\n");

    printf("\"%s\";\t%lu;\t", string_get_data(concat), string_get_length(concat));
    string_isvalid(concat) ? printf("valid;\t") : printf("invalid;\t");
    string_isempty(concat) ? printf("empty\n") : printf("not empty\n");

    delete_string(concat);
}

void print_string_substring(const string* str) {
    printf("\n===== Test: substring (\"%s\") =====\n", string_get_data(str));
    string* substring = string_substring(str, 1, string_get_length(str) - 2);

    printf("\"%s\";\t%lu;\t", string_get_data(str), string_get_length(str));
    string_isvalid(str) ? printf("valid;\t") : printf("invalid;\t");
    string_isempty(str) ? printf("empty\n") : printf("not empty\n");

    printf("\"%s\";\t%lu;\t", string_get_data(substring), string_get_length(substring));
    string_isvalid(substring) ? printf("valid;\t") : printf("invalid;\t");
    string_isempty(substring) ? printf("empty\n") : printf("not empty\n");

    delete_string(substring);
}

void print_string_letter_cases(const string* str) {
    printf("\n===== Test: upper case, lower case, capitalisation (\"%s\") =====\n", string_get_data(str));
    string* lowercase = string_to_lower_case(str);

    printf("\"%s\";\t%lu;\t", string_get_data(lowercase), string_get_length(lowercase));
    string_isvalid(lowercase) ? printf("valid;\t") : printf("invalid;\t");
    string_isempty(lowercase) ? printf("empty\n") : printf("not empty\n");

    string* uppercase = string_to_upper_case(str);
    printf("\"%s\";\t%lu;\t", string_get_data(uppercase), string_get_length(uppercase));
    string_isvalid(uppercase) ? printf("valid;\t") : printf("invalid;\t");
    string_isempty(uppercase) ? printf("empty\n") : printf("not empty\n");

    string* capitalised = string_capitalise(str);
    printf("\"%s\";\t%lu;\t", string_get_data(capitalised), string_get_length(capitalised));
    string_isvalid(capitalised) ? printf("valid;\t") : printf("invalid;\t");
    string_isempty(capitalised) ? printf("empty\n") : printf("not empty\n");

    delete_string(lowercase);
    delete_string(uppercase);
    delete_string(capitalised);
}

void print_string_truncation(const string* str) {
    printf("\n===== Test: truncation (\"%s\") =====\n", string_get_data(str));
    string* alltrunc = string_truncate(str);

    printf("\"%s\";\t%lu;\t", string_get_data(alltrunc), string_get_length(alltrunc));
    string_isvalid(alltrunc) ? printf("valid;\t") : printf("invalid;\t");
    string_isempty(alltrunc) ? printf("empty\n") : printf("not empty\n");

    string* truncleft = string_truncate_left(str);
    printf("\"%s\";\t%lu;\t", string_get_data(truncleft), string_get_length(truncleft));
    string_isvalid(truncleft) ? printf("valid;\t") : printf("invalid;\t");
    string_isempty(truncleft) ? printf("empty\n") : printf("not empty\n");

    string* truncright = string_truncate_right(str);
    printf("\"%s\";\t%lu;\t", string_get_data(truncright), string_get_length(truncright));
    string_isvalid(truncright) ? printf("valid;\t") : printf("invalid;\t");
    string_isempty(truncright) ? printf("empty\n") : printf("not empty\n");

    delete_string(alltrunc);
    delete_string(truncleft);
    delete_string(truncright);
}