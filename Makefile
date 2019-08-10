CC_WFLAGS	:=	-W -Wall -Wextra
CC_OFLAGS	:=	-O2 -funroll-loops
CC_LFLAGS	:=	-Wl,-s -static
CFLAGS		:=	$(CC_WFLAGS) $(CC_OFLAGS)

# DIRECTORIES
BUILDDIR	:=	build
BINLIBDIR	:=	binlib

SOURCES		:=	src/core/Decode/DecodeSOS/DecodeSOS.c \
				src/core/Decode/DecodeWonderMail/DecodeWonderMail.c \
				src/core/Decode/UtilDecode/UtilDecode.c \
				src/core/Encode/EncodeSOS/EncodeSOS.c \
				src/core/Encode/EncodeWonderMail/EncodeWonderMail.c \
				src/core/Encode/UtilEncode/UtilEncode.c \
				src/core/Convert/Convert.c \
				src/core/UtilCore/UtilCore.c \
				src/data/md1database/md1database.c

OBJS_SLIB	:=	$(BUILDDIR)/DecodeSOS.o $(BUILDDIR)/DecodeWonderMail.o $(BUILDDIR)/UtilDecode.o \
				$(BUILDDIR)/EncodeSOS.o $(BUILDDIR)/EncodeWonderMail.o $(BUILDDIR)/UtilEncode.o \
				$(BUILDDIR)/Convert.o \
				$(BUILDDIR)/UtilCore.o \
				$(BUILDDIR)/md1database.o

LIB_HEADER_NAME		:=	pokem.h
LIB_HEADER_FILEPATH	:=	src/lib/$(LIB_HEADER_NAME)

# Examples
EXAMPLES_DIR	:=	examples
EXAMPLES		:=	$(EXAMPLES_DIR)/pokem-cli

# Deployment
STATIC_LIB_NAME				:=	libpokem.a
STATIC_LIB_DEPLOY_FILEPATH	:=	$(BINLIBDIR)/$(STATIC_LIB_NAME)

LIB_HEADER_DEPLOY_FILEPATH	:=	$(BINLIBDIR)/$(LIB_HEADER_NAME)

AR_FLAGS	:=	rcs

# Platform-specific switches
ifeq ($(OS),Windows_NT)
	SHELL		:=	cmd
	RM			:=	del
	CP			:=	cp
	CC			:=	gcc
	RMDIR		:=	rd
	RM_FLAGS	:=
	RMDIR_FLAGS	:=
	MKDIR		:=	mkdir
	MKDIR_FLAGS	:=
else
	RMDIR		:=	$(RM)
	CP			:=	cp
	CP_FLAGS	:=	-f
	RM_FLAGS	:=
	RMDIR_FLAGS	:=	-frd
	MKDIR		:=	mkdir
	MKDIR_FLAGS	:=	-p
endif

# MESSAGES
MSG			:=	printf
# COLORS
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

.DEFAULT_GOAL := all
.PHONY: all staticlib examples clean help

all: $(EXAMPLES) $(STATIC_LIB_DEPLOY_FILEPATH) ## Build Pokem project (default)

staticlib: $(BUILDDIR) $(STATIC_LIB_DEPLOY_FILEPATH) ## Build Pokem static library

examples: $(EXAMPLES) ## Build examples

clean: ## Remove all leftovers from the previous build
	@$(MSG) "$(ORANGE)Removing intermediate objects files...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(RC_OBJ) $(OBJS_SLIB) $(OBJS)
	@$(MSG) "$(ORANGE)Removing binaries...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(STATIC_LIB_DEPLOY_FILEPATH)
	@$(MSG) "$(ORANGE)Removing headers...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(STATIC_H)
	@$(MSG) "$(ORANGE)Removing directories...$(NOCOLOR)\n"
	$(RMDIR) $(RMDIR_FLAGS) $(BUILDDIR)
	$(RMDIR) $(RMDIR_FLAGS) $(BINLIBDIR)
	@$(MSG) "\n$(ORANGE)Cleaning examples...$(NOCOLOR)\n"
	@$(MSG) "\n$(WHITE)pokem-cli$(NOCOLOR)\n"
	@$(MAKE) --directory $(EXAMPLES_DIR)/pokem-cli clean
	@$(MSG) "\n$(LIGHTGREEN)Project $(WHITE)Pokem$(LIGHTGREEN) cleaned.$(NOCOLOR)\n\n"

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {$(MSG) "$(WHITE)%-20s$(NOCOLOR) %s\n", $$1, $$2}'

$(STATIC_LIB_DEPLOY_FILEPATH): $(BUILDDIR) $(BINLIBDIR) $(OBJS_SLIB)
	@$(MSG) "$(YELLOW)Building and linking static library file...$(NOCOLOR)\n"
	$(AR) $(AR_FLAGS) $@ $(OBJS_SLIB)
	@$(MSG) "$(YELLOW)Deploying the static library header file...$(NOCOLOR)\n"
	$(CP) $(CP_FLAGS) $(LIB_HEADER_FILEPATH) $(LIB_HEADER_DEPLOY_FILEPATH)
	@$(MSG) "\n$(LIGHTGREEN)Done. The static library was built in the $(LIGHTBLUE)$(BINLIBDIR)$(LIGHTGREEN) directory.$(NOCOLOR)\n\n"

$(EXAMPLES): $(STATIC_LIB_DEPLOY_FILEPATH)
	@$(MSG) "$(LIGHTBLUE)Building $(WHITE)$@$(LIGHTBLUE)...$(NOCOLOR)\n"
	@$(MSG) "$(YELLOW)Updating static library...$(NOCOLOR)\n"
	$(CP) $(CP_FLAGS) $(STATIC_LIB_DEPLOY_FILEPATH) $@/lib/$(STATIC_LIB_NAME)
	$(CP) $(CP_FLAGS) $(LIB_HEADER_DEPLOY_FILEPATH) $@/lib/$(LIB_HEADER_NAME)
	@$(MAKE) --directory $@

$(OBJS_SLIB):
	@$(MSG) "$(GREEN)Compiling $(LIGHTBLUE)$<$(GREEN)...$(NOCOLOR)\n"
	@$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR):
	@$(MSG) "$(YELLOW)Creating $@ directory...$(NOCOLOR)\n"
	$(MKDIR) $(MKDIR_FLAGS) $(BUILDDIR)

$(BINLIBDIR):
	@$(MSG) "$(YELLOW)Creating $@ directory...$(NOCOLOR)\n"
	$(MKDIR) $(MKDIR_FLAGS) $(BINLIBDIR)

# INTERMEDIATE OBJECTS BUILD RULES
$(BUILDDIR)/DecodeSOS.o:        src/core/Decode/DecodeSOS/DecodeSOS.c
$(BUILDDIR)/DecodeWonderMail.o: src/core/Decode/DecodeWonderMail/DecodeWonderMail.c
$(BUILDDIR)/UtilDecode.o:       src/core/Decode/UtilDecode/UtilDecode.c
$(BUILDDIR)/EncodeSOS.o:        src/core/Encode/EncodeSOS/EncodeSOS.c
$(BUILDDIR)/EncodeWonderMail.o: src/core/Encode/EncodeWonderMail/EncodeWonderMail.c
$(BUILDDIR)/UtilEncode.o:       src/core/Encode/UtilEncode/UtilEncode.c
$(BUILDDIR)/Convert.o:          src/core/Convert/Convert.c
$(BUILDDIR)/UtilCore.o:         src/core/UtilCore/UtilCore.c
$(BUILDDIR)/md1database.o:      src/data/md1database/md1database.c
