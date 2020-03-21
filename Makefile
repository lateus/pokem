# Compiler
CC			:=	gcc
# Compiler flags
DEFINES		:=	$(if $(filter all-no-colors, $(MAKECMDGOALS)), -DNO_USE_COLORS,)
CC_WFLAGS	:=	-W -Wall -Wextra -pedantic -std=c89
CC_OFLAGS	:=	-O2 -funroll-loops
CC_LFLAGS	:=
CFLAGS		:=	$(CC_OFLAGS) $(CC_WFLAGS) $(DEFINES)
AR_FLAGS	:=	rcs

# Tools
RM			:=	rm
RM_FLAGS	:=	-rf
MKDIR		:=	mkdir
MKDIR_FLAGS	:=	-p
CP			:=	cp
CP_FLAGS	:=	-f
FIND		:=	find

# Directories
BUILDDIR	:=	build
BINLIBDIR	:=	binlib

SOURCES		:=	src/core/Decode/DecodeSos/DecodeSos.c \
				src/core/Decode/DecodeWonderMail/DecodeWonderMail.c \
				src/core/Decode/UtilDecode/UtilDecode.c \
				src/core/Encode/EncodeSos/EncodeSos.c \
				src/core/Encode/EncodeWonderMail/EncodeWonderMail.c \
				src/core/Encode/UtilEncode/UtilEncode.c \
				src/core/Convert/Convert.c \
				src/core/UtilCore/UtilCore.c \
				src/data/md1database/md1database.c \
				src/util/messages.c

OBJECTS		:=	$(BUILDDIR)/DecodeSos.o $(BUILDDIR)/DecodeWonderMail.o $(BUILDDIR)/UtilDecode.o \
				$(BUILDDIR)/EncodeSos.o $(BUILDDIR)/EncodeWonderMail.o $(BUILDDIR)/UtilEncode.o \
				$(BUILDDIR)/Convert.o \
				$(BUILDDIR)/UtilCore.o \
				$(BUILDDIR)/md1database.o \
				$(BUILDDIR)/messages.o

TEST_SUITE	:=	test/CuTest.c test/allTests.c
TEST_FILES	:=	src/core/UtilCore/UtilCore_test.c \
				src/core/Decode/UtilDecode/UtilDecode_test.c \
				src/core/Encode/UtilEncode/UtilEncode_test.c \
				src/core/Decode/DecodeWonderMail/DecodeWonderMail_test.c \
				src/core/Decode/DecodeSos/DecodeSos_test.c \
				src/core/Encode/EncodeWonderMail/EncodeWonderMail_test.c \
				src/core/Encode/EncodeSos/EncodeSos_test.c \
				src/core/Convert/Convert_test.c
TEST_RESULT	:=	$(BUILDDIR)/tests

# Library header
LIB_HEADER_NAME	:=	pokem.h

# Deployment
STATIC_LIB_NAME				:=	libpokem.a
STATIC_LIB_DEPLOY_FILEPATH	:=	$(BINLIBDIR)/$(STATIC_LIB_NAME)

LIB_HEADER_DEPLOY_FILEPATH	:=	$(BINLIBDIR)/$(LIB_HEADER_NAME)

# Messages
MSG			:=	printf
# Colors
NOCOLOR		:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[0m)
BLACK		:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[0;30m)
DARKGRAY	:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[1;30m)
RED			:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[0;31m)
LIGHTRED	:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[1;31m)
GREEN		:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[0;32m)
LIGHTGREEN	:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[1;32m)
ORANGE		:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[0;33m)
YELLOW		:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[1;33m)
BLUE		:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[0;34m)
LIGHTBLUE	:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[1;34m)
PURPLE		:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[0;35m)
LIGHTPURPLE	:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[1;35m)
CYAN		:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[0;36m)
LIGHTCYAN	:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[1;36m)
LIGHTGRAY	:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[0;37m)
WHITE		:=	$(if $(filter -DNO_USE_COLORS, $(DEFINES)),,\033[1;37m)

# ----------------------------------------------------------------------------------------------------

.DEFAULT_GOAL := all
.PHONY: all all-without-colors staticlib clean help

all: $(STATIC_LIB_DEPLOY_FILEPATH) ## Build Pokem library (default)
all-no-colors: $(STATIC_LIB_DEPLOY_FILEPATH) ## Build Pokem library without color support

staticlib: $(BUILDDIR) $(STATIC_LIB_DEPLOY_FILEPATH) ## Build Pokem static library

test: $(TEST_RESULT) ## Build and run tests

clean: ## Remove all leftovers from the previous build
	@$(MSG) "$(YELLOW)Cleaning Pokem...$(NOCOLOR)\n\n"
	@$(MSG) "$(ORANGE)Removing intermediate objects files...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(RM_FLAGS) $(RC_OBJ) $(OBJECTS) $(OBJS)
	@$(MSG) "$(ORANGE)Removing binaries...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(RM_FLAGS) $(STATIC_LIB_DEPLOY_FILEPATH)
	@$(MSG) "$(ORANGE)Removing headers...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(RM_FLAGS) $(STATIC_H)
	@$(MSG) "$(ORANGE)Removing tests...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(RM_FLAGS) $(TEST_RESULT)
	@$(MSG) "$(ORANGE)Removing directories...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(BUILDDIR)
	$(RM) $(RM_FLAGS) $(BINLIBDIR)

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "$(WHITE)%-16s$(NOCOLOR) %s\n", $$1, $$2}'

