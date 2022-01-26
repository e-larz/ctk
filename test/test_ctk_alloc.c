// SPDX-License-Identifier: 0BSD
/*!
 * @file
 * @date 23.01.2022
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
 */
/*==============================================================================
    INCLUDE
==============================================================================*/
// Own header
#include "test_ctk_alloc.h"
// The API to test
#include "ctk_alloc.h"
// C Standard Library
#include <assert.h>
#include <stdio.h>  // printf()
#include <stdlib.h> // malloc(), free()
/*==============================================================================
    MACRO
==============================================================================*/
#define CREATE(ptr, size) \
    int * (ptr) = malloc(size); \
    assert((ptr) != NULL)

#define CREATE_SET(ptr, size, data) \
    CREATE((ptr), (size)); \
    *(ptr) = (data)

#define REALLOC(ptr, size) \
    FREE(ptr); \
    (ptr) = malloc(size); \
    assert((ptr) != NULL)

#define REALLOC_SET(ptr, size, data) \
    REALLOC((ptr), (size)); \
    *(ptr) = (data)

#define FREE(ptr) \
    free(ptr); (ptr) = NULL
/*==============================================================================
    FUNCTION DECLARATION
==============================================================================*/
static void TEST_ctk_malloc(void);
static void TEST_ctk_calloc(void);
static void TEST_ctk_realloc(void);
static void TEST_ctk_realloc_macro(void);
static void TEST_ctk_free(void);
static void TEST_ctk_free_macro(void);
/*==============================================================================
    FUNCTION DEFINITION
==============================================================================*/
/*------------------------------------------------------------------------------
    TEST_ctk_alloc()
------------------------------------------------------------------------------*/
void TEST_ctk_alloc(void)
{
    printf("%s:\n", __func__);
    TEST_ctk_malloc();
    TEST_ctk_calloc();
    TEST_ctk_realloc();
    TEST_ctk_realloc_macro();
    TEST_ctk_free();
    TEST_ctk_free_macro();
}
/*------------------------------------------------------------------------------
    TEST_ctk_malloc()
------------------------------------------------------------------------------*/
static void TEST_ctk_malloc(void)
{
    // size = 0
    int * x = ctk_malloc(0);
    assert(x == NULL);
    // size > 0
    x = ctk_malloc(sizeof(*x));
    assert(x != NULL);
    FREE(x);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_ctk_calloc()
------------------------------------------------------------------------------*/
static void TEST_ctk_calloc(void)
{
    // num > 0 && size > 0
    int * x = ctk_calloc(1, sizeof(*x));
    assert(x != NULL);
    assert(*x == 0);
    FREE(x);
    // size > 0 && num > 0
    x = ctk_calloc(sizeof(*x), 1);
    assert(x != NULL);
    assert(*x == 0);
    FREE(x);
    // num = 0 && size > 0
    x = ctk_calloc(0, sizeof(*x));
    assert(x == NULL);
    // size > 0 && num = 0
    x = ctk_calloc(sizeof(*x), 0);
    assert(x == NULL);
    // num = 0 && size = 0
    x = ctk_calloc(0, 0);
    assert(x == NULL);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_ctk_realloc()
------------------------------------------------------------------------------*/
static void TEST_ctk_realloc(void)
{
    const size_t x_size = 2 * sizeof(int);
    const int data = 0xCAFE;
    // ptr != NULL && size = 0
    CREATE_SET(x, x_size, data);
    int * xr = (ctk_realloc)((void*)&x, 0);
    assert(xr == NULL);
    assert(x != NULL);
    assert(*x == data);
    // ptr != NULL && 0 < size < x_size
    REALLOC_SET(x, x_size, data);
    xr = (ctk_realloc)((void*)&x, x_size/2);
    assert(xr != NULL);
    assert(*xr == data);
    assert(x == NULL);
    FREE(xr);
    // ptr != NULL && 0 < size = x_size
    REALLOC_SET(x, x_size, data);
    xr = (ctk_realloc)((void*)&x, x_size);
    assert(xr != NULL);
    assert(*xr == data);
    assert(x == NULL);
    FREE(xr);
    // ptr != NULL && 0 < x_size < size
    REALLOC_SET(x, x_size, data);
    xr = (ctk_realloc)((void*)&x, 2 * x_size);
    assert(xr != NULL);
    assert(*xr == data);
    assert(x == NULL);
    // ptr != NULL && ptr = xr
    xr = (ctk_realloc)((void*)&xr, x_size);
    assert(xr != NULL);
    assert(*xr == data);
    FREE(xr);
    // ptr == NULL && size = 0
    xr = (ctk_realloc)(NULL, 0);
    assert(xr == NULL);
    // ptr == NULL && size > 0
    xr = (ctk_realloc)(NULL, x_size);
    assert(xr != NULL);
    FREE(xr);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_ctk_realloc_macro()
------------------------------------------------------------------------------*/
static void TEST_ctk_realloc_macro(void)
{
    const size_t x_size = 2 * sizeof(int);
    const int data = 0xCAFE;
    // ptr != NULL && size = 0
    CREATE_SET(x, x_size, data);
    int * xr = ctk_realloc(&x, 0);
    assert(xr == NULL);
    assert(x != NULL);
    assert(*x == data);
    // ptr != NULL && 0 < size < x_size
    REALLOC_SET(x, x_size, data);
    xr = ctk_realloc(&x, x_size/2);
    assert(xr != NULL);
    assert(*xr == data);
    assert(x == NULL);
    FREE(xr);
    // ptr != NULL && 0 < size = x_size
    REALLOC_SET(x, x_size, data);
    xr = ctk_realloc(&x, x_size);
    assert(xr != NULL);
    assert(*xr == data);
    assert(x == NULL);
    FREE(xr);
    // ptr != NULL && 0 < x_size < size
    REALLOC_SET(x, x_size, data);
    xr = ctk_realloc(&x, 2 * x_size);
    assert(xr != NULL);
    assert(*xr == data);
    assert(x == NULL);
    // ptr != NULL && ptr = xr
    xr = ctk_realloc(&xr, x_size);
    assert(xr != NULL);
    assert(*xr == data);
    FREE(xr);
    // ptr == NULL && size = 0
    xr = ctk_realloc(NULL, 0);
    assert(xr == NULL);
    // ptr == NULL && size > 0
    xr = ctk_realloc(NULL, x_size);
    assert(xr != NULL);
    FREE(xr);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_ctk_free()
------------------------------------------------------------------------------*/
static void TEST_ctk_free(void)
{
    (ctk_free)(NULL);
    // ptr = NULL
    int * ptr = NULL;
    (ctk_free)((void*)&ptr);
    assert(ptr == NULL);
    // ptr != NULL
    REALLOC(ptr, sizeof(*ptr));
    (ctk_free)((void*)&ptr);
    assert(ptr == NULL);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_ctk_free_macro()
------------------------------------------------------------------------------*/
static void TEST_ctk_free_macro(void)
{
    // ptr = NULL
    int * ptr = NULL;
    ctk_free(ptr);
    assert(ptr == NULL);
    // ptr != NULL
    REALLOC(ptr, sizeof(*ptr));
    ctk_free(&ptr);
    assert(ptr == NULL);
    printf("\t%s: OK\n", __func__);
}
