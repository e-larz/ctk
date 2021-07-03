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
 *
 * @brief
 * Detect various platforms, OSes, compilers, language features, etc through
 * macros
 */
/*==============================================================================
    GUARD
==============================================================================*/
#ifndef CTK_PLATFORM_H_20210624181246
#define CTK_PLATFORM_H_20210624181246
/*==============================================================================
    DEFINE
==============================================================================*/
#if (defined(__unix__) || defined(__unix)) && !defined(_WIN32)
    // Must be defined before including any header
    #define _POSIX_C_SOURCE 200809L
    #include <unistd.h>
    #if defined(_POSIX_VERSION)
        #define CTK_POSIX 1
    #else
        #undef _POSIX_C_SOURCE
    #endif
#endif
/*==============================================================================
    GUARD
==============================================================================*/
#endif // CTK_PLATFORM_H_20210624181246
