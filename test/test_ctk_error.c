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
 *
 * @todo
 * - Find a way to test `CTK_ERROR_RET_IF()`.
 */
/*==============================================================================
    INCLUDE
==============================================================================*/
// Own header
#include "test_ctk_error.h"
// The API to test
#include "ctk_error.h"
// C Standard Library
#include <assert.h>
#include <stdbool.h>
#include <stdio.h> // EOF, NULL, printf()
/*==============================================================================
    FUNCTION DECLARATION
==============================================================================*/
static void TEST_CTK_ERROR_RET_VAL_IF_MSG(void);
static void TEST_CTK_ERROR_RET_VAL_IF(void);
//static void TEST_CTK_ERROR_RET_IF(void);
static void TEST_CTK_ERROR_RET_NULL_IF(void);
static void TEST_CTK_ERROR_RET_0_IF(void);
static void TEST_CTK_ERROR_RET_EOF_IF(void);
static void TEST_CTK_ERROR_RET_FALSE_IF(void);
/*==============================================================================
    FUNCTION DEFINITION
==============================================================================*/
/*------------------------------------------------------------------------------
    TEST_ctk_error()
------------------------------------------------------------------------------*/
void TEST_ctk_error(void)
{
    printf("%s:\n", __func__);
    TEST_CTK_ERROR_RET_VAL_IF_MSG();
    TEST_CTK_ERROR_RET_VAL_IF();
    //TEST_CTK_ERROR_RET_IF();
    TEST_CTK_ERROR_RET_NULL_IF();
    TEST_CTK_ERROR_RET_0_IF();
    TEST_CTK_ERROR_RET_EOF_IF();
    TEST_CTK_ERROR_RET_FALSE_IF();
}
/*------------------------------------------------------------------------------
    TEST_CTK_ERROR_RET_VAL_IF_MSG()
------------------------------------------------------------------------------*/
static int test_ctk_error_ret_val_if_msg(int x, const char * const msg)
{
    if(msg){}
    CTK_ERROR_RET_VAL_IF_MSG(x == 0, 0, msg);
    return 1;
}
static void TEST_CTK_ERROR_RET_VAL_IF_MSG(void)
{
    assert(test_ctk_error_ret_val_if_msg(0, "Returning 0") == 0);
    assert(test_ctk_error_ret_val_if_msg(1, "Returning 1") == 1);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_CTK_ERROR_RET_VAL_IF()
------------------------------------------------------------------------------*/
static int test_ctk_error_ret_val_if(int x)
{
    CTK_ERROR_RET_VAL_IF(x == 0, 0);
    return 1;
}
static void TEST_CTK_ERROR_RET_VAL_IF(void)
{
    assert(test_ctk_error_ret_val_if(0) == 0);
    assert(test_ctk_error_ret_val_if(1) == 1);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_CTK_ERROR_RET_IF()
------------------------------------------------------------------------------*/
/*static void test_ctk_error_ret_if(int x, const char * const msg)
{
    CTK_ERROR_RET_IF(x == 0);
    return -1;
}
static void TEST_CTK_ERROR_RET_IF(void)
{
    assert(test_ctk_error_ret_if(0, "Returning 1"));
    printf("\t%s: OK\n", __func__);
}*/
/*------------------------------------------------------------------------------
    TEST_CTK_ERROR_RET_NULL_IF()
------------------------------------------------------------------------------*/
static void * test_ctk_error_ret_null_if(int x)
{
    CTK_ERROR_RET_NULL_IF(x == 0);
    return &(int){1};
}
static void TEST_CTK_ERROR_RET_NULL_IF(void)
{
    assert(test_ctk_error_ret_null_if(0) == NULL);
    assert(test_ctk_error_ret_null_if(1) != NULL);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_CTK_ERROR_RET_0_IF()
------------------------------------------------------------------------------*/
static int test_ctk_error_ret_0_if(int x)
{
    CTK_ERROR_RET_0_IF(x == 0);
    return 1;
}
static void TEST_CTK_ERROR_RET_0_IF(void)
{
    assert(test_ctk_error_ret_0_if(0) == 0);
    assert(test_ctk_error_ret_0_if(1) != 0);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_CTK_ERROR_RET_EOF_IF()
------------------------------------------------------------------------------*/
static int test_ctk_error_ret_eof_if(int x)
{
    CTK_ERROR_RET_EOF_IF(x == 0);
    return 1;
}
static void TEST_CTK_ERROR_RET_EOF_IF(void)
{
    assert(test_ctk_error_ret_eof_if(0) == EOF);
    assert(test_ctk_error_ret_eof_if(1) != EOF);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_CTK_ERROR_RET_EOF_IF()
------------------------------------------------------------------------------*/
static _Bool test_ctk_error_ret_false_if(int x)
{
    CTK_ERROR_RET_FALSE_IF(x == 0);
    return true;
}
static void TEST_CTK_ERROR_RET_FALSE_IF(void)
{
    assert(test_ctk_error_ret_false_if(0) == false);
    assert(test_ctk_error_ret_false_if(1) != false);
    printf("\t%s: OK\n", __func__);
}
