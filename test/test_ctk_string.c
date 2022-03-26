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
 */
/*==============================================================================
    INCLUDE
==============================================================================*/
// Own header
#include "test_ctk_string.h"
// The API to test
#include "ctk_string.h"
// C Standard Library
#include <assert.h>
#include <ctype.h>  // tolower(), toupper()
#include <errno.h>
#include <limits.h> // UCHAR_MAX
#include <stdio.h>  // EOF, printf()
#include <string.h> // strcmp(), strerror()
/*==============================================================================
    MACRO
==============================================================================*/
/*==============================================================================
    FUNCTION DECLARATION
==============================================================================*/
static void TEST_ctk_strerror_r(void);
static void TEST_ctk_strtolower(void);
static void TEST_ctk_strtoupper(void);
static void TEST_ctk_tolower(void);
static void TEST_ctk_toupper(void);
/*==============================================================================
    FUNCTION DEFINITION
==============================================================================*/
/*------------------------------------------------------------------------------
    TEST_ctk_string()
------------------------------------------------------------------------------*/
void TEST_ctk_string(void)
{
    printf("%s:\n", __func__);
    TEST_ctk_strerror_r();
    TEST_ctk_strtolower();
    TEST_ctk_strtoupper();
    TEST_ctk_tolower();
    TEST_ctk_toupper();
}
/*------------------------------------------------------------------------------
    TEST_ctk_strerror_r()
------------------------------------------------------------------------------*/
static void TEST_ctk_strerror_r(void)
{
    char error[CTK_STRING_ERR_LENGTH] = {0};
    assert(ctk_strerror_r(0, error, CTK_STRING_ERR_LENGTH) == 0);
    assert(strcmp(error, strerror(0)) == 0);
    assert(ctk_strerror_r(EDOM, error, CTK_STRING_ERR_LENGTH) == 0);
    assert(strcmp(error, strerror(EDOM)) == 0);
    assert(ctk_strerror_r(EILSEQ, error, CTK_STRING_ERR_LENGTH) == 0);
    assert(strcmp(error, strerror(EILSEQ)) == 0);
    assert(ctk_strerror_r(ERANGE, error, CTK_STRING_ERR_LENGTH) == 0);
    assert(strcmp(error, strerror(ERANGE)) == 0);
    assert(ctk_strerror_r(-1, error, CTK_STRING_ERR_LENGTH) == EINVAL);
    assert(strcmp(error, strerror(-1)) == 0);
    assert(ctk_strerror_r(0, NULL, CTK_STRING_ERR_LENGTH) == EINVAL);
    assert(ctk_strerror_r(0, error, 0) == ERANGE);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_ctk_strtolower()
------------------------------------------------------------------------------*/
static void TEST_ctk_strtolower(void)
{
    // NULL pointer
    assert(ctk_strtolower(NULL) == NULL);
    // Empty string
    char str_empty_actual[] = "";
    const char * str_empty_expected = "";
    assert(strcmp(ctk_strtolower(str_empty_actual), str_empty_expected) == 0);
    // Full ASCII string
    char str_full_actual[256] = {0};
    char str_full_expected[256] = {0};
    for(int i = 0; i < 255; i++) {
        str_full_actual[i] = (char)(i+1);
        str_full_expected[i] = (char)tolower(i+1);
    }
    str_full_actual[255] = '\0';
    str_full_expected[255] = '\0';
    assert(strcmp(ctk_strtolower(str_full_actual), str_full_expected) == 0);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_ctk_strtoupper()
------------------------------------------------------------------------------*/
static void TEST_ctk_strtoupper(void)
{
    // NULL pointer
    assert(ctk_strtoupper(NULL) == NULL);
    // Empty string
    char str_empty_actual[] = "";
    const char * str_empty_expected = "";
    assert(strcmp(ctk_strtoupper(str_empty_actual), str_empty_expected) == 0);
    // Full ASCII string
    char str_full_actual[256] = {0};
    char str_full_expected[256] = {0};
    for(int i = 0; i < 255; i++) {
        str_full_actual[i] = (char)(i+1);
        str_full_expected[i] = (char)toupper(i+1);
    }
    str_full_actual[255] = '\0';
    str_full_expected[255] = '\0';
    assert(strcmp(ctk_strtoupper(str_full_actual), str_full_expected) == 0);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_ctk_tolower()
------------------------------------------------------------------------------*/
static void TEST_ctk_tolower(void)
{
    // Find a negative value different from EOF.
    int c = 0;
    for(int i = -1; i > INT_MIN; i--) {
        if(i != EOF) {
            c = i;
            break;
        }
    }
    // Invalid range: c < 0 && c != EOF
    assert(ctk_tolower(c) == c);
    // Invalid range: c > UCHAR_MAX
    assert(ctk_tolower(UCHAR_MAX+1) == UCHAR_MAX+1);
    // Valid range: c >= 0 && c <= UCHAR_MAX
    for(int i = 0; i < UCHAR_MAX; i++) {
        assert(ctk_tolower(i) == tolower(i));
    }
    // Valid value: EOF
    assert(ctk_tolower(EOF) == tolower(EOF));
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_ctk_toupper()
------------------------------------------------------------------------------*/
static void TEST_ctk_toupper(void)
{
    // Find a negative value different from EOF.
    int c = 0;
    for(int i = -1; i > INT_MIN; i--) {
        if(i != EOF) {
            c = i;
            break;
        }
    }
    // Invalid range: c < 0 && c != EOF
    assert(ctk_toupper(c) == c);
    // Invalid range: c > UCHAR_MAX
    assert(ctk_toupper(UCHAR_MAX+1) == UCHAR_MAX+1);
    // Valid range: c >= 0 && c <= UCHAR_MAX
    for(int i = 0; i < UCHAR_MAX; i++) {
        assert(ctk_toupper(i) == toupper(i));
    }
    // Valid value: EOF
    assert(ctk_toupper(EOF) == toupper(EOF));
    printf("\t%s: OK\n", __func__);
}
