#ifndef CSTRING_H
#define CSTRING_H

#include <stddef.h>
#include <stdbool.h>

/* ======================================= */
/* ============= Definitions ============= */
/* ======================================= */

// Type definition of 'string' type.
typedef struct _string string;

// Alternative 'keyword' for type 'string'.
typedef string String;

// Alternative 'keyword' for type 'string'.
typedef string string_t;

/* ======================================= */
/* ======== Constructor, destructor ====== */
/* ======================================= */

// Constructor of string.
string* new_string    (const char* source);

// Destructor of string. Standardised template: void func_name(void* obj).
void    delete_string (void* str);

/* ======================================= */
/* =============== Getters =============== */
/* ======================================= */

// Getter of length of string.
size_t      string_get_length  (const string* str);

// Getter of traditional C-style string (i.e. character array). Individual characters are not directly modifiable.
const char* string_get_data    (const string* str);

// Returns the character at the specified index.
char        string_get_char_at (const string* str, const size_t index);

/* ======================================= */
/* ============ Query methods ============ */
/* ======================================= */

// Checks whether the string's last character is the null terminator character.
bool  string_isvalid         (const string* str);

// Checks whether the string is empty, meaning that either the length is 0 or all the characters are whitespaces or control characters.
bool  string_isempty         (const string* str);

// Compares two strings. Returns 0 is they're equal. Return a negative integer if str1 < str2. Returns a positive integer if str1 > str2.
// Standardised template: int func_name(const void* obj1, const void* obj2)
int   string_compare         (const void* str1, const void* str2);

// Checks whether two strings are equal.
bool  string_areequal        (const void* str1, const void* str2);

// Checks whether 'sub_str' is a substring of 'str'. Argument 'str' is a standard C-style character array.
bool  string_issubstring     (const string* str, const char* sub_str);

// Checks whether 'sub_str' is a substring of 'str'. Argument 'str' is of type 'string'.
bool  string_issubstring_str (const string* str, const string* sub_str);

// Checks whether the given character is present in the string. Often used to check for delimiters in a text.
bool  string_contains_char   (const string* str, const char character);

// Checks whether 'prefix' occurs in 'str'. Argument 'prefix' is a standard C-style character array.
bool  string_isprefix        (const string* str, const char* prefix);

// Checks whether 'prefix' occurs in 'str'. Argument 'prefix' is of type 'string'.
bool  string_isprefix_str    (const string* str, const string* prefix);

// Checks whether 'suffix' occurs in 'str'. Argument 'suffix' is a standard C-style character array.
bool  string_issuffix        (const string* str, const char* suffix);

// Checks whether 'suffix' occurs in 'str'. Argument 'suffix' is of type 'string'.
bool  string_issuffix_str    (const string* str, const string* suffix);

// Returns a pointer to the first occurrence of 'character' in the string. Identical to 'strchr()' but for 'string' type.
char* string_find_first_char (const string* str, char character);

// Returns a pointer to the last occurrence of 'character' in the string. Identical to 'strrchr()' but for 'string' type.
char* string_find_last_char  (const string* str, char character);

/* ======================================================================================= */
/* === Immutative methods: methods that return a modified copy of the oringinal string === */
/* ======================================================================================= */

// Returns an exact copy of the original string.
string* string_copy            (const string* str);

// Concatenates the two strings and returns it as a new object.
string* string_concatenate     (const string* str1, const string* str2);

// Creates a substring based on the indices and returns it as a new object.
string* string_substring       (const string* str, const size_t start_index, const size_t end_index);

// Returns a new string where
string* string_to_lower_case   (const string* str);

// Returns a new string where all the characters are upper-case letters.
string* string_to_upper_case   (const string* str);

// Returns a new string where the first character is capitalised.
string* string_capitalise      (const string* str);

// Returns a new string where leading and trailing whitespaces are removed.
string* string_truncate        (const string* str);

// Returns a new string where leading whitespaces are removed.
string* string_truncate_left   (const string* str);

// Returns a new string where trailing whitespaces are removed.
string* string_truncate_right  (const string* str);

/* ======================================================================================= */
/* === Mutative methods: methods that modify the internal state of the original string === */
/* ======================================================================================= */

// Replaces the character at the givn index. Prevents you from replacing the null terminator and inserting another extra one.
void string_mut_char_at        (string* str, char character, const size_t index);

// Overwrites the original contents of the string.
void string_mut_overwrite      (string* str, const char* new_str);

// Concatenates 'str2' to the end of 'str1'. 'str2' is left unaffected.
void string_mut_concatenate    (string* str1, const string* str2);

// Creates a substring based on the indices and returns it as a new object.
void string_mut_to_substring   (string* str, const size_t start_index, const size_t end_index);

// Converts all upper-case letters to lower-case letters.
void string_mut_to_lower_case  (string* str);

// Converts all lower-caseletters to upper-case letters.
void string_mut_to_upper_case  (string* str);

// Capitalises the first character of the string.
void string_mut_capitalise     (string* str);

// Removes leading and trailing whitespaces.
void string_mut_truncate       (string* str);

// Removes leading whitespaces.
void string_mut_truncate_left  (string* str);

