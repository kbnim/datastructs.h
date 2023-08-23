#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdbool.h>

/* ======================================= */
/* ============= Definitions ============= */
/* ======================================= */

/*
The 'array' type is the closest data structure to a traditional C-style array, with the added benefit storing its capacity at runtime.
Therefore, it has the following characteristics:
    - not resizeable
    - mergeing and splitting operations are not available
    - stores elements of one type, which are ensured by the destructor, equality and copy functions
Similar in nature to std::array in C++.
*/

// Type definition of 'string' type.
typedef struct _array array;

// Alternative 'keyword' for type 'string'.
typedef array Array;

// Alternative 'keyword' for type 'string'.
typedef array array_t;

/* ========================================= */
/* ======== Constructor, destructor ======== */
/* ========================================= */

// Constructor of 'generic' array. 'destrutcor' and 'copy' are 
array* new_array    (const size_t capacity, void (*destructor)(void*), bool (*equality)(void*, void*), void* (*copy)(void*));

// Destructor of array. Standardised template: void func_name(void* obj).
void   delete_array (void* obj);

/* ======================================= */
/* =============== Getters =============== */
/* ======================================= */

// Getter of capacity.
size_t array_get_capacity (const array* arr);

// Getter of the number of stored elements.
size_t array_get_size     (const array* arr);

// Returns the element at the specified index. Note the 'void*' return value, hence it can return NULL.
void   array_get_item_at  (const array* arr, const size_t index);

// Special macro to facilitate the casting of primitive types when retrieving them from the array.
#define CAST(type, pointer) (*(type*)(pointer))

/* ======================================= */
/* ============ Query methods ============ */
/* ======================================= */

// Checks whether the array is empty.
bool array_isempty  (const array* arr);

// Checks whether the array is full.
bool array_isfull   (const array* arr);

// Checks whether the contents of the two arrays are identical. The order of elements matters.
bool array_areequal (const array* arr1, const array* arr2);

/* ======================================= */
/* =========== General methods =========== */ 
/* ======================================= */

// Inserts 'obj' where the 'index' is NULL and overwrites the existing object.
void  array_insert_item_to (const array* arr, const size_t index, void* obj);

// Removes the item found at the 'index', resets the index to NULL and returns the object.
void* array_remove_item_at (const array* arr, const size_t index);

// Deletes the item found at the 'index', resets the index to NULL. Returns nothing.
void  array_delete_item_at (const array* arr, const size_t index);

// Creates a copy of the object at the specified 'index'.
void* array_copy_item_from (const array* arr, const size_t index);

/* ====================================================== */
/* =========== Immutative array manipulations =========== */ 
/* ====================================================== */

// Copies the entire contents of 'arr'.
array* array_copy     (const array* arr);

// Creates a subarray based on the indices.
array* array_subarray (const array* arr, const size_t start_index, const size_t end_index);

/* ====================================================== */
/* ============ Mutative array manipulations ============ */ 
/* ====================================================== */

// Erases all the elements of the array, resulting in an empty one.
void array_mut_clean (array* arr);

// Swaps the contents of two arrays storing the same amount of elements and having the same destructor, equality and copy functions.
void array_mut_swap  (array* old_arr, array* new_arr);

/* ====================================== */
/* ========== Warning messages ========== */
/* ====================================== */

#define CARRAY_WARNMSG_EMPTY_CAPACITY "Warning: capacity cannot be 0."
// #define CARRAY_WARNMSG_BLABLABLA "Warning: blablabla"

/* ====================================== */
/* === Error messages and error codes === */
/* ====================================== */

#define CARRAY_ERRMSSG_NULL_ARRAY "Error: array is a null pointer."
#define CARRAY_ERRCODE_NULL_ARRAY -1

#define CARRAY_ERRMSSG_MEMORY_ALLOCATION_FAILURE "Error: memory allocation failed."
#define CARRAY_ERRCODE_MEMORY_ALLOCATION_FAILURE -2

#define CARRAY_ERRMSSG_INDEX_OUT_OF_BOUNDS "Error: index out of bounds."
#define CARRAY_ERRCODE_INDEX_OUT_OF_BOUNDS -3

#define CARRAY_ERRMSSG_BLABLABLA "Error: blablabla"
#define CARRAY_ERRCODE_BLABLABLA -4

#endif // ARRAY_H