#include <stdio.h>
#include <string.h>
#include "../../src/cstring.h"

void print_string_data(const string* str);
void print_string_equality(const string* str1, const string* str2);
void print_string_affix(const string* str, const char* afx);
void print_string_affix_str(const string* str, const string* afx);

int main(void)
{
    puts("===== CSTRING data type unit tests - Basic functionalities =====");
    string* str01     = new_string("string");
    string* duplicate = new_string("string");

    char invalid[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g' };
    string* str02 = new_string(invalid); // will correct it to a null terminating ("valid") string
    string* str03 = new_string("");

    string* str04 = new_string(" ");

    print_string_data(str01);
    print_string_data(str02);
    print_string_data(str03);
    print_string_data(str04);

    print_string_equality(str01, str02);
    print_string_equality(str01, duplicate);

    char affix_chr[]  = "str";
    string* affix_str = new_string("ing");

    print_string_affix(str01, affix_chr);
    print_string_affix_str(str01, affix_str);
    print_string_affix(str01, invalid);
    print_string_affix_str(str01, str02);

    delete_string(affix_str);
    delete_string(duplicate);

    delete_string(str01);
    delete_string(str02);
    delete_string(str03);
    delete_string(str04);
    return 0;
}

void print_string_data(const string* str) {
    printf("\n===== Test: getters, query methods (\"%s\") =====\n", string_get_data(str));
    printf("\"%s\" - %lu - ", string_get_data(str), string_get_length(str));
    string_isvalid(str) ? printf("valid - ") : printf("invalid - ");
    string_isempty(str) ? printf("empty\n") : printf("not empty\n");
}

void print_string_equality(const string* str1, const string* str2) {
    printf("\n===== Test: equality (\"%s\", \"%s\") =====\n", string_get_data(str1), string_get_data(str2));
    bool result = string_areequal(str1, str2);
    result ? printf("\"%s\" is equal to \"%s\"\n", string_get_data(str1), string_get_data(str2)) : 
             printf("\"%s\" is NOT equal to \"%s\"\n", string_get_data(str1), string_get_data(str2));
}

void print_string_affix(const string* str, const char* afx) {
    printf("\n===== Test: substring, prefix, suffix (\"%s\", \"%s\") =====\n", string_get_data(str), afx);

    bool result01 = string_issubstring(str, afx);
    result01 ?  printf("\"%s\" is substring of \"%s\"\n",     afx, string_get_data(str)) :
                printf("\"%s\" is NOT substring of \"%s\"\n", afx, string_get_data(str));

    bool result02 = string_isprefix(str, afx);
    result02 ?  printf("\"%s\" is prefix of \"%s\"\n",     afx, string_get_data(str)) :
                printf("\"%s\" is NOT prefix of \"%s\"\n", afx, string_get_data(str));

    bool result03 = string_issuffix(str, afx);
    result03 ?  printf("\"%s\" is suffix of \"%s\"\n",     afx, string_get_data(str)) :
                printf("\"%s\" is NOT suffix of \"%s\"\n", afx, string_get_data(str));

    bool result04 = string_contains_char(str, 'e');
    result04 ?  printf("\"%s\" contains the letter '%c'\n",         string_get_data(str), 'e') :
                printf("\"%s\" DOES NOT contain the letter '%c'\n", string_get_data(str), 'e');
}

void print_string_affix_str(const string* str, const string* afx) {
    printf("\n===== Test: substring, prefix, suffix (\"%s\", \"%s\") =====\n", string_get_data(str), string_get_data(afx));

    bool result01 = string_issubstring_str(str, afx);
    result01 ?  printf("\"%s\" is substring of \"%s\"\n",     string_get_data(afx), string_get_data(str)) :
                printf("\"%s\" is NOT substring of \"%s\"\n", string_get_data(afx), string_get_data(str));

    bool result02 = string_isprefix_str(str, afx);
    result02 ?  printf("\"%s\" is prefix of \"%s\"\n",     string_get_data(afx), string_get_data(str)) :
                printf("\"%s\" is NOT prefix of \"%s\"\n", string_get_data(afx), string_get_data(str));

    bool result03 = string_issubstring_str(str, afx);
    result03 ?  printf("\"%s\" is suffix of \"%s\"\n",     string_get_data(afx), string_get_data(str)) :
                printf("\"%s\" is NOT suffix of \"%s\"\n", string_get_data(afx), string_get_data(str));

    bool result04 = string_contains_char(str, 'e');
    result04 ?  printf("\"%s\" contains the letter '%c'\n",         string_get_data(str), 'e') :
                printf("\"%s\" DOES NOT contain the letter '%c'\n", string_get_data(str), 'e');
}

