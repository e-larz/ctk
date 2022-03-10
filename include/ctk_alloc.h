// SPDX-License-Identifier: 0BSD
/*!
 * @file
 * @license{
 * BSD Zero Clause License
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 * }
 *
 * @brief
 * Provide wrappers around standard allocation functions to make them a bit
 * safer by providing predictable behaviors.
 *
 * @details
 * Calls to standard functions `malloc()`, `calloc()`, `realloc()` and
 * `aligned_alloc()` with a size of `0` is implementation-defined.
 * They either have to return `NULL` or a non-zero value that can't be used to
 * access an objet.
 * In order to have a predictable behaviour, wrappers return `NULL` if
 * they are called with a size of `0`.
 *
 * @see
 * @C17{7,22,3}
 *
 * @todo
 * - Add wrapper around `aligned_alloc()`
 */
/*==============================================================================
    GUARD
==============================================================================*/
#ifndef CTK_ALLOC_H_20180303155245
#define CTK_ALLOC_H_20180303155245
/*==============================================================================
    INCLUDE
==============================================================================*/
// C Standard Library
#include <stddef.h> // size_t
/*==============================================================================
    PUBLIC FUNCTION
==============================================================================*/
/*------------------------------------------------------------------------------
    ctk_malloc()
------------------------------------------------------------------------------*/
/**
 * Wrapper around `malloc()` returning `NULL` if \p{size} is `0`.
 *
 * @param[in] size : Number of bytes to allocate.
 *
 * @return
 * - @success: A pointer to the allocated memory.
 * - @failure: `NULL`.
 *
 * @warning
 * - \p{size} must be > `0`.
 *
 * @example{
 *  int * a = ctk_malloc(sizeof(*a)); // Ok
 *  int * b = ctk_malloc(0);          // Erro: b == NULL
 * }
 *
 * @see
 * @C17{7,22,3,4}
 */
void * ctk_malloc(size_t size);
/*------------------------------------------------------------------------------
    ctk_calloc()
------------------------------------------------------------------------------*/
/**
 * Wrapper around `calloc()` returning `NULL` if either \p{num} or \p{size} is
 * `0`.
 *
 * @param[in] num  : Number of objects to allocate.
 * @param[in] size : Size of an object in bytes.
 *
 * @return
 * - @success: A pointer to the allocated memory.
 * - @failure: `NULL`.
 *
 * @warning
 * - \p{num} must be > `0`.
 * - \p{size} must be > `0`.
 *
 * @example{
 *  int * a = ctk_calloc(1, sizeof(*a)); // Ok
 *  int * b = ctk_calloc(0, sizeof(*b)); // Error: b == NULL
 *  int * c = ctk_calloc(sizeof(*c), 0); // Error: c == NULL
 *  int * d = ctk_calloc(0, 0);          // Error: d == NULL
 * }
 *
 * @see
 * @C17{7,22,3,2}
 */
void * ctk_calloc(size_t num, size_t size);
/*------------------------------------------------------------------------------
    ctk_realloc()
------------------------------------------------------------------------------*/
/**
 * Wrapper around `realloc()` returning `NULL` if \p{size} is `0` and setting
 * \p{ptr} to `NULL` if the reallocation succeeded.
 *
 * - Since \p{ptr} is a double pointer, a simple pointer parameter must be
 *   passed as `(void*)&ptr`. Use #ctk_realloc() macro to to pass parameter as
 *   `&ptr`.
 * - #ctk_realloc() macro having the same name, this function must be enclosed
 *   with parenthesis to call it(i.e, `(ctk_realloc)((void*)&ptr)`).
 *
 * @param[in,out] ptr  : Address of the pointer to the memory to reallocate.
 * @param[in]     size : Number of bytes to allocate.
 *
 * @return
 * - @success: A pointer to the reallocated memory.
 * - @failure: `NULL`.
 *
 * @warning
 * - \p{size} must be > `0`.
 *
 * @example{
 *  const size_t size = sizeof(*ptr);
 *  int * ptr = malloc(size);
 *  int * a = (ctk_realloc)((void*)&ptr, size * 2); // Ok: ptr == NULL
 *  a = (ctk_realloc)((void*)&a, size * 3); // Ok
 *  int * b = (ctk_realloc)((void*)&a, 0);  // Error: b == NULL, a is unchanged
 *  int * c = (ctk_realloc)(NULL, 0);       // Error: c == NULL
 *  int * d = (ctk_realloc)(NULL, size);    // Ok: same as malloc(size)
 * }
 *
 * @see
 * @C17{7,22,3,5}
 */
