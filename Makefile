CC_WFLAGS	:=	-W -Wall -Wextra
CC_OFLAGS	:=	-O2 -funroll-loops
CC_LFLAGS	:=	-Wl,-s -static
CFLAGS		:=	$(CC_WFLAGS) $(CC_OFLAGS)

# DIRECTORIES
BUILDDIR	:=	build
BINDIR		:=	bin
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

OBJS		:=	$(BUILDDIR)/main.o $(BUILDDIR)/application.o $(BUILDDIR)/view.o

OBJS_SLIB	:=	$(BUILDDIR)/DecodeSOS.o $(BUILDDIR)/DecodeWonderMail.o $(BUILDDIR)/UtilDecode.o \
				$(BUILDDIR)/EncodeSOS.o $(BUILDDIR)/EncodeWonderMail.o $(BUILDDIR)/UtilEncode.o \
				$(BUILDDIR)/Convert.o \
				$(BUILDDIR)/UtilCore.o \
				$(BUILDDIR)/md1database.o

LIB_HEADER      :=      src/lib/pokem.h

STATIC_LIB	:=	$(BINLIBDIR)/libpokem.a
STATIC_HEADER	:=	$(BINLIBDIR)/pokem.h

AR_FLAGS	:=	rcs

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

# Platform-specific switches
ifeq ($(OS),Windows_NT)
	SHELL		:=	cmd
	RM			:=	del
	CP			:=	cp
	CC			:=	gcc
	RMDIR		:=	rd
	WINRES		:=	windres
	EXECUTABLE	:=	$(BINDIR)/pokeM.exe
	RC_FILE		:=	res/manifest.rc
	RC_OBJ		:=	$(BUILDDIR)/res.o
	RM_FLAGS	:=
	RMDIR_FLAGS	:=
	MKDIR		:=	mkdir
	MKDIR_FLAGS	:=
else
	RMDIR		:=	$(RM)
	CP			:=	cp
	WINRES		:=
	EXECUTABLE	:=	$(BINDIR)/pokeM
	RC_FILE		:=
	RC_OBJ		:=
	RM_FLAGS	:=
	RMDIR_FLAGS	:=	-frd
	MKDIR		:=	mkdir
	MKDIR_FLAGS	:=	-p
endif

.DEFAULT_GOAL := all
.PHONY: all staticlib clean help

all: $(STATIC_LIB) ## Build Pokem project

staticlib: $(BUILDDIR) $(STATIC_LIB) ## Build Pokem static library (default)

clean: ## Remove all leftovers from the previous build
	@$(MSG) "$(ORANGE)Removing intermediate objects files...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(RC_OBJ) $(OBJS_SLIB) $(OBJS)
	@$(MSG) "$(ORANGE)Removing binaries...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(EXECUTABLE)
	$(RM) $(RM_FLAGS) $(STATIC_LIB)
	@$(MSG) "$(ORANGE)Removing headers...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(STATIC_HDR)
	@$(MSG) "$(ORANGE)Removing directories...$(NOCOLOR)\n"
	$(RMDIR) $(RMDIR_FLAGS) $(BUILDDIR)
	$(RMDIR) $(RMDIR_FLAGS) $(BINDIR)
	$(RMDIR) $(RMDIR_FLAGS) $(BINLIBDIR)
	@$(MSG) "$(GREEN)Done.$(NOCOLOR)\n"

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {$(MSG) "$(WHITE)%-20s$(NOCOLOR) %s\n", $$1, $$2}'

$(EXECUTABLE): $(BUILDDIR) $(RC_OBJ) $(OBJS_SLIB) $(OBJS) $(BINDIR)
	@$(MSG) "$(YELLOW)Building and linking executable file...$(NOCOLOR)\n"
	$(CC) $(CFLAGS) $(CC_LFLAGS) $(RC_OBJ) $(OBJS_SLIB) $(OBJS) -o $@
	@$(MSG) "$(GREEN)Done. The program was build in the $(LIGHTBLUE)$(BINDIR)$(GREEN) directory.$(NOCOLOR)\n"
	@$(MSG) "$(GREEN)You can run it by typing: $(WHITE)./$(EXECUTABLE)$(GREEN). Enjoy.$(NOCOLOR)\n"

$(STATIC_LIB): $(BUILDDIR) $(BINLIBDIR) $(OBJS_SLIB)
	@$(MSG) "$(YELLOW)Building and linking static library file...$(NOCOLOR)\n"
	$(AR) $(AR_FLAGS) $@ $(OBJS_SLIB)
	@$(MSG) "$(YELLOW)Copying the static library header file...$(NOCOLOR)\n"
	$(CP) $(LIB_HEADER) $(STATIC_HEADER)
	@$(MSG) "$(GREEN)Done. The static library was build in the $(LIGHTBLUE)$(BINLIBDIR)$(GREEN) directory.$(NOCOLOR)\n"

$(OBJS):
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJS_SLIB):
	$(CC) -c $(CFLAGS) $< -o $@

$(RC_OBJ):
	@$(MSG) "$(YELLOW)Building MS Windows's RC file...$(NOCOLOR)\n"
	$(WINRES) -i $(RC_FILE) -o $@
	@$(MSG) "$(YELLOW)Building intermediate objects files...$(NOCOLOR)\n"

$(BUILDDIR):
	@$(MSG) "$(YELLOW)Creating $@ directory...$(NOCOLOR)\n"
	$(MKDIR) $(MKDIR_FLAGS) $(BUILDDIR)

$(BINDIR):
	@$(MSG) "$(YELLOW)Creating $@ directory...$(NOCOLOR)\n"
	$(MKDIR) $(MKDIR_FLAGS) $(BINDIR)

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
