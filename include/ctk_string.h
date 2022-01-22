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
 * Provide string related functions.
 */
/*==============================================================================
    GUARD
==============================================================================*/
#ifndef CTK_STRING_H_20210627022855
#define CTK_STRING_H_20210627022855
/*==============================================================================
    INCLUDE
==============================================================================*/
// C Standard Library
#include <stddef.h> // size_t
/*==============================================================================
    DEFINE
==============================================================================*/
/**
 * Size of a buffer big enough to contain an error string returned by
 * ctk_strerror_r().
 *
 * - The longest error message on Linux is 49 characters(not including the null
 *   terminator) for the English language but other languages could take more
 *   space, especially those using more than one byte for a letter.
 * - `1024` was used as the internal buffer size for `strerror()` in glibc so it
 *   should be good enough.
 */
#define CTK_STRING_ERR_LENGTH 1024
/*==============================================================================
    PUBLIC FUNCTION
==============================================================================*/
/*------------------------------------------------------------------------------
    ctk_strerror_r()
------------------------------------------------------------------------------*/
/**
 * Store the string corresponding to an error number into a user-provided
 * buffer.
 *
 * - Reentrant version of `strerror()`.
 * - Functionally equivalent to POSIX `strerror_r()`.
 * - If the compiler supports the C11 Annex K, `strerrorlen_s()` can be used to
 *   get the right length for the buffer, otherwise there is no standard/POSIX
 *   way to get it.
 * - #CTK_STRING_ERR_LENGTH can be used if space is not a huge priority.
 *
 * @param[in]  errnum : Error number.
 * @param[out] result : Buffer where the string will be stored.
 * @param[in]  length : Length of the result buffer.
 *
 * @return
 * - @success: `0`.
 * - @failure: A non-zero error number.
 *
 * @warning
 * - \p{errnum} must be a valid error number.
 * - \p{result} must not be `NULL`.
 * - \p{length} must be >= to the length of the error string.
 *
 * @see
 * - https://en.cppreference.com/w/c/string/byte/strerror
 * - https://pubs.opengroup.org/onlinepubs/9699919799/functions/strerror.html
 */
int ctk_strerror_r(int errnum, char * result, size_t length);
/*==============================================================================
    GUARD
==============================================================================*/
#endif // CTK_STRING_H_20210627022855
