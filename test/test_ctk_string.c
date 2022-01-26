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
#include "test_ctk_string.h"
// The API to test
#include "ctk_string.h"
// C Standard Library
#include <assert.h>
#include <errno.h>
#include <stdio.h>  // printf()
#include <string.h> // strerror(), strcmp()
/*==============================================================================
    MACRO
==============================================================================*/
/*==============================================================================
    FUNCTION DECLARATION
==============================================================================*/
static void TEST_ctk_strerror_r(void);
/*==============================================================================
    FUNCTION DEFINITION
==============================================================================*/
/*------------------------------------------------------------------------------
    TEST_ctk_string()
------------------------------------------------------------------------------*/
void TEST_ctk_string(void)
{
    printf("%s:\n", __func__);
    TEST_ctk_strerror_r();
}
/*------------------------------------------------------------------------------
    TEST_ctk_strerror_r()
------------------------------------------------------------------------------*/
static void TEST_ctk_strerror_r(void)
{
    char error[CTK_STRING_ERR_LENGTH] = {0};
    assert(ctk_strerror_r(0, error, CTK_STRING_ERR_LENGTH) == 0);
    assert(strcmp(error, strerror(0)) == 0);
    assert(ctk_strerror_r(EDOM, error, CTK_STRING_ERR_LENGTH) == 0);
    assert(strcmp(error, strerror(EDOM)) == 0);
    assert(ctk_strerror_r(EILSEQ, error, CTK_STRING_ERR_LENGTH) == 0);
    assert(strcmp(error, strerror(EILSEQ)) == 0);
    assert(ctk_strerror_r(ERANGE, error, CTK_STRING_ERR_LENGTH) == 0);
    assert(strcmp(error, strerror(ERANGE)) == 0);
    assert(ctk_strerror_r(-1, error, CTK_STRING_ERR_LENGTH) == EINVAL);
    assert(strcmp(error, strerror(-1)) == 0);
    assert(ctk_strerror_r(0, NULL, CTK_STRING_ERR_LENGTH) == EINVAL);
    assert(ctk_strerror_r(0, error, 0) == ERANGE);
    printf("\t%s: OK\n", __func__);
}
