/*!
 * @file
 * @copyright
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
 */
/*==============================================================================
    INCLUDE
==============================================================================*/
// Portability
#include "ctk_platform.h"
// Own header
#include "ctk_string.h"
// C Standard Library
#include <assert.h>
#include <stdio.h>  // fputs()
#include <string.h> // size_t, POSIX strerror_r()
/*==============================================================================
    PUBLIC FUNCTION
==============================================================================*/
/*------------------------------------------------------------------------------
    ctk_strerror_r()
------------------------------------------------------------------------------*/
int ctk_strerror_r(const int errnum, char * const result, const size_t length)
{
    assert(result != NULL);
    assert(length > 0);

// There is a GNU-specific strerror_r() with a different prototype and behavior
// that will be used if _GNU_SOURCE is defined.
#if defined(CTK_POSIX) && !defined(_GNU_SOURCE)
    // strerror_r() return an error number but doesn't set errno
    const int err_no = strerror_r(errnum, result, length);
    if(err_no != 0) {
        fputs("strerror_r() failed!\n", stderr);
    }
    return err_no;
//! @todo Support non-POSIX platforms
#else
    return CTK_ERR_NO_SUPPORT;
#endif
}
