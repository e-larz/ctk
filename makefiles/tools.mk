################################################################################
# CPPCHECK
################################################################################
CPPCHECK_PATH := $(ANALYSIS_PATH)/cppcheck
CPPCHECK := cppcheck
# Enable all checks
CPPCHECK += --enable=all
CPPCHECK += --force
# Allow reports even if the analysis is inconclusive
CPPCHECK += --inconclusive
CPPCHECK += --language=c
CPPCHECK += --platform=unix64
# Only print if there is an error
CPPCHECK += --quiet
CPPCHECK += --std=c11
#CPPCHECK += -I./$(HEADER_PATH)
CPPCHECK += . 2> $(CPPCHECK_PATH)/cppcheck
################################################################################
# DOXYGEN
################################################################################
DOXYGEN_PATH := $(DOC_PATH)/doxygen
DOXYGEN := doxygen
################################################################################
# GCOV
################################################################################
GCOV_PATH := $(ANALYSIS_PATH)/gcov
GCOV := gcov
GCOV += --all-blocks
GCOV += --branch-counts
GCOV += --branch-probabilities
GCOV += --demangled-names
#GCOV += --function-summaries
GCOV += --long-file-names
GCOV += --relative-only
GCOV += -o $(OBJ_PATH) $(OBJ_DEPS) $(TEST_OBJ_FILES)
################################################################################
# LCOV
################################################################################
LCOV_PATH := $(ANALYSIS_PATH)/lcov
LCOV = lcov
LCOV += --capture
LCOV += --directory .
LCOV += --no-external
LCOV += --quiet
LCOV += --rc lcov_branch_coverage=1
LCOV += -o $@

INFO_FILES := $(wildcard $(OBJ_PATH)/*.o)
INFO_FILES := $(notdir $(INFO_FILES:.o=.info))
INFO_FILES := $(INFO_FILES:%=$(LCOV_PATH)/%)

LCOV_TARGET := $(addprefix -a , $(INFO_FILES))

LCOV_FINAL := lcov
LCOV_FINAL += --quiet
LCOV_FINAL += --rc lcov_branch_coverage=1
LCOV_FINAL += -o $(LCOV_PATH)/test.info
LCOV_FINAL += $(LCOV_TARGET)

GENHTML := genhtml
GENHTML += --branch-coverage
GENHTML += --function-coverage
GENHTML += --quiet
GENHTML += --show-details
GENHTML += -o $(LCOV_PATH) $(LCOV_PATH)/test.info
################################################################################
# SCANBUILD
################################################################################
SCANBUILD_PATH := $(ANALYSIS_PATH)/scanbuild
SCANBUILD := scan-build
SCANBUILD += -analyze-headers
SCANBUILD += -o $(SCANBUILD_PATH)
SCANBUILD += make --silent all
################################################################################
# VALGRIND
################################################################################
VALGRIND_PATH := $(ANALYSIS_PATH)/valgrind
MEMCHECK := --leak-check=full
MEMCHECK += --show-leak-kinds=all
MEMCHECK += --track-origins=yes
VALGRIND := valgrind $(MEMCHECK) $(TEST_EXE) 2> $(VALGRIND_PATH)/valgrind
