# SPDX-License-Identifier: 0BSD
################################################################################
# TEST
################################################################################
include $(MAKEFILE_PATH)/config.mk
PROJECT  := test
SRC_DIRS := .
INC_DIRS := ../$(INC_PATH)
LDFLAGS  := -L../build/$(BUILD_MODE)
LDLIBS   := -Wl,-rpath,../build/$(BUILD_MODE)
LDLIBS   += -lctk
################################################################################
# TARGETS
################################################################################
# Default targets
include $(MAKEFILE_PATH)/targets.mk
