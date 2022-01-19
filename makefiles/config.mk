# SPDX-License-Identifier: 0BSD
################################################################################
# [R]: Variable can be redefined with a single value.
# [+]: Variable can be redefined and/or have values added to it.
# [X]: Variable must not be redefined nor have values added to it.
################################################################################
# Set `all` as the default target.
.DEFAULT_GOAL := all

# Eliminate use of the built-in rule-specific variables(--no-builtin-variables).
# Eliminate use of the built-in implicit rules(--no-builtin-rules/-r).
MAKEFLAGS += -R

# Makefiles used to configure aspects of the project.
# No target are present in these.
include $(MAKEFILE_PATH)/project.mk
include $(MAKEFILE_PATH)/cc.mk
include $(MAKEFILE_PATH)/tools.mk

# Abort Make with an error message when some variables contain invalid values
ifeq ($(filter $(PROJECT_TYPE),header program shared static),)
    $(error PROJECT_TYPE must be one of [header, program, shared, static])
endif

ifeq ($(filter $(BUILD_MODE),debug release),)
    $(error BUILD_MODE must be one of [debug, release])
endif

ifeq ($(filter $(COVERAGE),true false),)
    $(error COVERAGE must be one of [true, false])
endif

ifneq ($(filter $(MAKECMDGOALS),analyze_static),)
  ifeq ($(ANALYSIS_STATIC_CMD),true)
    $(error No tools found to analyze code!)
  endif
endif

ifneq ($(filter $(MAKECMDGOALS),cov),)
  ifeq ($(COV_CMD),true)
    $(error No tools found to make code coverage!)
  endif
endif

ifneq ($(filter $(MAKECMDGOALS),doc),)
  ifeq ($(DOC_CMD),true)
    $(error No tools found to build documentation!)
  endif
endif
