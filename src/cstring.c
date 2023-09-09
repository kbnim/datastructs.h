#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h> // toupper(), tolower(), etc.
#include <stdarg.h>

#include "cstring.h"

const char DELIMITERS[] = " \t\n\v\f\r";
const char PUNCTUATION_MARKS[] = " ,.;:\t\n\v\f\r";

struct _string {
    char* data;
    size_t length;
};

/* ================================ */
/* === Error handling functions === */
/* ================================ */

// Generic error handling function.
static void string_error_handling(const char* error_msg, const int error_code) {
    #if !(defined(DATASTRUCTS_NO_WARNINGS) || defined(DATASTRUCTS_CSTRING_NO_WARNINGS))
        fprintf(stderr, "Error: %d\n%s\n", error_code, error_msg);
    #endif
    
    exit(error_code);
}

// Specialised function for handling out-of-bound indices.
static void string_check_index(const string* str, const size_t index) {
    if (index >= str->length + 1) {
        delete_string((string*)str);
        string_error_handling(CSTRING_ERRMSSG_INDEX_OUT_OF_BOUNDS,
                              CSTRING_ERRCODE_INDEX_OUT_OF_BOUNDS);
    }
}

static void string_check_null_string(const string* str) {
    if (!str) string_error_handling(CSTRING_ERRMSSG_NULL_STRING,
                                    CSTRING_ERRCODE_NULL_STRING);
}

static void string_warning_handling(const char* warn_msg) {
    #if !(defined(DATASTRUCTS_NO_WARNINGS) || defined(DATASTRUCTS_CSTRING_NO_WARNINGS))
        fprintf(stderr, "%s\n", warn_msg);
    #endif
}

/* ========================================= */
/* ======== Constructor, destructor ======== */
/* ========================================= */

// Constructor of string.
string* new_string(const char* source) {
    string* str = calloc(1, sizeof(string));

    if (!str) string_error_handling(CSTRING_ERRMSSG_MEMORY_ALLOCATION_FAILURE,
                                    CSTRING_ERRCODE_MEMORY_ALLOCATION_FAILURE);

    str->length = strlen(source);
    str->data   = calloc(str->length + 1, sizeof(char));

    if (!str->data) {
        free(str);
        string_error_handling(CSTRING_ERRMSSG_MEMORY_ALLOCATION_FAILURE,
                              CSTRING_ERRCODE_MEMORY_ALLOCATION_FAILURE);
    }

    strncpy(str->data, source, str->length + 1);

    return str;
}

// Destructor of string. Standardised template: void func_name(void* obj).
void delete_string(void* obj) {
    if (obj) {
        string* str = (string*)obj;
        free(str->data);
        free(str);
        str = NULL;
        obj = NULL;
    }
}

/* ======================================= */
/* =============== Getters =============== */
/* ======================================= */

// Getter of length of string.
size_t string_get_length(const string* str) {
    string_check_null_string(str);
    return str->length;
}

// Getter of traditional C-style string (i.e. character array). Individual characters are not directly modifiable.
const char* string_get_data(const string* str) {
    string_check_null_string(str);
    return str->data;
}

// Returns the character at the specified index.
char string_get_char_at(const string* str, const size_t index) {
    string_check_null_string(str);
    string_check_index(str, index);
    return str->data[index];
}

/* ======================================= */
/* ============ Query methods ============ */
/* ======================================= */

// Checks whether the string's last character is the null terminator character.
bool string_isvalid(const string* str) {
    string_check_null_string(str);
    return str->data[str->length] == '\0';
}

// Checks whether the string is empty, meaning that either the length is 0 or all the characters are whitespaces or control characters.
bool string_isempty(const string* str) {
    string_check_null_string(str);
    return str->length == 0;
}

// Compares two strings. Returns 0 is they're equal. Return a negative integer if str1 < str2. Returns a positie integer if str1 > str2.
// Standardised template: int func_name(const void* obj1, const void* obj2)
int string_compare(const void* str1, const void* str2) {
    string_check_null_string((string*)str1);
    string_check_null_string((string*)str2);
    return strcmp(((string*)str1)->data, ((string*)str2)->data);
}

