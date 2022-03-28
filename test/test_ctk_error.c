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
static void TEST_CTK_ERROR_RET_NEG_1_IF(void);
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
    TEST_CTK_ERROR_RET_NEG_1_IF();
}
/*------------------------------------------------------------------------------
    TEST_CTK_ERROR_RET_VAL_IF_MSG()
------------------------------------------------------------------------------*/
static int test_ctk_error_ret_val_if_msg(_Bool cond, const char * const msg)
{
    if(msg){}
    CTK_ERROR_RET_VAL_IF_MSG(cond, 0, msg);
    return 1;
}
static void TEST_CTK_ERROR_RET_VAL_IF_MSG(void)
{
    assert(test_ctk_error_ret_val_if_msg(true, "Returning 0")  == 0);
    assert(test_ctk_error_ret_val_if_msg(false, "Returning 1") == 1);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_CTK_ERROR_RET_VAL_IF()
------------------------------------------------------------------------------*/
static int test_ctk_error_ret_val_if(_Bool cond)
{
    CTK_ERROR_RET_VAL_IF(cond, 0);
    return 1;
}
static void TEST_CTK_ERROR_RET_VAL_IF(void)
{
    assert(test_ctk_error_ret_val_if(true)  == 0);
    assert(test_ctk_error_ret_val_if(false) == 1);
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
static void * test_ctk_error_ret_null_if(_Bool cond)
{
    CTK_ERROR_RET_NULL_IF(cond);
    return &(int){1};
}
static void TEST_CTK_ERROR_RET_NULL_IF(void)
{
    assert(test_ctk_error_ret_null_if(true)  == NULL);
    assert(test_ctk_error_ret_null_if(false) != NULL);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_CTK_ERROR_RET_0_IF()
------------------------------------------------------------------------------*/
static int test_ctk_error_ret_0_if(_Bool cond)
{
    CTK_ERROR_RET_0_IF(cond);
    return 1;
}
static void TEST_CTK_ERROR_RET_0_IF(void)
{
    assert(test_ctk_error_ret_0_if(true)  == 0);
    assert(test_ctk_error_ret_0_if(false) != 0);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_CTK_ERROR_RET_EOF_IF()
------------------------------------------------------------------------------*/
static int test_ctk_error_ret_eof_if(_Bool cond)
{
    CTK_ERROR_RET_EOF_IF(cond);
    return 1;
}
static void TEST_CTK_ERROR_RET_EOF_IF(void)
{
    assert(test_ctk_error_ret_eof_if(true)  == EOF);
    assert(test_ctk_error_ret_eof_if(false) != EOF);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_CTK_ERROR_RET_FALSE_IF()
------------------------------------------------------------------------------*/
static _Bool test_ctk_error_ret_false_if(_Bool cond)
{
    CTK_ERROR_RET_FALSE_IF(cond);
    return true;
}
static void TEST_CTK_ERROR_RET_FALSE_IF(void)
{
    assert(test_ctk_error_ret_false_if(true)  == false);
    assert(test_ctk_error_ret_false_if(false) != false);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_CTK_ERROR_RET_NEG_1_IF()
------------------------------------------------------------------------------*/
static int test_ctk_error_ret_neg_1_if(_Bool cond)
{
    CTK_ERROR_RET_NEG_1_IF(cond);
    return 0;
}
static void TEST_CTK_ERROR_RET_NEG_1_IF(void)
{
    assert(test_ctk_error_ret_neg_1_if(true)  == -1);
    assert(test_ctk_error_ret_neg_1_if(false) != -1);
    printf("\t%s: OK\n", __func__);
}
