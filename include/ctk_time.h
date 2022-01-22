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
 * Provide time related functions.
 */
/*==============================================================================
    GUARD
==============================================================================*/
#ifndef CTK_TIME_H_20210622224649
#define CTK_TIME_H_20210622224649
/*==============================================================================
    INCLUDE
==============================================================================*/
// C Standard Library
#include <time.h> // struct tm, time_t, size_t
/*==============================================================================
    DEFINE
==============================================================================*/
/**
 * Size needed for a buffer to contain the timestamp string returned by
 * ctk_iso8601_time().
 */
#define CTK_TIME_ISO8601_STR_LENGTH sizeof("YYYY-MM-DDThh:mm:ss+hhmm")
/*==============================================================================
    PUBLIC FUNCTION
==============================================================================*/
/*------------------------------------------------------------------------------
    ctk_localtime_r()
------------------------------------------------------------------------------*/
/**
 * Convert time in seconds since Epoch to a broken-down local time.
 *
 * - Reentrant version of `localtime()`.
 * - Functionally equivalent to POSIX `localtime_r()`.
 *
 * @param[in]  timer  : Time in seconds since Epoch.
 * @param[out] result : Buffer where the result will be stored.
 *
 * @return
 * - @success: A pointer to \p{result}.
 * - @failure: `NULL`.
 *
 * @warning
 * - \p{timer} must not be `NULL`
 * - \p{result} must not be `NULL`
 *
 * @see
 * - https://en.cppreference.com/w/c/chrono/localtime
 * - https://en.cppreference.com/w/c/chrono/tm
 * - https://pubs.opengroup.org/onlinepubs/9699919799/functions/localtime.html
 */
struct tm * ctk_localtime_r(
    const time_t * restrict timer, struct tm * restrict result
);
/*------------------------------------------------------------------------------
    ctk_iso8601_time()
------------------------------------------------------------------------------*/
/**
 * Convert time in seconds since Epoch to a null-terminated ISO 8601 formatted
 * string.
 *
 * - Equivalent to using `strftime()` with `"%FT%T%z"` as format string.
 * - The string is formatted as follows: `"YYYY-MM-DDThh:mm:ss+hhmm"`
 *   @v
 *   YYYY : 4 digits year
 *   MM   : 2 digits month
 *   DD   : 2 digits day
 *   hh   : Hour
 *   mm   : Minute
 *   ss   : Second
 *   +    : '+' or '-' character
 *   hhmm : UTC offset
 *   @endv
 * - Example:
 *   @v
 *   2021-03-15T19:37:59+0530
 *   2021-03-15T19:37:59-0530
 *   @endv
 *
 * @param[in]  timer  : Time in seconds since Epoch.
 * @param[out] result : Buffer where the string will be stored.
 * @param[in]  length : Length of the result buffer.
 *
 * @return
 * - @success: A pointer to \p{result}.
 * - @failure: `NULL`.
 *
 * @warning
 * - \p{result} must not be `NULL`.
 * - \p{length} must be >= #CTK_TIME_ISO8601_STR_LENGTH.
 *
 * @see
 * - https://en.wikipedia.org/wiki/ISO_8601
 * - https://en.cppreference.com/w/c/chrono/strftime
 */
char * ctk_iso8601_time(time_t timer, char * result, size_t length);
/*==============================================================================
    GUARD
==============================================================================*/
#endif // CTK_TIME_H_20210622224649
