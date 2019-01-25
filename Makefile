CC_WFLAGS	:=	-W -Wall -Wextra
CC_OFLAGS	:=	-O2 -funroll-loops
CC_LFLAGS	:=	-Wl,-s -static
CFLAGS		:=	$(CC_WFLAGS) $(CC_OFLAGS)

# DIRECTORIES
BUILDDIR	:=	build
BINDIR		:=	bin
BINLIBDIR	:=	binlib

SRCS		:=	src/main.c src/application.c \
				src/model/md1database.c \
				src/decode_encode/dec_enc_common.c \
				src/decode_encode/encode/enc_wm.c src/decode_encode/encode/enc_sos.c src/decode_encode/encode/encode.c \
				src/decode_encode/decode/dec_wm.c src/decode_encode/decode/dec_sos.c src/decode_encode/decode/decode.c \
				src/decode_encode/convert/convert.c \
				src/view/view.c

OBJS		:=	$(BUILDDIR)/main.o $(BUILDDIR)/application.o $(BUILDDIR)/view.o

OBJS_SLIB	:=	$(BUILDDIR)/md1database.o \
				$(BUILDDIR)/dec_enc_common.o \
				$(BUILDDIR)/enc_wm.o $(BUILDDIR)/enc_sos.o $(BUILDDIR)/encode.o \
				$(BUILDDIR)/dec_wm.o $(BUILDDIR)/dec_sos.o $(BUILDDIR)/decode.o \
				$(BUILDDIR)/convert.o

STATIC_LIB	:=	$(BINLIBDIR)/libpokem.a
STATIC_HDR	:=	$(BINLIBDIR)/pokem.h

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

.PHONY: all
all: $(EXECUTABLE)

.PHONY: staticlib
staticlib: $(BUILDDIR) $(STATIC_LIB)

.PHONY: clean
clean:
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

$(EXECUTABLE): $(BUILDDIR) $(RC_OBJ) $(OBJS_SLIB) $(OBJS) $(BINDIR)
	@$(MSG) "$(YELLOW)Building and linking executable file...$(NOCOLOR)\n"
	$(CC) $(CFLAGS) $(CC_LFLAGS) $(RC_OBJ) $(OBJS_SLIB) $(OBJS) -o $@
	@$(MSG) "$(GREEN)Done. The program was build in the $(LIGHTBLUE)$(BINDIR)$(GREEN) directory.$(NOCOLOR)\n"
	@$(MSG) "$(GREEN)You can run it by typing: $(WHITE)./$(EXECUTABLE)$(GREEN). Enjoy.$(NOCOLOR)\n"

$(STATIC_LIB): $(BINLIBDIR) $(OBJS_SLIB)
	@$(MSG) "$(YELLOW)Building and linking static library file...$(NOCOLOR)\n"
	$(AR) $(AR_FLAGS) $@ $(OBJS_SLIB)
	@$(MSG) "$(YELLOW)Copying the static library header file...$(NOCOLOR)\n"
	$(CP) include/staticlib.h $(STATIC_HDR)
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
$(BUILDDIR)/main.o:				src/main.c
$(BUILDDIR)/application.o:		src/application.c
$(BUILDDIR)/md1database.o:		src/model/md1database.c
$(BUILDDIR)/dec_enc_common.o:	src/decode_encode/dec_enc_common.c
$(BUILDDIR)/enc_wm.o:			src/decode_encode/encode/enc_wm.c
$(BUILDDIR)/enc_sos.o:			src/decode_encode/encode/enc_sos.c
$(BUILDDIR)/encode.o:			src/decode_encode/encode/encode.c
$(BUILDDIR)/dec_wm.o:			src/decode_encode/decode/dec_wm.c
$(BUILDDIR)/dec_sos.o:			src/decode_encode/decode/dec_sos.c
$(BUILDDIR)/decode.o:			src/decode_encode/decode/decode.c
$(BUILDDIR)/convert.o:			src/decode_encode/convert/convert.c
$(BUILDDIR)/view.o:				src/view/view.c