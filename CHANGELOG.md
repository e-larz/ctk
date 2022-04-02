# Changelog

This file is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/) but
doesn't follow it to the letter.

This project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html),
which says in its summary:

    Given a version number MAJOR.MINOR.PATCH, increment the:
      1. MAJOR version when you make incompatible API changes,
      2. MINOR version when you add functionality in a backwards compatible manner, and
      3. PATCH version when you make backwards compatible bug fixes.

## [Unreleased]

### Added

- `ctk_error.h`
  - `CTK_ERROR_RET_EOF_IF()`: Makes a function return `EOF` if the given
    condition is true.
  - `CTK_ERROR_RET_FALSE_IF()`: Makes a function return `false` if the given
    condition is true.
  - `CTK_ERROR_RET_NEG_1_IF()` Makes a function return `-1` if the given
    condition is true.
- `ctk_string.h`
  - `ctk_stpcpy()`: Copies a string and returns a pointer to the end of the copied string.
  - `ctk_strpos()`: Finds the first position of a substring in a string.
  - `ctk_strrpos()`: Finds the last position of a substring in a string.
  - `ctk_strtolower()`: Converts in-place a null-terminated string to lower case.
  - `ctk_strtoupper()`: Converts in-place a null-terminated string to upper case.
  - `ctk_strrstr()`: Finds the last occurrence of a substring in a string.
  - `ctk_strtrim()`: Removes leading and trailing whitespaces from a null-terminated string.
  - `ctk_strtriml()`: Removes leading whitespaces from a null-terminated string.
  - `ctk_strtrimr()`: Removes trailing whitespaces from a null-terminated string.
  - `ctk_tolower()`: Safe wrapper around `tolower()`.
  - `ctk_toupper()`: Safe wrapper around `toupper()`.

## [0.1.0]

(2022-26-01)

### Added

- `ctk_alloc.h`: Provide wrappers around standard allocation functions.
  - `ctk_malloc()`: Return an error on size of `0`.
  - `ctk_calloc()`: Return an error on size of `0`.
  - `ctk_realloc()`: Return an error on size of `0`.
  - `ctk_free()`: Set pointer to `NULL` after dealocation.
- `ctk_error.h`: Provide error related functions.
  - `CTK_ERROR_RET_VAL_IF_MSG()`: Make a function return a value if a condition is true.
  - `CTK_ERROR_RET_VAL_IF()`: Same as `CTK_ERROR_RET_VAL_IF_MSG()`.
  - `CTK_ERROR_RET_IF()`: Same as `CTK_ERROR_RET_VAL_IF()` but for functions returning `void`.
  - `CTK_ERROR_RET_NULL_IF()`: Same as `CTK_ERROR_RET_VAL_IF()` but return `NULL`.
  - `CTK_ERROR_RET_0_IF()`: Same as `CTK_ERROR_RET_VAL_IF()` but return `0`.
- `ctk_platform.h`: Detect various platforms through macros.
  - `CTK_POSIX`: Defined to `1` on Posix platforms.
- `ctk_string.h`: Provide string related functions.
  - `ctk_strerror_r()`: Reentrant version of `strerror()`.
- `ctk_time.h`: Provide time related functions.
  - `ctk_localtime_r()`: Reentrant version of `localtime()`.
  - `ctk_iso8601_time()`: Convert time since Epoch to a ISO 8601 formatted string.
