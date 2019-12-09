# Compiler flags
CC_WFLAGS	:=	-W -Wall -Wextra -pedantic
CC_OFLAGS	:=	-O2 -funroll-loops
CC_LFLAGS	:=
CFLAGS		:=	$(CC_OFLAGS) $(CC_WFLAGS)
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
				src/data/md1database/md1database.c

OBJECTS		:=	$(BUILDDIR)/DecodeSos.o $(BUILDDIR)/DecodeWonderMail.o $(BUILDDIR)/UtilDecode.o \
				$(BUILDDIR)/EncodeSos.o $(BUILDDIR)/EncodeWonderMail.o $(BUILDDIR)/UtilEncode.o \
				$(BUILDDIR)/Convert.o \
				$(BUILDDIR)/UtilCore.o \
				$(BUILDDIR)/md1database.o

TEST_SUITE	:=	test/CuTest.c test/allTests.c
TEST_FILES	:=	src/core/UtilCore/UtilCore_test.c \
				src/core/Decode/UtilDecode/UtilDecode_test.c \
				src/core/Encode/UtilEncode/UtilEncode_test.c \
				src/core/Decode/DecodeWonderMail/DecodeWonderMail_test.c \
				src/core/Decode/DecodeSos/DecodeSos_test.c
TEST_RESULT	:=	$(BUILDDIR)/tests

# Library header
LIB_HEADER_NAME	:=	pokem.h

# Examples
EXAMPLES_DIR	:=	examples
EXAMPLES		:=	$(EXAMPLES_DIR)/pokem-cli

# Deployment
STATIC_LIB_NAME				:=	libpokem.a
STATIC_LIB_DEPLOY_FILEPATH	:=	$(BINLIBDIR)/$(STATIC_LIB_NAME)

LIB_HEADER_DEPLOY_FILEPATH	:=	$(BINLIBDIR)/$(LIB_HEADER_NAME)

# Messages
MSG			:=	echo -n
# Colors
NOCOLOR		:=	\033[0m
BLACK		:=	\033[0;30m
DARKGRAY	:=	\033[1;30m
RED			:=	\033[0;31m
LIGHTRED	:=	\033[1;31m
GREEN		:=	\033[0;32m
LIGHTGREEN	:=	\033[1;32m
ORANGE		:=	\033[0;33m
YELLOW		:=	\033[1;33m
BLUE		:=	\033[0;34m
LIGHTBLUE	:=	\033[1;34m
PURPLE		:=	\033[0;35m
LIGHTPURPLE	:=	\033[1;35m
CYAN		:=	\033[0;36m
LIGHTCYAN	:=	\033[1;36m
LIGHTGRAY	:=	\033[0;37m
WHITE		:=	\033[1;37m

# ----------------------------------------------------------------------------------------------------

.DEFAULT_GOAL := all
.PHONY: all staticlib examples tests clean help

all: $(EXAMPLES) $(STATIC_LIB_DEPLOY_FILEPATH) $(TEST_RESULT) ## Build Pokem library, examples and tests (default)

staticlib: $(BUILDDIR) $(STATIC_LIB_DEPLOY_FILEPATH) ## Build Pokem static library

examples: $(EXAMPLES) ## Build examples

tests: $(TEST_RESULT) ## Build and run tests

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
	@$(MSG) "\n$(YELLOW)Cleaning examples...$(NOCOLOR)\n"
	@$(MSG) "\n$(WHITE)pokem-cli$(NOCOLOR)\n"
	@$(MAKE) --directory $(EXAMPLES_DIR)/pokem-cli clean
	@$(MSG) "\n$(LIGHTGREEN)Project $(WHITE)Pokem$(LIGHTGREEN) cleaned.$(NOCOLOR)\n\n"

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {$(MSG) "$(WHITE)%-20s$(NOCOLOR) %s\n", $$1, $$2}'

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

$(EXAMPLES): $(STATIC_LIB_DEPLOY_FILEPATH)
	@$(MSG) "$(LIGHTBLUE)Building $(WHITE)$@$(LIGHTBLUE)...$(NOCOLOR)\n"
	@$(MSG) "$(YELLOW)Updating static library...$(NOCOLOR)\n"
	$(CP) $(CP_FLAGS) $(STATIC_LIB_DEPLOY_FILEPATH) $@/lib/$(STATIC_LIB_NAME)
	$(CP) $(CP_FLAGS) $(LIB_HEADER_DEPLOY_FILEPATH) $@/lib/$(LIB_HEADER_NAME)
	@$(MAKE) --directory $@

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