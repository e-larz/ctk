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
 */
/*==============================================================================
    GUARD
==============================================================================*/
#ifndef CTK_ERROR_H_20210628173507
#define CTK_ERROR_H_20210628173507
/*==============================================================================
    INCLUDE
==============================================================================*/
// C Standard Library
#include <stdio.h> // EOF, NULL, fprintf()
/*==============================================================================
    MACRO
==============================================================================*/
/*------------------------------------------------------------------------------
    CTK_ERROR_RET_VAL_IF_MSG()
------------------------------------------------------------------------------*/
/**
 * Print \p{msg} to `stderr` and make the calling fuction return \p{retval} if
 * \p{cond} is true.
 *
 * @param[in] cond   : Condition to be evaluated.
 * @param[in] retval : Value to return.
 * @param[in] msg    : Message to print.
 *
 * @example{
 *   CTK_ERROR_RET_VAL_IF_MSG(buf == NULL, -1, "foo() failed! buf == NULL");
 * }
 */
#define CTK_ERROR_RET_VAL_IF_MSG(cond, retval, msg)                            \
    do {                                                                       \
        if(cond) {                                                             \
            /*fprintf(stderr, "%s() failed! %s\n", __func__, msg);*/           \
            return retval;                                                     \
        }                                                                      \
    } while(0)
/*------------------------------------------------------------------------------
    CTK_ERROR_RET_VAL_IF()
------------------------------------------------------------------------------*/
/**
 * Print an error message to `stderr` and make the calling fuction return
 * \p{retval} if \p{cond} is true.
 *
 * @param[in] cond   : Condition to be evaluated.
 * @param[in] retval : Value to return.
 *
 * @example{
 *   CTK_ERROR_RET_VAL_IF(buf == NULL, -1);
 * }
 */
#define CTK_ERROR_RET_VAL_IF(cond, retval)                                     \
    CTK_ERROR_RET_VAL_IF_MSG(cond, retval, #cond)
/*------------------------------------------------------------------------------
    CTK_ERROR_RET_IF()
------------------------------------------------------------------------------*/
/**
 * Print an error message to `stderr` and make the calling fuction return if
 * \p{cond} is true.
 *
 * @param[in] cond : Condition to be evaluated.
 *
 * @example{
 *   CTK_ERROR_RET_IF(buf == NULL);
 * }
 */
#define CTK_ERROR_RET_IF(cond)                                                 \
    CTK_ERROR_RET_VAL_IF(cond, )
/*------------------------------------------------------------------------------
    CTK_ERROR_RET_NULL_IF()
------------------------------------------------------------------------------*/
/**
 * Print an error message to `stderr` and make the calling fuction return `NULL`
 * if \p{cond} is true.
 *
 * @param[in] cond : Condition to be evaluated.
 *
 * @example{
 *   CTK_ERROR_RET_NULL_IF(buf == NULL);
 * }
 */
#define CTK_ERROR_RET_NULL_IF(cond)                                            \
    CTK_ERROR_RET_VAL_IF(cond, NULL)
/*------------------------------------------------------------------------------
    CTK_ERROR_RET_0_IF()
------------------------------------------------------------------------------*/
/**
 * Print an error message to `stderr` and make the calling fuction return `0` if
 * \p{cond} is true.
 *
 * @param[in] cond : Condition to be evaluated.
 *
 * @example{
 *   CTK_ERROR_RET_0_IF(buf == NULL);
 * }
 */
#define CTK_ERROR_RET_0_IF(cond)                                               \
    CTK_ERROR_RET_VAL_IF(cond, 0)
/*------------------------------------------------------------------------------
    CTK_ERROR_RET_EOF_IF()
------------------------------------------------------------------------------*/
/**
 * Print an error message to `stderr` and make the calling fuction return `EOF`
 * if \p{cond} is true.
 *
 * @param[in] cond : Condition to be evaluated.
 *
 * @example{
 *   CTK_ERROR_RET_EOF_IF(buf == NULL);
 * }
 */
#define CTK_ERROR_RET_EOF_IF(cond)                                             \
    CTK_ERROR_RET_VAL_IF(cond, EOF)
/*------------------------------------------------------------------------------
    CTK_ERROR_RET_FALSE_IF()
------------------------------------------------------------------------------*/
/**
 * Makes the calling fuction return `false` if \p{cond} is true.
 *
 * @param[in] cond : Condition to be evaluated.
 *
 * @example{
 *   CTK_ERROR_RET_FALSE_IF(buf == NULL);
 * }
 */
#define CTK_ERROR_RET_FALSE_IF(cond)                                           \
    CTK_ERROR_RET_VAL_IF(cond, false)
/*==============================================================================
    GUARD
==============================================================================*/
#endif // CTK_ERROR_H_20210628173507
