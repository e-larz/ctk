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
#include <limits.h> // INT_MAX, UCHAR_MAX
#include <stdio.h>  // EOF, printf()
#include <string.h> // NULL, strcmp(), strerror()
/*==============================================================================
    MACRO
==============================================================================*/
/*==============================================================================
    FUNCTION DECLARATION
==============================================================================*/
static void TEST_ctk_strerror_r(void);
static void TEST_ctk_strpos(void);
static void TEST_ctk_strrpos(void);
static void TEST_ctk_strrstr(void);
static void TEST_ctk_strtolower(void);
static void TEST_ctk_strtoupper(void);
static void TEST_ctk_strtrim(void);
static void TEST_ctk_strtriml(void);
static void TEST_ctk_strtrimr(void);
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
    TEST_ctk_strpos();
    TEST_ctk_strrpos();
    TEST_ctk_strrstr();
    TEST_ctk_strtolower();
    TEST_ctk_strtoupper();
    TEST_ctk_strtrim();
    TEST_ctk_strtriml();
    TEST_ctk_strtrimr();
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
    TEST_ctk_strpos()
------------------------------------------------------------------------------*/
static void TEST_ctk_strpos(void)
{
    // Haystack and needle are NULL
    assert(ctk_strpos(NULL, NULL) == -1);
    // Haystack is NULL and needle is empty
    assert(ctk_strpos(NULL, "") == -1);
    // Haystack is empty and needle is NULL
    assert(ctk_strpos("", NULL) == -1);
    // Haystack and needle are empty
    assert(ctk_strpos("", "") == 0);
    // Haystack is random and needle is empty
    assert(ctk_strpos(">X,3?in.a{g>>qRc", "") == 0);
    // Haystack is empty and needle is random
    assert(ctk_strpos("", ">X,3?in.a{g>>qRc") == -1);
    // Haystack is a truncated needle
    assert(ctk_strpos(">X,3?in", ">X,3?in.a{g>>qRc") == -1);
    // Haystack and needle are one char long and don't match
    assert(ctk_strpos("a", "b") == -1);
    // Haystack and needle are one char long and match
    assert(ctk_strpos("a", "a") == 0);
    // Haystack and needle are multiple char long and match exactly
    assert(ctk_strpos(">X,3?in.a{g>>qRc", ">X,3?in.a{g>>qRc") == 0);
    // Needle is at the beggining of haystack
    assert(ctk_strpos(">X,3?in.a{g>>qRc", ">X,3?in") == 0);
    // Needle is in the middle of haystack
    assert(ctk_strpos(">X,3?in.a{g>>qRc", "in.a{g>") == 5);
    // Needle is at the end of haystack
    assert(ctk_strpos(">X,3?in.a{g>>qRc", "{g>>qRc") == 9);
    // Needle is at the end of haystack but has one char too many
    assert(ctk_strpos(">X,3?in.a{g>>qRc", "{g>>qRcX") == -1);
    // Haystack has multiple adjacent needles
    assert(ctk_strpos(">X,3?i3?i3?i>qRc", "3?i") == 3);
    // Haystack has multiple non-adjacent needles
    assert(ctk_strpos(">X,3?in.3?i>3?ic", "3?i") == 3);
    // Needle is at the beginning but its first char is wrong
    assert(ctk_strpos(">X,3?in.a{g>>qRc", "<X,3?in") == -1);
    // Needle is at the beginning but a char in its middle is wrong
    assert(ctk_strpos(">X,3?in.a{g>>qRc", ">X,!3in") == -1);
    // Needle is at the beginning but its last char is wrong
    assert(ctk_strpos(">X,3?in.a{g>>qRc", ">X,3?im") == -1);
    // Needle is in the middle but its first char is wrong
    assert(ctk_strpos(">X,3?in.a{g>>qRc", "jn.a{g>") == -1);
    // Needle is in the middle but a char in its middle is wrong
    assert(ctk_strpos(">X,3?in.a{g>>qRc", "in.b{g>") == -1);
    // Needle is in the middle but its last char is wrong
    assert(ctk_strpos(">X,3?in.a{g>>qRc", "in.a{g<") == -1);
    // Needle is at the end but its first char is wrong
    assert(ctk_strpos(">X,3?in.a{g>>qRc", "}g>>qRc") == -1);
    // Needle is at the end but a char in its middle is wrong
    assert(ctk_strpos(">X,3?in.a{g>>qRc", "{g><qRc") == -1);
    // Needle is at the end but its last char is wrong
    assert(ctk_strpos(">X,3?in.a{g>>qRc", "{g>>qRd") == -1);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_ctk_strrpos()
------------------------------------------------------------------------------*/
static void TEST_ctk_strrpos(void)
{
    // Haystack and needle are NULL
    assert(ctk_strrpos(NULL, NULL) == -1);
    // Haystack is NULL and needle is empty
    assert(ctk_strrpos(NULL, "") == -1);
    // Haystack is empty and needle is NULL
    assert(ctk_strrpos("", NULL) == -1);
    // Haystack and needle are empty
    assert(ctk_strrpos("", "") == 0);
    // Haystack is random and needle is empty
    assert(ctk_strrpos(">X,3?in.a{g>>qRc", "") == 0);
    // Haystack is empty and needle is random
    assert(ctk_strrpos("", ">X,3?in.a{g>>qRc") == -1);
    // Haystack is a truncated needle
    assert(ctk_strrpos(">X,3?in", ">X,3?in.a{g>>qRc") == -1);
    // Haystack and needle are one char long and don't match
    assert(ctk_strrpos("a", "b") == -1);
    // Haystack and needle are one char long and match
    assert(ctk_strrpos("a", "a") == 0);
    // Haystack and needle are multiple char long and match exactly
    assert(ctk_strrpos(">X,3?in.a{g>>qRc", ">X,3?in.a{g>>qRc") == 0);
    // Needle is at the beggining of haystack
    assert(ctk_strrpos(">X,3?in.a{g>>qRc", ">X,3?in") == 0);
    // Needle is in the middle of haystack
    assert(ctk_strrpos(">X,3?in.a{g>>qRc", "in.a{g>") == 5);
    // Needle is at the end of haystack
    assert(ctk_strrpos(">X,3?in.a{g>>qRc", "{g>>qRc") == 9);
    // Needle is at the end of haystack but has one char too many
    assert(ctk_strrpos(">X,3?in.a{g>>qRc", "{g>>qRcX") == -1);
    // Haystack has multiple adjacent needles
    assert(ctk_strrpos(">X,3?i3?i3?i>qRc", "3?i") == 9);
    // Haystack has multiple non-adjacent needles
    assert(ctk_strrpos(">X,3?in.3?i>3?ic", "3?i") == 12);
    // Needle is at the beginning but its first char is wrong
    assert(ctk_strrpos(">X,3?in.a{g>>qRc", "<X,3?in") == -1);
    // Needle is at the beginning but a char in its middle is wrong
    assert(ctk_strrpos(">X,3?in.a{g>>qRc", ">X,!3in") == -1);
    // Needle is at the beginning but its last char is wrong
    assert(ctk_strrpos(">X,3?in.a{g>>qRc", ">X,3?im") == -1);
    // Needle is in the middle but its first char is wrong
    assert(ctk_strrpos(">X,3?in.a{g>>qRc", "jn.a{g>") == -1);
    // Needle is in the middle but a char in its middle is wrong
    assert(ctk_strrpos(">X,3?in.a{g>>qRc", "in.b{g>") == -1);
    // Needle is in the middle but its last char is wrong
    assert(ctk_strrpos(">X,3?in.a{g>>qRc", "in.a{g<") == -1);
    // Needle is at the end but its first char is wrong
    assert(ctk_strrpos(">X,3?in.a{g>>qRc", "}g>>qRc") == -1);
    // Needle is at the end but a char in its middle is wrong
    assert(ctk_strrpos(">X,3?in.a{g>>qRc", "{g><qRc") == -1);
    // Needle is at the end but its last char is wrong
    assert(ctk_strrpos(">X,3?in.a{g>>qRc", "{g>>qRd") == -1);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_ctk_strrstr()
------------------------------------------------------------------------------*/
static void TEST_ctk_strrstr(void)
{
    // Haystack and needle are NULL
    assert(ctk_strrstr(NULL, NULL) == NULL);
    // Haystack is NULL and needle is empty
    assert(ctk_strrstr(NULL, "") == NULL);
    // Haystack is empty and needle is NULL
    assert(ctk_strrstr("", NULL) == NULL);
    // Haystack and needle are empty
    assert(strcmp(ctk_strrstr("", ""), "") == 0);
    // Haystack is random and needle is empty
    assert(strcmp(ctk_strrstr(">X,3?in.a{g>>qRc", ""), ">X,3?in.a{g>>qRc") == 0);
    // Haystack is empty and needle is random
    assert(ctk_strrstr("", ">X,3?in.a{g>>qRc") == NULL);
    // Haystack is a truncated needle
    assert(ctk_strrstr(">X,3?in", ">X,3?in.a{g>>qRc") == NULL);
    // Haystack and needle are one char long and don't match
    assert(ctk_strrstr("a", "b") == NULL);
    // Haystack and needle are one char long and match
    assert(strcmp(ctk_strrstr("a", "a"), "a") == 0);
    // Haystack and needle are multiple char long and match exactly
    assert(strcmp(ctk_strrstr(">X,3?in.a{g>>qRc", ">X,3?in.a{g>>qRc"), ">X,3?in.a{g>>qRc") == 0);
    // Needle is at the beggining of haystack
    assert(strcmp(ctk_strrstr(">X,3?in.a{g>>qRc", ">X,3?in"), ">X,3?in.a{g>>qRc") == 0);
    // Needle is in the middle of haystack
    assert(strcmp(ctk_strrstr(">X,3?in.a{g>>qRc", "in.a{g>"), "in.a{g>>qRc") == 0);
    // Needle is at the end of haystack
    assert(strcmp(ctk_strrstr(">X,3?in.a{g>>qRc", "{g>>qRc"), "{g>>qRc") == 0);
    // Needle is at the end of haystack but has one char too many
    assert(ctk_strrstr(">X,3?in.a{g>>qRc", "{g>>qRcX") == NULL);
    // Haystack has multiple adjacent needles
    assert(strcmp(ctk_strrstr(">X,3?i3?i3?i>qRc", "3?i"), "3?i>qRc") == 0);
    // Haystack has multiple non-adjacent needles
    assert(strcmp(ctk_strrstr(">X,3?in.3?i>3?ic", "3?i"), "3?ic") == 0);
    // Needle is at the beginning but its first char is wrong
    assert(ctk_strrstr(">X,3?in.a{g>>qRc", "<X,3?in") == NULL);
    // Needle is at the beginning but a char in its middle is wrong
    assert(ctk_strrstr(">X,3?in.a{g>>qRc", ">X,!3in") == NULL);
    // Needle is at the beginning but its last char is wrong
    assert(ctk_strrstr(">X,3?in.a{g>>qRc", ">X,3?im") == NULL);
    // Needle is in the middle but its first char is wrong
    assert(ctk_strrstr(">X,3?in.a{g>>qRc", "jn.a{g>") == NULL);
    // Needle is in the middle but a char in its middle is wrong
    assert(ctk_strrstr(">X,3?in.a{g>>qRc", "in.b{g>") == NULL);
    // Needle is in the middle but its last char is wrong
    assert(ctk_strrstr(">X,3?in.a{g>>qRc", "in.a{g<") == NULL);
    // Needle is at the end but its first char is wrong
    assert(ctk_strrstr(">X,3?in.a{g>>qRc", "}g>>qRc") == NULL);
    // Needle is at the end but a char in its middle is wrong
    assert(ctk_strrstr(">X,3?in.a{g>>qRc", "{g><qRc") == NULL);
    // Needle is at the end but its last char is wrong
    assert(ctk_strrstr(">X,3?in.a{g>>qRc", "{g>>qRd") == NULL);
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
    char str_empty[] = "";
    assert(strcmp(ctk_strtolower(str_empty), "") == 0);
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
    char str_empty[] = "";
    assert(strcmp(ctk_strtoupper(str_empty), "") == 0);
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
    TEST_ctk_strtrim()
------------------------------------------------------------------------------*/
static void TEST_ctk_strtrim(void)
{
    // NULL pointer
    assert(ctk_strtrim(NULL) == NULL);
    // Empty string
    char str_empty[] = "";
    assert(strcmp(ctk_strtrim(str_empty), "") == 0);
    // No white spaces
    char str_no_ws[] = "Lorem";
    assert(strcmp(ctk_strtrim(str_no_ws), "Lorem") == 0);
    // Only white spaces: n = 1
    char str_only_ws_1[] = " ";
    assert(strcmp(ctk_strtrim(str_only_ws_1), "") == 0);
    // Only white spaces: n = 5
    char str_only_ws_5[] = "     ";
    assert(strcmp(ctk_strtrim(str_only_ws_5), "") == 0);
    // White spaces: before n = 1
    char str_ws_b1[] = " Lorem";
    assert(strcmp(ctk_strtrim(str_ws_b1), "Lorem") == 0);
    // White spaces: before n = 5
    char str_ws_b5[] = "     Lorem";
    assert(strcmp(ctk_strtrim(str_ws_b5), "Lorem") == 0);
    // White spaces: middle n = 1
    char str_ws_m1[] = "Lorem ipsum";
    assert(strcmp(ctk_strtrim(str_ws_m1), "Lorem ipsum") == 0);
    // White spaces: middle n = 5
    char str_ws_m5[] = "Lorem     ipsum";
    assert(strcmp(ctk_strtrim(str_ws_m5), "Lorem     ipsum") == 0);
    // White spaces: end n = 1
    char str_ws_e1[] = "Lorem ";
    assert(strcmp(ctk_strtrim(str_ws_e1), "Lorem") == 0);
    // White spaces: end n = 5
    char str_ws_e5[] = "Lorem     ";
    assert(strcmp(ctk_strtrim(str_ws_e5), "Lorem") == 0);
    // White spaces: before - middle n = 1
    char str_ws_bm1[] = " Lorem ipsum";
    assert(strcmp(ctk_strtrim(str_ws_bm1), "Lorem ipsum") == 0);
    // White spaces: before - middle n = 5
    char str_ws_bm5[] = "     Lorem     ipsum";
    assert(strcmp(ctk_strtrim(str_ws_bm5), "Lorem     ipsum") == 0);
    // White spaces: before - end n = 1
    char str_ws_be1[] = " Lorem ";
    assert(strcmp(ctk_strtrim(str_ws_be1), "Lorem") == 0);
    // White spaces: before - end n = 5
    char str_ws_be5[] = "     Lorem     ";
    assert(strcmp(ctk_strtrim(str_ws_be5), "Lorem") == 0);
    // White spaces: middle - end n = 1
    char str_ws_me1[] = "Lorem ipsum ";
    assert(strcmp(ctk_strtrim(str_ws_me1), "Lorem ipsum") == 0);
    // White spaces: middle - end n = 5
    char str_ws_me5[] = "Lorem     ipsum     ";
    assert(strcmp(ctk_strtrim(str_ws_me5), "Lorem     ipsum") == 0);
    // White spaces: before - middle - end n = 1
    char str_ws_bme1[] = " Lorem ipsum dolor sit ";
    assert(strcmp(ctk_strtrim(str_ws_bme1), "Lorem ipsum dolor sit") == 0);
    // White spaces: before - middle - end n = 5
    char str_ws_bme5[] = "     Lorem     ipsum     dolor     sit     ";
    assert(strcmp(ctk_strtrim(str_ws_bme5), "Lorem     ipsum     dolor     sit") == 0);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_ctk_strtriml()
------------------------------------------------------------------------------*/
static void TEST_ctk_strtriml(void)
{
    // NULL pointer
    assert(ctk_strtriml(NULL) == NULL);
    // Empty string
    char str_empty[] = "";
    assert(strcmp(ctk_strtriml(str_empty), "") == 0);
    // No white spaces
    char str_no_ws[] = "Lorem";
    assert(strcmp(ctk_strtriml(str_no_ws), "Lorem") == 0);
    // Only white spaces: n = 1
    char str_only_ws_1[] = " ";
    assert(strcmp(ctk_strtriml(str_only_ws_1), "") == 0);
    // Only white spaces: n = 5
    char str_only_ws_5[] = "     ";
    assert(strcmp(ctk_strtriml(str_only_ws_5), "") == 0);
    // White spaces: before n = 1
    char str_ws_b1[] = " Lorem";
    assert(strcmp(ctk_strtriml(str_ws_b1), "Lorem") == 0);
    // White spaces: before n = 5
    char str_ws_b5[] = "     Lorem";
    assert(strcmp(ctk_strtriml(str_ws_b5), "Lorem") == 0);
    // White spaces: middle n = 1
    char str_ws_m1[] = "Lorem ipsum";
    assert(strcmp(ctk_strtriml(str_ws_m1), "Lorem ipsum") == 0);
    // White spaces: middle n = 5
    char str_ws_m5[] = "Lorem     ipsum";
    assert(strcmp(ctk_strtriml(str_ws_m5), "Lorem     ipsum") == 0);
    // White spaces: end n = 1
    char str_ws_e1[] = "Lorem ";
    assert(strcmp(ctk_strtriml(str_ws_e1), "Lorem ") == 0);
    // White spaces: end n = 5
    char str_ws_e5[] = "Lorem     ";
    assert(strcmp(ctk_strtriml(str_ws_e5), "Lorem     ") == 0);
    // White spaces: before - middle n = 1
    char str_ws_bm1[] = " Lorem ipsum";
    assert(strcmp(ctk_strtriml(str_ws_bm1), "Lorem ipsum") == 0);
    // White spaces: before - middle n = 5
    char str_ws_bm5[] = "     Lorem     ipsum";
    assert(strcmp(ctk_strtriml(str_ws_bm5), "Lorem     ipsum") == 0);
    // White spaces: before - end n = 1
    char str_ws_be1[] = " Lorem ";
    assert(strcmp(ctk_strtriml(str_ws_be1), "Lorem ") == 0);
    // White spaces: before - end n = 5
    char str_ws_be5[] = "     Lorem     ";
    assert(strcmp(ctk_strtriml(str_ws_be5), "Lorem     ") == 0);
    // White spaces: middle - end n = 1
    char str_ws_me1[] = "Lorem ipsum ";
    assert(strcmp(ctk_strtriml(str_ws_me1), "Lorem ipsum ") == 0);
    // White spaces: middle - end n = 5
    char str_ws_me5[] = "Lorem     ipsum     ";
    assert(strcmp(ctk_strtriml(str_ws_me5), "Lorem     ipsum     ") == 0);
    // White spaces: before - middle - end n = 1
    char str_ws_bme1[] = " Lorem ipsum dolor sit ";
    assert(strcmp(ctk_strtriml(str_ws_bme1), "Lorem ipsum dolor sit ") == 0);
    // White spaces: before - middle - end n = 5
    char str_ws_bme5[] = "     Lorem     ipsum     dolor     sit     ";
    assert(strcmp(ctk_strtriml(str_ws_bme5), "Lorem     ipsum     dolor     sit     ") == 0);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_ctk_strtrimr()
------------------------------------------------------------------------------*/
static void TEST_ctk_strtrimr(void)
{
    // NULL pointer
    assert(ctk_strtrimr(NULL) == NULL);
    // Empty string
    char str_empty[] = "";
    assert(strcmp(ctk_strtrimr(str_empty), "") == 0);
    // No white spaces
    char str_no_ws[] = "Lorem";
    assert(strcmp(ctk_strtrimr(str_no_ws), "Lorem") == 0);
    // Only white spaces: n = 1
    char str_only_ws_1[] = " ";
    assert(strcmp(ctk_strtrimr(str_only_ws_1), "") == 0);
    // Only white spaces: n = 5
    char str_only_ws_5[] = "     ";
    assert(strcmp(ctk_strtrimr(str_only_ws_5), "") == 0);
    // White spaces: before n = 1
    char str_ws_b1[] = " Lorem";
    assert(strcmp(ctk_strtrimr(str_ws_b1), " Lorem") == 0);
    // White spaces: before n = 5
    char str_ws_b5[] = "     Lorem";
    assert(strcmp(ctk_strtrimr(str_ws_b5), "     Lorem") == 0);
    // White spaces: middle n = 1
    char str_ws_m1[] = "Lorem ipsum";
    assert(strcmp(ctk_strtrimr(str_ws_m1), "Lorem ipsum") == 0);
    // White spaces: middle n = 5
    char str_ws_m5[] = "Lorem     ipsum";
    assert(strcmp(ctk_strtrimr(str_ws_m5), "Lorem     ipsum") == 0);
    // White spaces: end n = 1
    char str_ws_e1[] = "Lorem ";
    assert(strcmp(ctk_strtrimr(str_ws_e1), "Lorem") == 0);
    // White spaces: end n = 5
    char str_ws_e5[] = "Lorem     ";
    assert(strcmp(ctk_strtrimr(str_ws_e5), "Lorem") == 0);
    // White spaces: before - middle n = 1
    char str_ws_bm1[] = " Lorem ipsum";
    assert(strcmp(ctk_strtrimr(str_ws_bm1), " Lorem ipsum") == 0);
    // White spaces: before - middle n = 5
    char str_ws_bm5[] = "     Lorem     ipsum";
    assert(strcmp(ctk_strtrimr(str_ws_bm5), "     Lorem     ipsum") == 0);
    // White spaces: before - end n = 1
    char str_ws_be1[] = " Lorem ";
    assert(strcmp(ctk_strtrimr(str_ws_be1), " Lorem") == 0);
    // White spaces: before - end n = 5
    char str_ws_be5[] = "     Lorem     ";
    assert(strcmp(ctk_strtrimr(str_ws_be5), "     Lorem") == 0);
    // White spaces: middle - end n = 1
    char str_ws_me1[] = "Lorem ipsum ";
    assert(strcmp(ctk_strtrimr(str_ws_me1), "Lorem ipsum") == 0);
    // White spaces: middle - end n = 5
    char str_ws_me5[] = "Lorem     ipsum     ";
    assert(strcmp(ctk_strtrimr(str_ws_me5), "Lorem     ipsum") == 0);
    // White spaces: before - middle - end n = 1
    char str_ws_bme1[] = " Lorem ipsum dolor sit ";
    assert(strcmp(ctk_strtrimr(str_ws_bme1), " Lorem ipsum dolor sit") == 0);
    // White spaces: before - middle - end n = 5
    char str_ws_bme5[] = "     Lorem     ipsum     dolor     sit     ";
    assert(strcmp(ctk_strtrimr(str_ws_bme5), "     Lorem     ipsum     dolor     sit") == 0);
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
