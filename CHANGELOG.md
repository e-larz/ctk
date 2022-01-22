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

- `ctk_alloc`: Provide wrappers around standard allocation functions.
  - `ctk_malloc()`
  - `ctk_calloc()`
  - `ctk_realloc()`
  - `ctk_free()`
- `ctk_platform`: Detect various platforms through macros.
  - `CTK_POSIX`: Defined to `1` on Posix platforms.
- `ctk_string`: Provide string related functions.
  - `ctk_strerror_r()`: Reentrant version of `strerror()`
- `ctk_time`: Provide time related functions.
  - `ctk_localtime_r()`: Reentrant version of `strerror()`
  - `ctk_iso8601_time()`: Convert time since Epoch to a ISO 8601 formatted string.