// Checks whether two strings are equal.
bool string_areequal(const void* str1, const void* str2) {
    string_check_null_string((string*)str1);
    string_check_null_string((string*)str2);
    return strcmp(((string*)str1)->data, ((string*)str2)->data) == 0;
}

// Checks whether 'sub_str' is a substring of 'str'. Argument 'str' is a standard C-style character array.
bool string_issubstring(const string* str, const char* sub_str) {
    string_check_null_string(str);

    if (!sub_str) {
        string_warning_handling(CSTRING_WARNMSG_SUBSTRING_CHAR_NULL);
        return false;
    }

    size_t sub_str_length = strlen(sub_str);

    if (sub_str_length > str->length) {
        string_warning_handling(CSTRING_WARNMSG_SUBSTRING_TOO_LONG);
        return false;
    }

    char buffer_string[sub_str_length + 1];
    buffer_string[sub_str_length] = '\0';
    size_t first_occurrence = 0;
    size_t occurrences = 0;

    for (size_t i = 0; i < str->length; i++) {
        if (str->data[i] == sub_str[first_occurrence]) {
            buffer_string[first_occurrence] = str->data[i];
            first_occurrence++;
            occurrences++; 
        }
    }

    return strcmp(sub_str, buffer_string) == 0;
}

// Checks whether 'sub_str' is a substring of 'str'. Argument 'str' is of type 'string'.
bool string_issubstring_str(const string* str, const string* sub_str) {
    string_check_null_string(str);
    string_check_null_string(sub_str);

    if (sub_str->length > str->length) {
        string_warning_handling(CSTRING_WARNMSG_SUBSTRING_TOO_LONG);
        return false;
    }

    char buffer_string[sub_str->length + 1];
    buffer_string[sub_str->length] = '\0';
    size_t first_occurrence = 0;
    size_t occurrences = 0;

    for (size_t i = 0; i < str->length; i++) {
        if (str->data[i] == sub_str->data[first_occurrence]) {
            buffer_string[first_occurrence] = str->data[i];
            first_occurrence++;
            occurrences++; 
        }
    }

    return strcmp(sub_str->data, buffer_string) == 0;
}

// Checks whether the given character is present in the string. Often used to check for delimiters in a text.
bool string_contains_char(const string* str, const char character) {
    string_check_null_string(str);
    return strchr(str->data, character) != NULL;
}

// Checks whether 'prefix' occurs in 'str'. Argument 'prefix' is a standard C-style character array.
bool string_isprefix(const string* str, const char* prefix) {
    string_check_null_string(str);

    if (!prefix) {
        delete_string((string*)str);
        string_error_handling(CSTRING_ERRMSSG_NULL_STRING,
                              CSTRING_ERRCODE_NULL_STRING);
    }

    size_t prefix_length = strlen(prefix);

    if (prefix_length > str->length) {
        string_warning_handling(CSTIRNG_WARNMSG_PREFIX_TOO_LONG);
        return false;
    }

    for (size_t i = 0; i < prefix_length; i++) {
        if (str->data[i] != prefix[i]) return false;
    }

    return true;
}

// Checks whether 'prefix' occurs in 'str'. Argument 'prefix' is of type 'string'.
bool string_isprefix_str(const string* str, const string* prefix) {
    string_check_null_string(str);
    string_check_null_string(prefix);

    if (prefix->length > str->length) {
        string_warning_handling(CSTIRNG_WARNMSG_PREFIX_TOO_LONG);
        return false;
    }

    for (size_t i = 0; i < prefix->length; i++) {
        if (str->data[i] != prefix->data[i]) return false;
    }

    return true;
}

// Checks whether 'suffix' occurs in 'str'. Argument 'suffix' is a standard C-style character array.
bool string_issuffix(const string* str, const char* suffix) {
    string_check_null_string(str);

    if (!suffix) {
        delete_string((string*)str);
        string_error_handling(CSTRING_ERRMSSG_NULL_STRING,
                              CSTRING_ERRCODE_NULL_STRING);
    }

    size_t suffix_length = strlen(suffix);

    if (str->length < suffix_length) {
        string_warning_handling(CSTRING_WARNMSG_SUFFIX_TOO_LONG);
        return false;
    }

    size_t start_index = str->length - suffix_length;

    printf("start index: %lu\n", start_index);

    for (size_t i = start_index; i < str->length; i++) {
        if (str->data[i] != suffix[i]) return false;
    }
    
    return true;
}

// Checks whether 'suffix' occurs in 'str'. Argument 'suffix' is of type 'string'.
bool string_issuffix_str(const string* str, const string* suffix) {
    string_check_null_string(str);
    string_check_null_string(suffix);

    if (str->length < suffix->length) {
        string_warning_handling(CSTRING_WARNMSG_SUFFIX_TOO_LONG);
        return false;
    }

    size_t start_index = str->length - suffix->length;

    for (size_t i = start_index; i < str->length; i++) {
        if (str->data[i] != suffix->data[i]) return false;
    }
    
    return true;
}

// Returns a pointer to the first occurrence of 'character' in the string. Identical to 'strchr()' but for 'string' type.
char* string_find_first_char(const string* str, char character) {
    string_check_null_string(str);
    return strchr(str->data, character);
}

// Returns a pointer to the last occurrence of 'character' in the string. Identical to 'strrchr()' but for 'string' type.
char* string_find_last_char(const string* str, char character) {
    string_check_null_string(str);
    return strrchr(str->data, character);
}

/* ======================================================================================= */
/* === Immutative methods: methods that return a modified copy of the oringinal string === */
/* ======================================================================================= */

// Returns an exact copy of the original string.
string* string_copy(const string* str) {
    string_check_null_string(str);
    return new_string(str->data);
}

// Concatenates the two strings and returns it as a new object.
string* string_concatenate(const string* str1, const string* str2) {
    string_check_null_string(str1);
    string_check_null_string(str2);

    size_t length = str1->length + str2->length;
    char proto_string[length + 1];

    for (size_t index = 0; index < length; index++) {
        if (index < str1->length) {
            proto_string[index] = str1->data[index];
        } else {
            proto_string[index] = str2->data[index - str1->length];
        }
    }

    proto_string[length] = '\0';

    return new_string(proto_string);
}

// Creates a substring based on the indices and returns it as a new object.
string* string_substring(const string* str, const size_t start_index, const size_t end_index) {
    string_check_null_string(str);
    string_check_index(str, start_index);
    string_check_index(str, end_index);

    size_t length = end_index - start_index + 1;
    char proto_string[length + 1];

    for (size_t i = 0; i < length; i++) {
        proto_string[i] = str->data[start_index + i];
    }

    proto_string[length] = '\0';

    return new_string(proto_string);
}

// Returns a new string where
string* string_to_lower_case(const string* str) {
    string_check_null_string(str);

    char proto_str[str->length + 1];
    
    for (size_t i = 0; i < str->length + 1; i++) {
        proto_str[i] = (char)tolower(str->data[i]);
    }

    return new_string(proto_str);
}

// Returns a new string where all the characters are upper-case letters.
string* string_to_upper_case(const string* str) {
    string_check_null_string(str);

    char proto_str[str->length + 1];
    
    for (size_t i = 0; i < str->length + 1; i++) {
        proto_str[i] = (char)toupper(str->data[i]);
    }

    return new_string(proto_str);
}

// Returns a new string where the first character is capitalised.
string* string_capitalise(const string* str) {
    string_check_null_string(str);

    char proto_str[str->length + 1];
    strncpy(proto_str, str->data, str->length + 1);
    if (islower(proto_str[0])) {
        proto_str[0] = (char)toupper(str->data[0]);
    }

    return new_string(proto_str);
}

// Returns a new string where leading and trailing whitespaces are removed.
string* string_truncate(const string* str) {
    string_check_null_string(str);

    size_t start = 0;
    size_t end   = 0;

    while (start <= str->length && (isspace(str->data[start]) || iscntrl(str->data[start]))) {
        start++;
    }

    end = start;

    while (end <= str->length && !(isspace(str->data[end]) || iscntrl(str->data[end]))) {
        end++;
    }

    end--;
    return string_substring(str, start, end);
}

// Returns a new string where leading whitespaces are removed.
string* string_truncate_left(const string* str) {
    string_check_null_string(str);

    size_t start = 0;

    while (start <= str->length && (isspace(str->data[start]) || iscntrl(str->data[start]))) {
        start++;
    }

    return string_substring(str, start, str->length);
}

// Returns a new string where trailing whitespaces are removed.
string* string_truncate_right(const string* str) {
    string_check_null_string(str);

    size_t start = 0;
    size_t end   = 0;

    while (start <= str->length && (isspace(str->data[start]) || iscntrl(str->data[start]))) {
        start++;
    }

    end = start;

    while (end <= str->length && !(isspace(str->data[end]) || iscntrl(str->data[end]))) {
        end++;
    }

    end--;
    return string_substring(str, 0, end);
}

/* ======================================================================================= */
/* === Mutative methods: methods that modify the internal state of the original string === */
/* ======================================================================================= */

// Replaces the character at the givn index. Prevents you from replacing the null terminator and inserting another extra one.
void string_mut_char_at(string* str, char character, const size_t index) {
    if (character == '\0') return;
    string_check_null_string(str);
    string_check_index(str, index);
    str->data[index] = character;
}

// Overwrites the original contents of the string.
void string_mut_overwrite(string* str, const char* new_str) {
    string_check_null_string(str);

    if (!new_str) {
        string_warning_handling(CSTRING_WARNMSG_OVERWRITE_TO_NULL);
        return;
    }

    free(str->data);
    size_t new_length = strlen(new_str);
    str->data = calloc(new_length + 1, sizeof(char));
    str->length = new_length;
    strncpy(str->data, new_str, str->length + 1);
}

// Concatenates 'str2' to the end of 'str1'. 'str1' is modified, 'str2' is left unaffected.
void string_mut_concatenate(string* str1, const string* str2) {
    string_check_null_string(str1);
    string_check_null_string(str2);
    size_t length = str1->length + str2->length;
    str1->data = realloc(str1->data, (length + 1) * sizeof(char));

    if (!str1->data) {
        string_error_handling(CSTRING_ERRMSSG_MEMORY_ALLOCATION_FAILURE,
                              CSTRING_ERRCODE_MEMORY_ALLOCATION_FAILURE);
    }

    for (size_t index = str1->length; index < length; index++) {
        str1->data[index] = str2->data[index - str1->length];
    }

    str1->data[length] = '\0';
    str1->length = length;
}

// Creates a substring based on the indices and returns it as a new object.
void string_mut_to_substring(string* str, const size_t start_index, const size_t end_index) {
    string_check_null_string(str);
    string_check_index(str, start_index);
    string_check_index(str, end_index);
    size_t new_length = end_index - start_index + 1;
    char proto_string[new_length + 1];

    for (size_t i = start_index; i <= end_index; i++) {
        proto_string[i - start_index] = str->data[i];
    }

    proto_string[new_length] = '\0';
    free(str->data);
    str->data = calloc(new_length + 1, sizeof(char));
    str->length = new_length;
    strncpy(str->data, proto_string, str->length + 1);
}

// Converts all upper-case letters to lower-case letters.
void string_mut_to_lower_case(string* str) {
    string_check_null_string(str);

    for (size_t i = 0; i < str->length + 1; i++) {
        str->data[i] = (char)tolower(str->data[i]);
    }
}

// Converts all lower-caseletters to upper-case letters.
void string_mut_to_upper_case(string* str) {
    string_check_null_string(str);

    for (size_t i = 0; i < str->length + 1; i++) {
        str->data[i] = (char)toupper(str->data[i]);
    }
}

// Capitalises the first character of the string.
void string_mut_capitalise(string* str) {
    string_check_null_string(str);
    str->data[0] = (char)toupper(str->data[0]);
}

// Removes leading and trailing whitespaces.
void string_mut_truncate(string* str) {
    string_check_null_string(str);
    size_t start = 0;
    size_t end   = 0;

    while (start <= str->length && (isspace(str->data[start]) || iscntrl(str->data[start]))) {
        start++;
    }

    end = start;

    while (end <= str->length && !(isspace(str->data[end]) || iscntrl(str->data[end]))) {
        end++;
    }

    end--;
    string_mut_to_substring(str, start, end);
}

// Removes leading whitespaces.
void string_mut_truncate_left(string* str) {
    string_check_null_string(str);
    size_t start = 0;

    while (start <= str->length && (isspace(str->data[start]) || iscntrl(str->data[start]))) {
        start++;
    }

    string_mut_to_substring(str, start, str->length - 1);
}

// Removes trailing whitespaces.
void string_mut_truncate_right(string* str) {
    string_check_null_string(str);

    size_t start = 0;
    size_t end   = 0;

    while (start <= str->length && (isspace(str->data[start]) || iscntrl(str->data[start]))) {
        start++;
    }

    end = start;

    while (end <= str->length && !(isspace(str->data[end]) || iscntrl(str->data[end]))) {
        end++;
    }

    end--;
    string_mut_to_substring(str, 0, end);
}

/* ================================================================= */
/* === Read and Write - methods related to user input and output === */
/* ================================================================= */

// Read input from a source (either a file or 'stdin') until it reaches a delimiter.
// Returns a 'string' pointer if it succeeded; otherwise, a 'NULL' pointer.
string* string_read(FILE* source, const char* delimiters) {
    if (feof(source)) return NULL;

    size_t index = 0; 
    size_t size = 2;
    int character;
    char* buffer = malloc(size * sizeof(char));

    if (!buffer) return NULL;

    character = getc(source);

    while (character != EOF && strchr(delimiters, character) == NULL) {
        if (index >= size - 1) {
            size *= 2;
            buffer = realloc(buffer, size * sizeof(char));
            for (size_t i = index; i < size; i++) buffer[i] = '\0';
        }

        buffer[index] = character;
        index++;
        character = getc(source);
    }

    buffer[index] = '\0';
    string* output = new_string(buffer);
    free(buffer);

    return output;
}

// Reads a line from 'stdin' until the first 'new line' character.
string* string_read_line(void) {
    return string_read(stdin, "\n");
}

// Reads characters from 'stdin' until the first space (' ') character.
string* string_read_word(void) {
    return string_read(stdin, " ");
}

// Writes string in the given file. Equivalent to an fprintf() call.
void string_write(FILE* destination, const string* str) {
    string_check_null_string(str);

    if (!destination) {
        string_warning_handling(CSTRING_WARNMSG_FILE_NOT_FOUND);
        return;
    }

    fprintf(destination, "%s", str->data);
}

// Writes string in the given file with an additional new line character based on your operating system.
void string_write_line(FILE* destination, const string* str) {
    string_check_null_string(str);

    if (!destination) {
        string_warning_handling(CSTRING_WARNMSG_FILE_NOT_FOUND);
        return;
    }

    #if defined(_WIN32) || defined(_WIN64)
        fprintf(destination, "%s\r\n", str->data);
    #else
        fprintf(destination, "%s\n", str->data);
    #endif
}

// Prints string to 'stdout'. Equivalent to an unformatted printf() call.
void string_print(const string* str) {
    string_check_null_string(str);
    printf("%s", str->data);
}

// Prints string to 'stdout' in a new line. Equivalent to a puts() call.
void string_print_line(const string* str) {
    string_check_null_string(str);
    puts(str->data);
}

// Creates a formatted string similarly to the 'printf()' function. 
string* string_format(const char* formatting, ...) {
    if (!formatting) {
        string_warning_handling(CSTRING_WARNMSG_FORMATTING_NULL_FORMAT);
        return new_string("");
    }

    va_list arguments01;
    va_list arguments02;

    va_start(arguments01, formatting);
    int buffer_size = vsnprintf(NULL, 0, formatting, arguments01);

    if (buffer_size < 0) {
        string_warning_handling(CSTIRNG_WARNMSG_FORMATTING_INVALID_SIZE);
        va_end(arguments01);
        return new_string("");
    }

    va_end(arguments01);
    va_start(arguments02, formatting);
    char buffer[buffer_size + 1];
    vsnprintf(buffer, buffer_size + 1, formatting, arguments02);
    va_end(arguments02);

    return new_string(buffer);
}

/* ========================================================================= */
/* === Type conversion: converting strings to other primitive data types === */
/* ========================================================================= */

// Converts string to a decimal 'long long' value. Has the synonym 'string_convert_to_int()'.
long long string_convert_to_long(const string* str) {
    string_check_null_string(str);

    #if !(defined(DATASTRUCTS_NO_WARNINGS) || defined(DATASTRUCTS_CSTRING_NO_WARNINGS))
        char* unused_chars;
        long long result = strtoll(str->data, &unused_chars, 10);
        
        if (strcmp(unused_chars, "") != 0) {
            fprintf(stderr, CSTRING_WARNMSG_CONVERSION_IGNORED_CHARS, unused_chars);

        }

        return result;
    #else
        return strtoll(str->data, NULL, 10);
    #endif
}

