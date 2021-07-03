################################################################################
# CC
################################################################################
CC := gcc-11
# Warning options for gcc 11.1.0
# https://gcc.gnu.org/onlinedocs/gcc/Warning-Options.html
# Enable the bare minimum number of warnings to write C
CC_WARNING += -Wall
# calloc/malloc/realloc(0) (behavior is implementation defined)
CC_WARNING += -Walloc-zero
# Implicit conversions from arithmetic operations
CC_WARNING += -Warith-conversion
# Warn for out of bounds access to arrays at the end of a struct and when arrays
# are accessed through pointers
# May give false positives
# Need -ftree-vrp(-O2)
CC_WARNING += -Warray-bounds=2
# Function call is cast to the wrong type
CC_WARNING += -Wbad-function-cast
# C2x features not present in C11
CC_WARNING += -Wc11-c2x-compat
# Pointer is cast to a type with stricter alignment
# Warn even for platform allowing missaligned memory access(x86)
CC_WARNING += -Wcast-align=strict
# Pointer is cast to remove a type qualifier
CC_WARNING += -Wcast-qual
# Implicit cast that may change the value
# Enable -Wsign-conversion and Wfloat-conversion
CC_WARNING += -Wconversion
# GCC can't optimize the code
CC_WARNING += -Wdisabled-optimization
# Implicit promotion from float to double
CC_WARNING += -Wdouble-promotion
# If branch has the same code as the else one
CC_WARNING += -Wduplicated-branches
# If condition is the same as the else one
CC_WARNING += -Wduplicated-cond
# Extra mandatory warnings to write C
CC_WARNING += -Wextra
# Float values are compared with '=='
CC_WARNING += -Wfloat-equal
# Enable -Wformat -Wformat-nonliteral -Wformat-security -Wformat-y2k
CC_WARNING += -Wformat=2
# Calls to formatted input/output functions might overflow the destination
# buffer
# Optimization may give false positives
CC_WARNING += -Wformat-overflow=2
# Difference signedness between the format string and the argument
# Need -Wformat(-Wall)
CC_WARNING += -Wformat-signedness
# Calls to formatted input/output functions might result in output truncation
# Optimization may give false positives
CC_WARNING += -Wformat-truncation=2
# Switch case falls through unless commented with those regex:
#    -fallthrough
#    @fallthrough@
#    lint -fallthrough[ \t]*
#    [ \t]*FALLTHR(OUGH|U)[ \t]*
CC_WARNING += -Wimplicit-fallthrough=4
# Variable is initialized with itself
# Need -Wunitialized(-Wall/-Wextra)
CC_WARNING += -Winit-self
# GCC cant' inline a function declared with 'inline'
CC_WARNING += -Winline
# Goto or switch statement jumps forward or backward accross a variable
# initialized when declared
CC_WARNING += -Wjump-misses-init
# Suspicious uses of logical operators
CC_WARNING += -Wlogical-op
# Global function is defined without a previous declaration
CC_WARNING += -Wmissing-declarations
# User-supplied include directory doesn't exist
CC_WARNING += -Wmissing-include-dirs
# Global function is defined without a previous prototype declaration
CC_WARNING += -Wmissing-prototypes
# Extern declaration within a function
CC_WARNING += -Wnested-externs
CC_WARNING += -Wnormalized
# Dereferencing a null pointer
# Need -fdelete-null-pointer-checks(-O2)
CC_WARNING += -Wnull-dereference
# Old-style function definition: int foo();
CC_WARNING += -Wold-style-definition
# Structure padding
#CC_WARNING += -Wpadded
# Strict ISO C warnings
CC_WARNING += -Wpedantic
# Two or more identical declarations in the same scope
CC_WARNING += -Wredundant-decls
# Variable or type declaration shadowing
CC_WARNING += -Wshadow
# Left shift overflows(sign bit included)
CC_WARNING += -Wshift-overflow=2
# Functions not protected against stack smashing
# Need -fstack-protector
CC_WARNING += -Wstack-protector
# Compiler optimizations assuming signed overflow does not occur
CC_WARNING += -Wstrict-overflow=5
# Function declaration/defintion without argument types
CC_WARNING += -Wstrict-prototypes
# String manipulation functions determined to overflow the destination buffer
CC_WARNING += -Wstringop-overflow=4
CC_WARNING += -Wsuggest-attribute=noreturn
# Missing default in a switch
CC_WARNING += -Wswitch-default
# Missing case when using enum in a switch statement
CC_WARNING += -Wswitch-enum
# Trampolines generated for pointers to nested functions
CC_WARNING += -Wtrampolines
# Undefined identifier is evaluated in an #if directive
CC_WARNING += -Wundef
# Loop cannot be optimized
CC_WARNING += -Wunsafe-loop-optimizations
# Floating constants without suffix
CC_WARNING += -Wunsuffixed-float-constants
# Unused static const variables
CC_WARNING += -Wunused-const-variable=2
# Macro is unused
#CC_WARNING += -Wunused-macros
# Vector operation is not implemented via SIMD
CC_WARNING += -Wvector-operation-performance
# use of variable-length array
CC_WARNING += -Wvla
# Writing into a string constant
CC_WARNING += -Wwrite-strings
CC_WARNING += -D_FORTIFY_SOURCE=2
# Treat -Wpedantic warnings as errors
CC_ERROR     := -pedantic-errors
# Treat all warnings as errors
CC_ERROR     += #-Werror
CC_C_VERSION := -std=c17
# Default build mode is debug
CC_DEBUG := -g3
CC_OPTIMIZATION := -O1
CC_PROFILING    := #-pg
# Valgrind doesn't seem to work properly on executables build with --coverage
CC_COVERAGE  := #--coverage
# Directories to be used with the -I option
CC_IDIRS  = $(SRC_DIRS:%=-I%)
CC_IDIRS += $(INC_DIRS:%=-I%)

ifeq ($(BUILD_MODE),release)
    CC_OPTIMIZATION := -O2
    CC_OPTIMIZATION += -fstack-protector-all
    CC_OPTIMIZATION += -fstack-protector-strong
    CC_DEBUG        := -DNDEBUG
endif
CC_OPTIMIZATION += -funsafe-loop-optimizations

# Extra flags for the compiler
CFLAGS  = $(CC_WARNING)
CFLAGS += $(CC_ERROR)
CFLAGS += $(CC_C_VERSION)
CFLAGS += $(CC_DEBUG)
CFLAGS += $(CC_OPTIMIZATION)
CFLAGS += $(CC_ANALYZER)
CFLAGS += $(CC_PROFILING)
CFLAGS += $(CC_COVERAGE)
CFLAGS += $(CC_IDIRS)
CFLAGS += -o $@
# Extra flags for the preprocessor
# MMD  : Create a dependency file which contains a target and its dependencies
# MT $@: Set the target name to the one in the Makefile
# MP   : Create a target for each .h
# MF   : Output path for the .d file
CPPFLAGS = -MMD -MT $@ -MP -MF $(DEP_PATH)/$*.d
# Command to compile *.c files
COMPILE  = $(CC)
COMPILE += $<
COMPILE += -c -fPIC
COMPILE += $(CFLAGS)
COMPILE += $(CPPFLAGS)
# Extra flags (-Lfoo) for the compilator when invoking the linker
LDFLAGS = $(EXTERNAL_LIB_DIRS:%=-L%)
# Libs name (-lfoo) for the compilator when invoking the linker
# Must be put at the very end of a link command
LDLIBS  =
# Command to link *.o files into a program
LINK_PROGRAM  = $(CC)
LINK_PROGRAM += $(CFLAGS)
LINK_PROGRAM += $^
LINK_PROGRAM += $(LDFLAGS)
LINK_PROGRAM += $(LDLIBS)
# Command to link *.o files into a shared library
LINK_SHARED  = $(CC)
LINK_SHARED += $(CFLAGS)
LINK_SHARED += $(LDFLAGS)
LINK_SHARED += -shared
LINK_SHARED += -Wl,-soname,$(LIB_SHARED_X)
LINK_SHARED += $^
LINK_SHARED += $(LDLIBS)
################################################################################
# AR
################################################################################
AR := gcc-ar-11
# Extra flags to give to ar
ARFLAGS  = -rcs
# Command to archive *.o files
ARCHIVE  = $(AR)
ARCHIVE += $(ARFLAGS)
ARCHIVE += $@
ARCHIVE += $^