void * ctk_realloc(void ** ptr, size_t size);
/**
 * Macro easing the use of `ctk_realloc()` by removing the need to cast \p{ptr}
 * to `(void*)`.
 *
 * @param[in,out] ptr  : Address of the pointer to the memory to reallocate.
 * @param[in]     size : Number of bytes to allocate.
 *
 * @return
 * - @success: A pointer to the reallocated memory.
 * - @failure: `NULL`.
 *
 * @warning
 * - \p{size} must be > `0`.
 *
 * @example{
 *  const size_t size = sizeof(*ptr);
 *  int * ptr = malloc(size);
 *  int * a = ctk_realloc(&ptr, size * 2); // Ok: ptr == NULL
 *  a = ctk_realloc(&a, size * 3);         // Ok
 *  int * b = ctk_realloc(&a, 0);          // Error: b == NULL, a is unchanged
 *  int * c = ctk_realloc(NULL, 0);        // Error: c == NULL
 *  int * d = ctk_realloc(NULL, size);     // Ok: same as malloc(size)
 * }
 *
 * @see
 * @C17{7,22,3,5}
 */
#define ctk_realloc(ptr, size) \
    (ctk_realloc)((void*)(ptr), (size))
/*------------------------------------------------------------------------------
    ctk_free()
------------------------------------------------------------------------------*/
/**
 * Wrapper around `free()` setting \p{*ptr} to `NULL` after freeing it.
 *
 * - Deallocate memory block allocated with `malloc()`, `calloc()`, `realloc()`
 *   or their wrappers and set \p{*ptr} to `NULL`.
 * - Since \p{ptr} is a double pointer, a simple pointer parameter must be
 *   passed as `(void*)&ptr`. Use #ctk_free() macro to to pass parameter as
 *   `&ptr`.
 * - #ctk_free() macro having the same name, this function must be enclosed with
 *   parenthesis to call it(i.e, `(ctk_free)((void*)&ptr)`).
 *
 * @param[in,out] ptr : Address of the pointer to the memory to deallocate.
 *
 * @return Nothing.
 *
 * @example{
 *  (ctk_free)(NULL);      // Ok
 *  int * a = NULL;
 *  (ctk_free)((void*)&a); // Ok: a == NULL
 *  int * b = malloc(sizeof(*b));
 *  (ctk_free)((void*)&b); // Ok: b == NULL
 * }
 *
 * @see
 * @C17{7,22,3,3}
 */
void ctk_free(void ** ptr);
/**
 * Macro easing the use of `ctk_free()` by removing the need to cast \p{ptr} to
 * `(void*)`.
 *
 * @param[in,out] ptr : Address of the pointer to the memory to deallocate.
 *
 * @return Nothing.
 *
 * @example{
 *  ctk_free(NULL); // Ok
 *  int * a = NULL;
 *  ctk_free(&a);   // Ok: a == NULL
 *  int * b = malloc(sizeof(*b));
 *  ctk_free(&b);   // Ok: b == NULL
 * }
 *
 * @see
 * @C17{7,22,3,3}
 */
#define ctk_free(ptr) \
    (ctk_free)((void*)(ptr))
/*==============================================================================
    GUARD
==============================================================================*/
#endif // CTK_ALLOC_H_20180303155245
