# SPDX-License-Identifier: 0BSD
################################################################################
# TARGETS
#
# [R]: Variable can be redefined with a single value.
# [+]: Variable can be redefined and/or have values added to it.
# [X]: Variable must not be redefined nor have values added to it.
################################################################################
# Build project and tests(if there is a test folder) with the default build mode
# (debug).
.PHONY: all
all:: $(PROJECT_DEPS) $(PROJECT_TYPE) $(TEST_TARGET)

# Same as `all` target but also build in release mode.
.PHONY: all_dr
all_dr::
	$(MAKE) all BUILD_MODE=debug
	$(MAKE) all BUILD_MODE=release

# Compile *.c files
$(OBJ_PATH)/%.o: %.c $(OBJ_DEPS)
	$(COMPILE)
################################################################################
# HEADER PROJECT
#
# Project which only provide headers (*.h) and thus does not need to compile
# code(apart from tests).
################################################################################
ifeq ($(PROJECT_TYPE),header)
# Nothing to build for header only project(tests are built with the `test`
# target).
SRC_DIRS :=
COV_CMD :=
.PHONY: header
header::;
endif
################################################################################
# HEADER/LIBRARY PROJECT COMMON
################################################################################
ifneq ($(filter $(PROJECT_TYPE),header shared static),)
# Install header files(*.h)
INSTALL_DEPS := install_header
.PHONY: install_header
install_header:: $(PKG_HEADER_TARGET) | $(HEADER_INSTALL_PATH) $(PKG_PC_INSTALL_PATH)
	cp -r $(INC_PATH)/. $(HEADER_INSTALL_PATH)
	mv $(PKG_PC_NAME) $(PKG_PC_INSTALL_PATH)

# *.pc.in => *.pc
$(PKG_HEADER_TARGET)::
	$(PKG_PC_IN)

# Uninstall header files(*.h/*.pc)
UNINSTALL_DEPS := uninstall_header
.PHONY: uninstall_header
uninstall_header::
	rm -r $(HEADER_INSTALL_PATH)
	rm $(PKG_PC_INSTALL_PATH)/$(PKG_PC_NAME)
