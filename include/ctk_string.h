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
 * Provide various functions to manipulate null-terminated strings.
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
#include <stddef.h> // ptrdiff_t, size_t
/*==============================================================================
    DEFINE
==============================================================================*/
/**
 * Size of a buffer big enough to contain an error string returned by
 * ctk_strerror_r().
 *
 * - There doesn't seem to be an easy way to ask for the length of a `errno`
 *   message(appart from `strerrorlen_s()` but nobody implements Annex K).
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
    ctk_stpcpy()
------------------------------------------------------------------------------*/
/**
 * Copies a string and returns a pointer to the end of the copied string.
 *
 * - The null-terminated string pointed by \p{src} is copied(including the
 *   terminating null character) into the character array pointed by \p{dest}.
 * - Works as `strcpy()` except for the following point:
 *     - Returns a pointer to the terminating null character of \p{dest}.
 *
 * @param[out] dest : The array where to copy \p{src}.
 * @param[in]  src  : The string to copy.
 *
 * @return
 * - @success: A pointer to the terminating null character of \p{dest}.
 * - @failure: `NULL`.
 *
 * @warning
 * - \b [UB] \p{src} must be a pointer to a null-terminated string.
 * - \b [UB] \p{src} and \p{dest} must not overlap.
 * - \b [UB] The size of the array pointed by \p{dest} must be equal or greater
 *           than the size of the array pointed by \p{src}.
 */
char * ctk_stpcpy(char * restrict dest, const char * restrict src);
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
/*------------------------------------------------------------------------------
    ctk_strpos()
------------------------------------------------------------------------------*/
/**
 * Finds the first position of \p{substr} in \p{str}.
 *
 * - Terminating null characters are excluded from the search.
 * - Both \p{str} and \p{substr} can be string litterals.
 *
 * @param[in] str    : The string to search in.
 * @param[in] substr : The string to search for.
 *
 * @return
 * - @success:
 *   - The position in \p{srt} of the first character from \p{substr}.
 *   - '0' if \p{substr} is an empty string.
 * - @failure: `-1`.
 *
 * @warning
 * - \b [UB] \p{str} must be a pointer to a null-terminated string.
 * - \b [UB] \p{substr} must be a pointer to a null-terminated string.
 */
ptrdiff_t ctk_strpos(const char * str, const char * substr);
/*------------------------------------------------------------------------------
    ctk_strrpos()
------------------------------------------------------------------------------*/
/**
 * Finds the last position of \p{substr} in \p{str}.
 *
 * - Terminating null characters are excluded from the search.
 * - Both \p{str} and \p{substr} can be string litterals.
 *
 * @param[in] str    : The string to search in.
 * @param[in] substr : The string to search for.
 *
 * @return
 * - @success:
 *   - The position in \p{srt} of the first character from \p{substr}.
 *   - '0' if \p{substr} is an empty string.
 * - @failure: `-1`.
 *
 * @warning
 * - \b [UB] \p{str} must be a pointer to a null-terminated string.
 * - \b [UB] \p{substr} must be a pointer to a null-terminated string.
 */
ptrdiff_t ctk_strrpos(const char * str, const char * substr);
/*------------------------------------------------------------------------------
    ctk_strrstr()
------------------------------------------------------------------------------*/
/**
 * Finds the last occurrence of \p{substr} in \p{str}.
 *
 * - Terminating null characters are excluded from the search.
 * - Both \p{str} and \p{substr} can be string litterals.
 *
 * @param[in] str    : The string to search in.
 * @param[in] substr : The string to search for.
 *
 * @return
 * - @success:
 *   - A pointer to the position in \p{str} where \p{substr} is found.
 *   - A pointer to the beginning of \p{str} if \p{substr} is an empty string.
 * - @failure: `NULL`.
 *
 * @warning
 * - \b [UB] \p{str} must be a pointer to a null-terminated string.
 * - \b [UB] \p{substr} must be a pointer to a null-terminated string.
 * - \b [UB] The returned pointer must not be dereferenced after freeing
 *           \p{str}.
 */
char * ctk_strrstr(const char * str, const char * substr);
/*------------------------------------------------------------------------------
    ctk_strtolower()
------------------------------------------------------------------------------*/
/**
 * Converts a string to lower case.
 *
 * - The conversion is done in-place and the string pointed by \p{str} may be
 *   modified by this function.
 *
 * @param[in,out] str : The string to convert.
 *
 * @return A pointer to the beginning of the string.
 *
 * @warning
 * - \b [UB] \p{str} must be a pointer to a null-terminated string.
 */
