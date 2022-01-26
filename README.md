# CTK - C Toolkit

[![pipeline status](https://gitlab.com/callback/ctl/badges/master/pipeline.svg)](https://gitlab.com/callback/ctk/-/commits/master)
[![license](https://img.shields.io/badge/license-0BSD-blue)](LICENSE)
[![doxygen](https://img.shields.io/badge/doc-doxygen-blue)](https://callback.gitlab.io/ctk)

A `C11` library providing some convenient, portable and safe low-level functions
for memory allocation, I/O, time, errors, etc.

## Table of Contents

- [Quick overview](#quick-overview)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Documentation](#documentation)
- [Versioning](#versioning)
- [Changelog](#changelog)
- [Contributing](#contributing)
- [License](#license)

## Quick overview

Safer `malloc()` and `free()`

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctk_alloc.h>

int main(int argc, char * argv[])
{
    const char * str = "foo bar";
    // Calling malloc(0) is implemtentation-defined, ctk_malloc(0) return NULL
    // in this case.
    char * str_cpy = ctk_malloc(0);
    // Will trigger because of the above
    if(str_cpy == NULL) {
        fprintf(stderr, "ctk_malloc() failed!\n");
    }
    char * str_cpy = ctk_malloc(strlen(str) + 1);
    // Won't trigger(not taking into account possible errors on the system side)
    if(str_cpy == NULL) {
        fprintf(stderr, "ctk_malloc() failed!\n");
    }
    strcpy(str_cpy, str);
    printf("%s\n", str_cpy);
    // Free str_cpy and set it to NULL(notice the `&`)
    ctk_free(&str_cpy);
    // OK: str_cpy has been set to NULL
    free(str_cpy);

    return EXIT_SUCCESS;
}
```

Time string formating

```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctk_time.h>

int main(int argc, char * argv[])
{
    const time_t t = time(NULL);
    if(t == -1) {
        fprintf(stderr, "time() failed!\n");
        return EXIT_FAILURE;
    }
    // The `\0` is taken into account in CTK_TIME_ISO8601_STR_LENGTH so it's not
    // needed to add 1 to the size of buf[]
    char buf[CTK_TIME_ISO8601_STR_LENGTH] = {0};
    if(ctk_iso8601_time(t, buf, sizeof(buf)) != NULL) {
        fprintf(stderr, "ctk_iso8601_time() failed!\n");
        return EXIT_FAILURE;
    }
    // The output was "2022-01-22T21:08:16+00:00" at the time of the execution
    printf("%s\n", buf);

    return EXIT_SUCCESS;
}
```

String functions

```c
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctk_string.h>

int main(int argc, char * argv[])
{
    char error_str[CTK_STRING_ERR_LENGTH] = {0};
    int * ptr = malloc(sizeof(*ptr) * 1000000000000000000);
    if(ptr == NULL) {
        if(ctk_strerror_r(errno, error_str, sizeof(error_str)) == 0) {
            fprintf(stderr, "ctk_malloc() failed! %s\n", error_str);
        }
        exit(EXIT_FAILURE);
    }
    free(ptr);
    return EXIT_SUCCESS;
}
```

Macros to ease parameters checking

```c
#include <stdio.h>
#include <stdlib.h>
#include <ctk_error.h>

int foo(int a, int b, int c)
{
    CTK_ERROR_RET_VAL_IF_MSG(a == 0, 1, "Returning 1");
    CTK_ERROR_RET_VAL_IF(b == 0, 2);
    CTK_ERROR_RET_0_IF(c == 0);
    return 17;
}

int main(int argc, char * argv[])
{
    int x = foo(0, 11, 13); // x = 1
    x = foo(11, 0, 13);     // x = 2
    x = foo(11, 13, 0);     // x = 0
    x = foo(0, 0, 0);       // x = 1
    x = foo(1, 2, 3);       // x = 17

    return EXIT_SUCCESS;
}
```

## Getting Started

### Prerequisites

A `C11` compliant compiler is needed to compile the code.

### Installation

[Download](https://gitlab.com/callback/ctk/-/archive/master/ctk-master.zip) or
clone the repository:

```
git clone https://gitlab.com/callback/ctk.git
```

Optionally run the tests:

```
cd ctk
make all
make check
```

Install the library to the standard default location `/usr/local/include/ctk`:

```
make install
```

Or install them to a different path `/my/custom/path/include/ctl`:

```
make install prefix=/my/custom/path
```

Add `/usr/local/include/ctl` or `/my/custom/path/include/ctl` to your include
paths.

## Documentation

Doxygen documentation is available here: <https://callback.gitlab.io/ctk>

## Versioning

This project follows [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## Changelog

See the [CHANGELOG.md](CHANGELOG.md) file.

## Contributing

See the [CONTRIBUTING.md](CONTRIBUTING.md) file.

## License

This project is licensed under the _very_ permissive [BSD Zero Clause License](LICENSE).

More information on the 0BSD license:

- [The 0BSD's creator website](https://landley.net/toybox/license.html)
- [BSD Zero Clause License | Software Package Data Exchange (SPDX)](https://spdx.org/licenses/0BSD.html)
- [Zero-Clause BSD (0BSD) | Open Source Initiative](https://opensource.org/licenses/0BSD)
- [BSD Zero Clause License | Choose a License](https://choosealicense.com/licenses/0bsd/)