// Converts string to 'long long' integer of an arbitrary base.
long long string_convert_to_long_base(const string* str, const int base) {
    string_check_null_string(str);
    #if !(defined(DATASTRUCTS_NO_WARNINGS) || defined(DATASTRUCTS_CSTRING_NO_WARNINGS))
        char* unused_chars;
        long long result = strtoll(str->data, &unused_chars, base);
        
        if (strcmp(unused_chars, "") != 0) {
            fprintf(stderr, CSTRING_WARNMSG_CONVERSION_IGNORED_CHARS, unused_chars);

        }

        return result;
    #else
        return strtoll(str->data, NULL, base);
    #endif
}

// Converts string to a decimal 'unsigned long long' value. Has the synonym 'string_convert_to_unsigned_int()'.
unsigned long long string_convert_to_unsigned_long(const string* str) {
    string_check_null_string(str);

    #if !(defined(DATASTRUCTS_NO_WARNINGS) || defined(DATASTRUCTS_CSTRING_NO_WARNINGS))
        char* unused_chars;
        long long result = strtoull(str->data, &unused_chars, 10);
        
        if (strcmp(unused_chars, "") != 0) {
            fprintf(stderr, CSTRING_WARNMSG_CONVERSION_IGNORED_CHARS, unused_chars);

        }

        return result;
    #else
        return strtoull(str->data, NULL, 10);
    #endif
}

// Converts string to 'unsigned long long' integer of an arbitrary base.
unsigned long long string_convert_to_unsigned_long_base(const string* str, const int base) {
    string_check_null_string(str);

    #if !(defined(DATASTRUCTS_NO_WARNINGS) || defined(DATASTRUCTS_CSTRING_NO_WARNINGS))
        char* unused_chars;
        long long result = strtoull(str->data, &unused_chars, base);
        
        if (strcmp(unused_chars, "") != 0) {
            fprintf(stderr, CSTRING_WARNMSG_CONVERSION_IGNORED_CHARS, unused_chars);
        }

        return result;
    #else
        return strtoull(str->data, NULL, base);
    #endif
    return strtoull(str->data, NULL, base);
}

// Converts string to 'float'.
float string_convert_to_float(const string* str) {
    string_check_null_string(str);

    #if !(defined(DATASTRUCTS_NO_WARNINGS) || defined(DATASTRUCTS_CSTRING_NO_WARNINGS))
        char* unused_chars;
        long long result = strtof(str->data, &unused_chars);
        
        if (strcmp(unused_chars, "") != 0) {
            fprintf(stderr, CSTRING_WARNMSG_CONVERSION_IGNORED_CHARS, unused_chars);
        }

        return result;
    #else
        return strtof(str->data, NULL);
    #endif
}

// Converts string to a decimal 'long double' value.
long double string_convert_to_double(const string* str) {
    string_check_null_string(str);

    #if !(defined(DATASTRUCTS_NO_WARNINGS) || defined(DATASTRUCTS_CSTRING_NO_WARNINGS))
        char* unused_chars;
        long long result = strtold(str->data, &unused_chars);
        
        if (strcmp(unused_chars, "") != 0) {
            fprintf(stderr, CSTRING_WARNMSG_CONVERSION_IGNORED_CHARS, unused_chars);
        }

        return result;
    #else
        return strtold(str->data, NULL);
    #endif
}

// Converts string to boolean values. Note: true == True == TRUE == 1 and false == False == FALSE == 0.
bool string_convert_to_bool (const string* str) {
    string_check_null_string(str);
    
    if (strcmp(str->data, "true") == 0 || strcmp(str->data, "True") == 0 || 
        strcmp(str->data, "TRUE") == 0 || strcmp(str->data, "0") != 0)  {
            return true;
    } else return false;
}

// Converts string to 'char'. For longers strings, only the first character is processed. 
char string_convert_to_char (const string* str) {
    string_check_null_string(str);
    return str->data[0];
}