# Static library header
$(LIB_HEADER_DEPLOY_FILEPATH): $(BINLIBDIR)
	@$(MSG) "$(YELLOW)Deploying the static library header file...$(NOCOLOR)\n"
	@$(MSG) "#ifndef POKEM_H\n" > $@
	@$(MSG) "#define POKEM_H\n" >> $@
	@$(MSG) "\n/** DEFINITIONS AND DATABASE: */\n" >> $@
	@$(FIND) src/data -path "*.h" -type f -exec tools/printSingleHeaderContent.sh {} \; | grep -v '#include "' >> $@
	@$(MSG) "\n/** CORE FUNCTIONALITIES: */\n" >> $@
	@$(FIND) src/core -path "*.h" -type f -exec tools/printSingleHeaderContent.sh {} \; | grep -v '#include "' >> $@
	@$(MSG) "\n#endif /* POKEM_H */" >> $@

# Static library
$(STATIC_LIB_DEPLOY_FILEPATH): $(BUILDDIR) $(BINLIBDIR) $(OBJECTS) $(LIB_HEADER_DEPLOY_FILEPATH)
	@$(MSG) "$(YELLOW)Building and linking static library file...$(NOCOLOR)\n"
	$(AR) $(AR_FLAGS) $@ $(OBJECTS)
	@$(MSG) "\n$(LIGHTGREEN)Done. The static library was built in the $(LIGHTBLUE)$(BINLIBDIR)$(LIGHTGREEN) directory.$(NOCOLOR)\n\n"

$(TEST_RESULT): $(BUILDDIR) $(TEST_FILES)
	@$(MSG) "$(LIGHTGREEN)Building tests...$(NOCOLOR)\n"
	$(CC) -o $@ $(TEST_SUITE) $(TEST_FILES) $(SOURCES)
	@$(MSG) "$(LIGHTGREEN)Running tests...$(NOCOLOR)\n"
	@$@

$(OBJECTS):
	@$(MSG) "$(GREEN)Compiling $(BLUE)$<$(GREEN)...$(NOCOLOR)\n"
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR):
	@$(MSG) "$(YELLOW)Creating $@ directory...$(NOCOLOR)\n"
	$(MKDIR) $(MKDIR_FLAGS) $(BUILDDIR)

$(BINLIBDIR):
	@$(MSG) "$(YELLOW)Creating $@ directory...$(NOCOLOR)\n"
	$(MKDIR) $(MKDIR_FLAGS) $(BINLIBDIR)

# Intermediate objects build rules
$(BUILDDIR)/DecodeSos.o:        src/core/Decode/DecodeSos/DecodeSos.c
$(BUILDDIR)/DecodeWonderMail.o: src/core/Decode/DecodeWonderMail/DecodeWonderMail.c
$(BUILDDIR)/UtilDecode.o:       src/core/Decode/UtilDecode/UtilDecode.c
$(BUILDDIR)/EncodeSos.o:        src/core/Encode/EncodeSos/EncodeSos.c
$(BUILDDIR)/EncodeWonderMail.o: src/core/Encode/EncodeWonderMail/EncodeWonderMail.c
$(BUILDDIR)/UtilEncode.o:       src/core/Encode/UtilEncode/UtilEncode.c
$(BUILDDIR)/Convert.o:          src/core/Convert/Convert.c
$(BUILDDIR)/UtilCore.o:         src/core/UtilCore/UtilCore.c
$(BUILDDIR)/md1database.o:      src/data/md1database/md1database.c
$(BUILDDIR)/messages.o:      	src/util/messages.c