// Removes trailing whitespaces.
void string_mut_truncate_right (string* str);

/* ================================================================= */
/* === Read and Write - methods related to user input and output === */
/* ================================================================= */

// Read input from a source (either a file or 'stdin') until it reaches a delimiter.
// Returns a 'string' pointer if it succeeded; otherwise, a 'NULL' pointer.
string* string_read        (FILE* source, const char* delimiters);

// Reads a line from 'stdin' until the first 'new line' character.
string* string_read_line   (void);

// Reads characters from 'stdin' until the first space (' ') character.
string* string_read_word   (void);

// Writes string in the given file. Equivalent to an fprintf() call.
void    string_write       (FILE* destination, const string* str);

// Writes string in the given file with an additional new line character based on your operating system.
void    string_write_line  (FILE* destination, const string* str);

// Prints string to 'stdout'. Equivalent to an unformatted printf() call.
void    string_print       (const string* str);

// Prints string to 'stdout' in a new line. Equivalent to a puts() call.
void    string_print_line  (const string* str);

/* ========================================================================= */
/* === Type conversion: converting strings to other primitive data types === */
/* ========================================================================= */

// Converts string to a decimal 'long long' value. Has the synonym 'string_convert_to_int()'.
long long string_convert_to_long       (const string* str);

// Converts string to 'long long' integer of an arbitrary base.
long long string_convert_to_long_base  (const string* str, const int base);

// A synonym for converting strings to integers.
#define string_convert_to_int (int)string_convert_to_long

// Converts string to a decimal 'unsigned long long' value. Has the synonym 'string_convert_to_unsigned_int()'.
unsigned long long string_convert_to_unsigned_long       (const string* str);

// Converts string to 'unsigned long long' integer of an arbitrary base.
unsigned long long string_convert_to_unsigned_long_base  (const string* str, const int base);

// A synonym for converting strings to unsigned integers.
#define string_convert_to_unsigned_int (unsigned int)string_convert_to_unsigned_long

// Converts string to 'float'.
float        string_convert_to_float          (const string* str);

// Converts string to a decimal 'long double' value.
long double  string_convert_to_double         (const string* str);

// Converts string to boolean values. Note: true == True == TRUE == 1 and false == False == FALSE == 0.
bool    string_convert_to_bool (const string* str);

// Converts string to 'char'. For longers strings, only the first character is processed. 
char    string_convert_to_char (const string* str);

// Number -> String

// Converts 'long long' of an arbitrary base to string.
string* string_convert_long_base            (const long long integer, const int base);

// Converts decimal 'long long' to string.
string* string_convert_long                 (const long long integer);

// Synonym for the function 'string_convert_long()'.
#define string_convert_int string_convert_long

// Converts 'unsigned long long' of an arbitrary base to string.
string* string_convert_unsigned_long_base   (const unsigned long long integer, const int base);

// Converts decimal 'unsigned long long' to string.
string* string_convert_unsigned_long        (const unsigned long long integer);

// Converts decimal 'long double' to string.
string* string_convert_double               (const long double real);

// Converts 'bool' to string.
string* string_convert_bool                 (const bool boolean);

// Creates a formatted string similarly to the 'printf()' function. 
string* string_format          (const char* formatting, ...);

/* ===================================================================== */
/* === String splitting: converting from and to arrays and, or lists === */
/* ===================================================================== */

/* ====================================== */
/* ========== Warning messages ========== */
/* ====================================== */

#define CSTRING_WARNMSG_SUBSTRING_CHAR_NULL "Warning: substring of type 'const char*' is NULL, which is invalid. Returns false."
#define CSTRING_WARNMSG_SUBSTRING_TOO_LONG  "Warning: substring is longer than the string itself. Returns false."
#define CSTIRNG_WARNMSG_PREFIX_TOO_LONG     "Warning: prefix is longer than the string itself. Returns false."
#define CSTRING_WARNMSG_SUFFIX_TOO_LONG     "Warning: suffix is longer than the string itself. Returns false."
#define CSTRING_WARNMSG_FILE_NOT_FOUND      "Warning: file does not exist. Writing string to file aborted."
#define CSTRING_WARNMSG_OVERWRITE_TO_NULL   "Warning: string cannot be overwritten by 'const char*' array of value NULL. No changes have been made."
#define CSTRING_WARNMSG_CONVERSION_IGNORED_CHARS "Warning: the following characters were ignored during conversion: \"%s\""
// #define CSTRING_WARNMSG_BLABLABLA "Warning: sample warning."

/* ====================================== */
/* === Error messages and error codes === */
/* ====================================== */

#define CSTRING_ERRMSSG_NULL_STRING "Error: string is null pointer."
#define CSTRING_ERRCODE_NULL_STRING -1

#define CSTRING_ERRMSSG_INDEX_OUT_OF_BOUNDS "Error: index out of bounds."
#define CSTRING_ERRCODE_INDEX_OUT_OF_BOUNDS -2

#define CSTRING_ERRMSSG_MEMORY_ALLOCATION_FAILURE "Error: memory allocation failed."
#define CSTRING_ERRCODE_MEMORY_ALLOCATION_FAILURE -3

#endif // CSTRING_H
