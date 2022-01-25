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
 */
/*==============================================================================
    INCLUDE
==============================================================================*/
// Own header
#include "ctk_alloc.h"
// C Standard Library
#include <assert.h>
#include <stdio.h>  // fputs()
#include <stdlib.h> // calloc(), free(), malloc(), realloc(), size_t, NULL
// Internal
#include "ctk_error.h"
/*==============================================================================
    PUBLIC FUNCTION DEFINITION
==============================================================================*/
/*------------------------------------------------------------------------------
    ctk_malloc()
------------------------------------------------------------------------------*/
void * ctk_malloc(const size_t size)
{
    CTK_ERROR_RET_NULL_IF(size == 0);
    void * const mem = malloc(size);
    /*if(mem == NULL) {
        fputs("malloc() failed!\n", stderr);
    }*/
    return mem;
}
/*------------------------------------------------------------------------------
    ctk_calloc()
------------------------------------------------------------------------------*/
void * ctk_calloc(const size_t num, const size_t size)
{
    CTK_ERROR_RET_NULL_IF(num == 0);
    CTK_ERROR_RET_NULL_IF(size == 0);
    void * const mem = calloc(num, size);
    /*if(mem == NULL) {
        fputs("calloc() failed!\n", stderr);
    }*/
    return mem;
}
/*------------------------------------------------------------------------------
    ctk_realloc()
------------------------------------------------------------------------------*/
void * ctk_realloc(void * const ptr, const size_t size)
{
    CTK_ERROR_RET_NULL_IF(size == 0);
    void * const mem = realloc(ptr, size);
    /*if(mem == NULL) {
        fputs("realloc() failed!\n", stderr);
    }*/
    return mem;
}
/*------------------------------------------------------------------------------
    ctk_free()
------------------------------------------------------------------------------*/
void (ctk_free)(void ** const ptr)
{
    // free(NULL) is a well-defined behaviour, therefore we only need to ensure
    // we can dereference `ptr`.
    CTK_ERROR_RET_IF(ptr == NULL);
    free(*ptr);
    *ptr = NULL;
}
