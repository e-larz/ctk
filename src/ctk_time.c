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
    INCLUDE
==============================================================================*/
// Portability
#include "ctk_platform.h"
// Own header
#include "ctk_time.h"
// C Standard Library
#include <assert.h>
#include <stdio.h>  // fputs()
#include <time.h> // struct tm, time_t, strftime(), POSIX localtime_r(), size_t
/*==============================================================================
    DEFINE
==============================================================================*/
#define CTK_TIME_ISO8601_STR_FMT "%FT%T%z"
/*==============================================================================
    PUBLIC FUNCTION
==============================================================================*/
/*------------------------------------------------------------------------------
    ctk_localtime_r()
------------------------------------------------------------------------------*/
struct tm * ctk_localtime_r(
    const time_t * restrict const timer, struct tm * restrict const result
)
{
    assert(timer != NULL);
    assert(result != NULL);

#if defined(CTK_POSIX)
    struct tm * const ptr = localtime_r(timer, result);
    if(ptr == NULL) {
        fputs("localtime_r() failed!\n", stderr);
    }
    return ptr;
//! @todo Support non-POSIX platforms
#else
    return NULL;
#endif
}
/*------------------------------------------------------------------------------
    ctk_iso8601_time()
------------------------------------------------------------------------------*/
char * ctk_iso8601_time(
    const time_t timer, char * const result, const size_t length)
{
    assert(result != NULL);
    assert(length >= CTK_TIME_ISO8601_STR_LENGTH);

    struct tm lt;
    if(ctk_localtime_r(&timer, &lt) == NULL) {
        return NULL;
    }
    const size_t byte_cnt = strftime(result, length, CTK_TIME_ISO8601_STR_FMT, &lt);
    if(byte_cnt == 0) {
        fputs("strftime() failed!\n", stderr);
        return NULL;
    }
    return result;
}
