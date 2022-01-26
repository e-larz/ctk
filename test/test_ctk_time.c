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
#include "test_ctk_time.h"
// The API to test
#include "ctk_time.h"
// C Standard Library
#include <assert.h>
#include <stdio.h>  // printf()
#include <string.h> // strcmp()
#include <time.h>   // asctime(), ctime(), strftime(), struct tm, time_t
/*==============================================================================
    MACRO
==============================================================================*/
/*==============================================================================
    FUNCTION DECLARATION
==============================================================================*/
static void TEST_ctk_localtime_r(void);
static void TEST_ctk_iso8601_time(void);
/*==============================================================================
    FUNCTION DEFINITION
==============================================================================*/
/*------------------------------------------------------------------------------
    TEST_ctk_time()
------------------------------------------------------------------------------*/
void TEST_ctk_time(void)
{
    printf("%s:\n", __func__);
    TEST_ctk_localtime_r();
    TEST_ctk_iso8601_time();
}
/*------------------------------------------------------------------------------
    TEST_ctk_localtime_r()
------------------------------------------------------------------------------*/
static void TEST_ctk_localtime_r(void)
{
    const time_t epoch = 0;
    struct tm t;
    // timer != NULL && result != NULL
    struct tm * res = ctk_localtime_r(&epoch, &t);
    assert(res != NULL);
    assert(strcmp(asctime(res), ctime(&epoch)) == 0);
    // timer == NULL && result != NULL
    res = ctk_localtime_r(NULL, &t);
    assert(res == NULL);
    // timer != NULL && result == NULL
    res = ctk_localtime_r(&epoch, NULL);
    assert(res == NULL);
    // timer == NULL && result == NULL
    res = ctk_localtime_r(&epoch, &t);
    assert(res != NULL);
    printf("\t%s: OK\n", __func__);
}
/*------------------------------------------------------------------------------
    TEST_ctk_iso8601_time()
------------------------------------------------------------------------------*/
static void TEST_ctk_iso8601_time(void)
{
    const time_t epoch = 0;
    char buf[CTK_TIME_ISO8601_STR_LENGTH] = {0};
    // result != NULL && length >= CTK_TIME_ISO8601_STR_LENGTH
    char * res = ctk_iso8601_time(epoch, buf, sizeof(buf));
    assert(res != NULL);
    struct tm * lt = localtime(&epoch);
    assert(lt != NULL);
    char buf_[CTK_TIME_ISO8601_STR_LENGTH] = {0};
    assert(strftime(buf_, sizeof(buf_), "%FT%T%z", lt) != 0);
    assert(strcmp(buf, buf_) == 0);
    // result != NULL && length < CTK_TIME_ISO8601_STR_LENGTH
    res = ctk_iso8601_time(epoch, buf, CTK_TIME_ISO8601_STR_LENGTH-1);
    assert(res == NULL);
    // result == NULL && length >= CTK_TIME_ISO8601_STR_LENGTH
    res = ctk_iso8601_time(epoch, NULL, sizeof(buf));
    assert(res == NULL);
    // result == NULL && length < CTK_TIME_ISO8601_STR_LENGTH
    res = ctk_iso8601_time(epoch, NULL, CTK_TIME_ISO8601_STR_LENGTH-1);
    assert(res == NULL);
    printf("\t%s: OK\n", __func__);
}
