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
 * @todo
 * - Check the portability of `errno` values not defined in the C standard
 *   (i.e, POSIX, Windows, OS X, etc).
 */
/*==============================================================================
    INCLUDE
==============================================================================*/
// Portability
#include "ctk_platform.h"
// Own header
#include "ctk_string.h"
// C Standard Library
#include <ctype.h>  // isspace(), tolower(), toupper()
#include <errno.h>
#include <limits.h> // UCHAR_MAX
#include <stddef.h> // NULL, ptrdiff_t, size_t
#include <stdio.h>  // EOF, fputs()
#include <string.h> // strerror_r(), strstr()
// Internal
#include "ctk_error.h"
/*==============================================================================
    PUBLIC FUNCTION
==============================================================================*/
/*------------------------------------------------------------------------------
    ctk_strerror_r()
------------------------------------------------------------------------------*/
int ctk_strerror_r(const int errnum, char * const result, const size_t length)
{
    // POSIX strerror_r() will segfault in this case
    CTK_ERROR_RET_VAL_IF(result == NULL, EINVAL);

// There is a GNU-specific strerror_r() with a different prototype and behavior
// that will be used if _GNU_SOURCE is defined.
#if defined(CTK_POSIX) && !defined(_GNU_SOURCE)
    // strerror_r() return an error number but doesn't set errno
    const int err_no = strerror_r(errnum, result, length);
    /*if(err_no != 0) {
        fputs("strerror_r() failed!\n", stderr);
    }*/
    return err_no;
//! @todo Support non-POSIX platforms
#else
    return CTK_ERR_NO_SUPPORT;
#endif
}
/*------------------------------------------------------------------------------
    ctk_strpos()
------------------------------------------------------------------------------*/
ptrdiff_t ctk_strpos(const char * const str, const char * const substr)
{
    CTK_ERROR_RET_NEG_1_IF(str == NULL);
    CTK_ERROR_RET_NEG_1_IF(substr == NULL);
    const char * const pos = strstr(str, substr);
    if(pos == NULL) {
        return -1;
    }
    return pos - str;
}
/*------------------------------------------------------------------------------
    ctk_strrpos()
------------------------------------------------------------------------------*/
ptrdiff_t ctk_strrpos(const char * const str, const char * const substr)
{
    CTK_ERROR_RET_NEG_1_IF(str == NULL);
    CTK_ERROR_RET_NEG_1_IF(substr == NULL);
    const char * const pos = ctk_strrstr(str, substr);
    if(pos == NULL) {
        return -1;
    }
    return pos - str;
}
/*------------------------------------------------------------------------------
    ctk_strrstr()
------------------------------------------------------------------------------*/
/*! @cast Dropping the `const` qualifier when returning the result is necessary
* to have a single function that can be used with both constant and non-constant
* strings.
*/
char * ctk_strrstr(const char * const str, const char * const  substr)
{
    CTK_ERROR_RET_NULL_IF(str == NULL);
    CTK_ERROR_RET_NULL_IF(substr == NULL);
    if(substr[0] == '\0') {
        return (char *)str;
    }
    const char * found = NULL;
    const char * it = str;
    while((it = strstr(it, substr))) {
        found = it++;
    }
    return (char *)found;
}
/*------------------------------------------------------------------------------
    ctk_strtolower()
------------------------------------------------------------------------------*/
char * ctk_strtolower(char * const str)
{
    CTK_ERROR_RET_NULL_IF(str == NULL);
    for(char * it = str; *it; it++) {
        *it = (char)ctk_tolower(*it);
    }
    return str;
}
/*------------------------------------------------------------------------------
    ctk_strtoupper()
------------------------------------------------------------------------------*/
char * ctk_strtoupper(char * const str)
{
    CTK_ERROR_RET_NULL_IF(str == NULL);
    for(char * it = str; *it; it++) {
        *it = (char)ctk_toupper(*it);
    }
    return str;
}
/*------------------------------------------------------------------------------
    ctk_strtrim()
------------------------------------------------------------------------------*/
char * ctk_strtrim(char * const str)
{
    CTK_ERROR_RET_NULL_IF(str == NULL);
    return ctk_strtriml(ctk_strtrimr(str));
}
/*------------------------------------------------------------------------------
    ctk_strtriml()
------------------------------------------------------------------------------*/
char * ctk_strtriml(char * const str)
{
    CTK_ERROR_RET_NULL_IF(str == NULL);
    char * it = str;
    while(isspace(*it) && it++){}
    return it;
}
/*------------------------------------------------------------------------------
    ctk_strtrimr()
------------------------------------------------------------------------------*/
char * ctk_strtrimr(char * const str)
{
    CTK_ERROR_RET_NULL_IF(str == NULL);
    char * it = str + strlen(str);
    while((it-- > str) && isspace(*it)){}
    *++it = '\0';
    return str;
}
/*------------------------------------------------------------------------------
    ctk_tolower()
------------------------------------------------------------------------------*/
int ctk_tolower(const int c)
{
    if((c < 0 || c > UCHAR_MAX) && c != EOF) {
        return c;
    }
    return tolower(c);
}
/*------------------------------------------------------------------------------
    ctk_toupper()
------------------------------------------------------------------------------*/
int ctk_toupper(const int c)
{
    if((c < 0 || c > UCHAR_MAX) && c != EOF) {
        return c;
    }
    return toupper(c);
}
