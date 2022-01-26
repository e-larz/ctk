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
// Test headers
#include "test_ctk_alloc.h"
#include "test_ctk_error.h"
#include "test_ctk_string.h"
#include "test_ctk_time.h"
// C Standard Library
#include <stdio.h>  // printf()
#include <stdlib.h> // EXIT_SUCCESS
/*==============================================================================
    MAIN
==============================================================================*/
int main(void)
{
    printf("*** Testing: ctk ***\n");
    TEST_ctk_alloc();
    TEST_ctk_error();
    TEST_ctk_string();
    TEST_ctk_time();
    return EXIT_SUCCESS;
}