char * ctk_strtolower(char * str);
/*------------------------------------------------------------------------------
    ctk_strtoupper()
------------------------------------------------------------------------------*/
/**
 * Converts string to upper case.
 *
 * - The conversion is done in-place and the string pointed by \p{str} may be
 *   modified by this function.
 *
 * @param[in,out] str : The string to convert.
 *
 * @return A pointer to the beginning of the string.
 *
 * @warning
 * - \b [UB] \p{str} must be a pointer to a null-terminated string.
 */
char * ctk_strtoupper(char * str);
/*------------------------------------------------------------------------------
    ctk_strtrim()
------------------------------------------------------------------------------*/
/**
 * Removes leading and trailing whitespaces from a string.
 *
 * - Whitespaces are the characters for which `isspace()` returns true.
 * - The removal is done in-place and the string pointed by \p{str} may be
 *   modified by this function.
 *
 * @param[in,out] str : The string to trim.
 *
 * @return A pointer to the first non-whitespace character of \p{str}.
 *
 * @warning
 * - \b [UB] \p{str} must be a pointer to a null-terminated string.
 * - \b [UB] The returned pointer must not be passed to `free()`.
 * - \b [UB] The returned pointer must not be dereferenced after freeing
 *           \p{str}.
 */
char * ctk_strtrim(char * str);
/*------------------------------------------------------------------------------
    ctk_strtriml()
------------------------------------------------------------------------------*/
/**
 * Removes leading whitespaces from a string.
 *
 * - Whitespaces are the characters for which `isspace()` returns true.
 * - The removal is done in-place and the string pointed by \p{str} may be
 *   modified by this function.
 *
 * @param[in,out] str : The string to trim.
 *
 * @return A pointer to the first non-whitespace character of \p{str}.
 *
 * @warning
 * - \b [UB] \p{str} must be a pointer to a null-terminated string.
 * - \b [UB] The returned pointer must not be passed to `free()`.
 * - \b [UB] The returned pointer must not be dereferenced after freeing
 *           \p{str}.
 */
char * ctk_strtriml(char * str);
/*------------------------------------------------------------------------------
    ctk_strtrimr()
------------------------------------------------------------------------------*/
/**
 * Removes trailing whitespaces from a string.
 *
 * - Whitespaces are the characters for which `isspace()` returns true.
 * - The removal is done in-place and the string pointed by \p{str} may be
 *   modified by this function.
 *
 * @param[in,out] str : The string to trim.
 *
 * @return A pointer to the beginning of the string.
 *
 * @warning
 * - \b [UB] \p{str} must be a pointer to a null-terminated string.
 * - \b [UB] The returned pointer must not be dereferenced after freeing
 *           \p{str}.
 */
char * ctk_strtrimr(char * str);
/*------------------------------------------------------------------------------
    ctk_tolower()
------------------------------------------------------------------------------*/
/**
 * Converts an uppercase character to a lowercase one.
 *
 * Works as `tolower()` except for the following points:
 * - Returns \p{c} if \p{c} is neither representable as an `unsigned char` nor
 *   has the value of `EOF`(instead of being an undefined behavior).
 *
 * @param[in] c : The character to convert.
 *
 * @return
 * - @success: The lowercase version of \p{c}.
 * - @failure: Unmodified \p{c}.
 *
 * @see
 * - @C17{7,4,2,1}
 * - https://en.cppreference.com/w/c/string/byte/tolower
 */
int ctk_tolower(int c);
/*------------------------------------------------------------------------------
    ctk_toupper()
------------------------------------------------------------------------------*/
/**
 * Converts a lowercase character to an uppercase one.
 *
 * Works as `toupper()` except for the following points:
 * - Returns \p{c} if \p{c} is neither representable as an `unsigned char` nor
 *   has the value of `EOF`(instead of being an undefined behavior).
 *
 * @param[in] c : The character to convert.
 *
 * @return
 * - @success: The uppercase version of \p{c}.
 * - @failure: Unmodified \p{c}.
 *
 * @see
 * - @C17{7,4,2,2}
 * - https://en.cppreference.com/w/c/string/byte/toupper
 */
int ctk_toupper(int c);
/*==============================================================================
    GUARD
==============================================================================*/
#endif // CTK_STRING_H_20210627022855