endif
################################################################################
# LIBRARY PROJECT
################################################################################
ifneq ($(filter $(PROJECT_TYPE),shared static),)
# Install library files(*.a/*.so)
INSTALL_DEPS := install_lib
.PHONY: install_lib
install_lib:: install_header | $(LIB_INSTALL_PATH)
	cp -ar $(BUILD_PATH)/* $(LIB_INSTALL_PATH)
	find $(EXT_LIB_PATH) -type f,l -exec cp -at $(LIB_INSTALL_PATH) {} +

# Build shared library(*.so)
.PHONY: shared
shared:: $(LIB_SHARED_TARGET)

# *.o => *.so.*
$(LIB_SHARED_TARGET): $(OBJ_FILES) | $(BUILD_PATH)
	$(LINK_SHARED)
	ln -sf $(LIB_SHARED_XYZ) $(LIB_SHARED_X_PATH)
	ln -sf $(LIB_SHARED_X) $(LIB_SHARED_PATH)

# Build static library(*.a)
.PHONY: static
static:: $(LIB_STATIC_TARGET)

# *.o => *.a
$(LIB_STATIC_TARGET): $(OBJ_FILES) | $(BUILD_PATH)
	$(ARCHIVE)

# Uninstall library files(*.a/*.so.*/*.h/*.pc)
UNINSTALL_DEPS := uninstall_lib
.PHONY: uninstall_lib
uninstall_lib:: uninstall_header
	rm -r $(LIB_INSTALL_PATH)
endif
################################################################################
# PROGRAM PROJECT
################################################################################
# Build program
ifeq ($(PROJECT_TYPE),program)
.PHONY: program
program:: $(PROGRAM_TARGET)

# *.o => executable
$(PROGRAM_TARGET): $(OBJ_FILES) | $(BUILD_PATH)
	$(LINK_PROGRAM)

# Run program
RUN_CMD = $(PROGRAM_PATH)
.PHONY: run
run:: $(RUN_DEPS)
	$(RUN_CMD)
endif
################################################################################
# TEST
################################################################################
# Build tests if there is a test folder
ifneq ($(TEST_TARGET),)
.PHONY: test
test::
	$(MAKE) -C $(TEST_PATH) all CC=$(CC) MAKEFILE_PATH=../$(MAKEFILE_PATH)

PRE_PASS_DEPS := pre_pass_test
.PHONY: pre_pass_test
pre_pass_test::
	$(MAKE) -C $(TEST_PATH) pre_pass MAKEFILE_PATH=../$(MAKEFILE_PATH)

# Run tests
.PHONY: check
check:: test
	$(MAKE) -C $(TEST_PATH) run MAKEFILE_PATH=../$(MAKEFILE_PATH)

# Remove test build files
CLEAN_DEPS := clean_test
.PHONY: clean_test
clean_test::
	$(MAKE) -C $(TEST_PATH) clean MAKEFILE_PATH=../$(MAKEFILE_PATH)

# Static analysis
ANALYZE_STATIC_DEPS := analyze_static_test
.PHONY: analyze_static_test
analyze_static_test::
	$(MAKE) -C $(TEST_PATH) analyze_static MAKEFILE_PATH=../$(MAKEFILE_PATH)

# Code coverage
COV_DEPS := cov_test
.PHONY: cov_test
cov_test::
	$(MAKE) -C $(TEST_PATH) cov MAKEFILE_PATH=../$(MAKEFILE_PATH)
endif
################################################################################
# CODE ANALYSIS/COVERAGE - DOC
################################################################################
# Code static analysis
.PHONY: analyze_static
analyze_static:: $(ANALYZE_STATIC_DEPS) | $(ANALYZE_STATIC_DIR_DEPS)
	$(ANALYZE_STATIC_CMD)

# Code coverage
.PHONY: cov
cov:: $(COV_DEPS) | $(COV_DIR_DEPS)
	$(COV_CMD)

# Generate documentation
.PHONY: doc
doc:: $(DOC_DEPS) | $(DOC_DIR_DEPS)
	$(DOC_CMD)
################################################################################
# CLEAN/REBUILD/INSTALL/UNINSTALL/PREPROCESSOR
################################################################################
# Remove build files
CLEAN_CMD = rm -rf $(BUILD_ROOT_PATH)
.PHONY: clean
clean:: $(CLEAN_DEPS)
	$(CLEAN_CMD)

# Remove existing build files and build again
.PHONY: rebuild
rebuild:: clean all

# Install everything
.PHONY: install
install:: $(INSTALL_DEPS)

# Uninstall everything
.PHONY: uninstall
uninstall:: $(UNINSTALL_DEPS)

# Only output the result of the preprocessor pass.
.PHONY: pre_pass
pre_pass:: $(PRE_FILES) $(PRE_PASS_DEPS)

# Implicit rule to output the result of the preprocessor pass.
$(PRE_PATH)/%.pre: %.c $(PRE_DEPS)
	$(PREPROCESSOR)
################################################################################
# HELP
################################################################################
.PHONY: help
help::
	@printf "Usage: make [TARGETS] [OPTIONS]\n"
	@printf "\n"
	@printf " - Unless stated otherwise, all targets are built in '%s' mode.\n" "$(BUILD_MODE)"
	@printf "\n"
	@printf "TARGETS:\n"
	@printf "  all                  : Default target. Build program(s), static/dynamic lib(s) and tests.\n"
	@printf "  all_dr               : Same as 'all' but also build in release mode.\n"
	@printf "  analyze_static       : \n"
	@printf "  check                : Run tests(and build them first if needed).\n"
	@printf "  clean                : \n"
	@printf "  cov                  : Run code coverage tool(s).\n"
	@printf "  doc                  : Build documentation.\n"
	@printf "  install              : Equivalent to calling targets 'install_header' and 'install_lib'.\n"
	@printf "  install_header       : Install headers. Default path is '%s'.\n" "$(HEADER_INSTALL_PATH)"
	@printf "  install_lib          : Instal lib. Default path is '%s'.\n" "$(LIB_INSTALL_PATH)"
	@printf "  pre_pass             : \n"
	@printf "  program              : Build program.\n"
	@printf "  rebuild              : Clean project and rebuild it. Equivalent to calling targets 'clean' and 'all' successively.\n"
	@printf "  run                  : Run program.\n"
	@printf "  shared               : Build shared lib.\n"
	@printf "  static               : Build static lib.\n"
	@printf "  test                 : Build tests.\n"
	@printf "  uninstall            : \n"
	@printf "  uninstall_header     : Uninstall headers.\n"
	@printf "  uninstall_lib        : Uninstall lib.\n"
	@printf "\n"
	@printf "OPTIONS:\n"
	@printf "  BUILD_MODE=<MODE>    : <MODE> must be one of [debug, release]. Default value is '%s'.\n" "$(BUILD_MODE)"
	@printf "  CC=<COMPILER>        : <COMPILER> must be one of [gcc]. Default value is '%s'.\n" "$(CC)"
	@printf "  COVERAGE=<true|false>: Default value is '%s'.\n" "$(COVERAGE)"
	@printf "  DESTDIR=<PATH>       : Default path is '%s'.\n" "$(DESTDIR)"
	@printf "  bindir=<PATH>        : Default path is '%s'.\n" "$(bindir)"
	@printf "  exec_prefix=<PATH>   : Default path is '%s'.\n" "$(exec_prefix)"
	@printf "  includedir=<PATH>    : Default path is '%s'.\n" "$(includedir)"
	@printf "  libdir=<PATH>        : Default path is '%s'.\n" "$(libdir)"
	@printf "  prefix=<PATH>        : Default path is '%s'.\n" "$(prefix)"
################################################################################
# MISC
################################################################################
# Targets to create output directories when they are needed but don't exist yet.
# mkdir -p: No error if directory exists and make parent directories as needed
$(ANALYZE_STATIC_DIR_DEPS): ;mkdir -p $(ANALYZE_STATIC_DIR_DEPS)
$(BUILD_PATH):              ;mkdir -p $(BUILD_PATH)
$(COV_DIR_DEPS):            ;mkdir -p $(COV_DIR_DEPS)
$(DEP_PATH):                ;mkdir -p $(DEP_PATH)
$(DOC_DIR_DEPS):            ;mkdir -p $(DOC_DIR_DEPS)
$(HEADER_INSTALL_PATH):     ;mkdir -p $(HEADER_INSTALL_PATH)
$(LIB_INSTALL_PATH):        ;mkdir -p $(LIB_INSTALL_PATH)
$(OBJ_PATH):                ;mkdir -p $(OBJ_PATH)
$(PKG_PC_INSTALL_PATH):     ;mkdir -p $(PKG_PC_INSTALL_PATH)
$(PRE_PATH):                ;mkdir -p $(PRE_PATH)
# Make each *.d file a target so make won't fail if the file doesn't exist
$(DEP_FILES):
# Only include *.d files if needed
ifeq ($(MAKECMDGOALS),$(findstring $(PROJECT_TYPE),program shared static))
    include $(wildcard $(DEP_FILES))
endif
# Delete files generated by a target which failed(prevent corrupted files)
.DELETE_ON_ERROR:
