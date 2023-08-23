#include <stddef.h>

#include "carray.h"

/* ======================================= */
/* ============= Definitions ============= */
/* ======================================= */

struct _array {
    union {
        void*  prim_data;
        void** comp_data;
    };

    size_t capacity;
    size_t size;
    void  (*destructor)(void*);
    bool  (*comparator)(void*, void*);
    void* (*copy)(void*);
};

/* ================================ */
/* === Error handling functions === */
/* ================================ */

// General error handling function.
static void array_error_handling(const char* error_msg, const int error_code) {
    fprintf(stderr, "Error: %d\n%s\n", error_code, error_msg);
    exit(error_code);
}

static void array_check_null(const array* arr) {
    if (!arr) {
        array_error_handling(CARRAY_ERRMSSG_NULL_ARRAY,
                             CARRAY_ERRCODE_NULL_ARRAY);
    }
}

static void array_check_index(const array* arr, const size_t index) {
    if (arr->capacity <= index) {
        delete_array((array*)arr);
        array_error_handling(CARRAY_ERRMSSG_INDEX_OUT_OF_BOUNDS,
                             CARRAY_ERRMSSG_INDEX_OUT_OF_BOUNDS);
    }
}

// General warning handling function.
static void array_warning_handling(const char* warn_msg) {
    fprintf(stderr, "%s\n", warn_msg);
}

/* ========================================= */
/* ======== Constructor, destructor ======== */
/* ========================================= */

// Constructor of 'generic' array. 'destrutcor' and 'copy' are 
array* new_array(const size_t capacity, void (*destructor)(void*), bool (*equality)(void*, void*), void* (*copy)(void*)) {
    if (capacity == 0) {
        array_warning_handling(CARRAY_WARNMSG_EMPTY_CAPACITY);
        return NULL;
    }

    array* arr = calloc(1, sizeof(array));

    if (!arr) array_error_handling(CARRAY_ERRMSSG_MEMORY_ALLOCATION_FAILURE,
                                   CARRAY_ERRCODE_MEMORY_ALLOCATION_FAILURE);
    
    arr->capacity = capacity;
    arr->size = 0;
    arr->destructor = destructor;
    arr->equality = equality;
    arr->copy = copy;

    if (arr->destructor) {
        arr->comp_data = calloc(capacity, sizeof(void*));

        if (!arr->comp_data) {
            free(arr);
            array_error_handling(CARRAY_ERRMSSG_MEMORY_ALLOCATION_FAILURE,
                                 CARRAY_ERRCODE_MEMORY_ALLOCATION_FAILURE);
        }
    } else {
        arr->prim_data = calloc(capacity, sizeof(void));

        if (!arr->prim_data) {
            free(arr);
            array_error_handling(CARRAY_ERRMSSG_MEMORY_ALLOCATION_FAILURE,
                                 CARRAY_ERRCODE_MEMORY_ALLOCATION_FAILURE);
        }
    }

    return arr;
}

// Destructor of array. Standardised template: void func_name(void* obj).
void delete_array (void* obj) {
    if (obj) {
        array* arr = (array*)obj;
        if (arr->destructor) {
            for (size_t i = 0; i < arr->capacity; i++) {
                arr->destructor(arr->comp_data[i]);
            }

            free(arr->comp_data);
        } else {
            free(arr->prim_data);
        }

        free(arr);
        arr = NULL;
        obj = arr;
    }
}

/* ======================================= */
/* =============== Getters =============== */
/* ======================================= */

// Getter of capacity.
size_t array_get_capacity(const array* arr) {
    array_check_null(arr);
    return arr->capacity;
}

// Getter of the number of stored elements.
size_t array_get_size(const array* arr) {
    array_check_null(arr);
    return arr->size;
}

// Returns the element at the specified index. Note the 'void*' return value, hence it can return NULL.
void* array_get_item_at(const array* arr, const size_t index) {
    array_check_null(arr);
    array_check_index(arr, index);

    if (arr->destructor) {
        return arr->comp_data[index];
    } else return arr->prim_data[index];
}

/* ======================================= */
/* ============ Query methods ============ */
/* ======================================= */

// Checks whether the array is empty.
bool array_isempty(const array* arr) {
    array_check_null(arr);
    return arr->size == 0;
}

// Checks whether the array is full.
bool array_isfull(const array* arr) {
    array_check_null(arr);
    return arr->size == arr->capacity;
}

// Checks whether the contents of the two arrays are identical. The order of elements matters.
bool array_areequal(const array* arr1, const array* arr2) {
    array_check_null(arr1);
    array_check_null(arr2);

    if (arr1->destructor != arr2->destructor) return false;

    if (arr1->capacity != arr2->capacity || 
        arr1->size != arr2->size) return false;
    
    for (size_t i = 0; i < arr1->capacity) {
        if (arr1->destructor) {
            if (arr1->equality(arr1->comp_data[i], arr2->comp_data[i])) {
                return false;
            }
        }
    }

    return true;
}

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