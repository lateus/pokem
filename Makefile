CC_WFLAGS	:=	-W -Wall -Wextra
CC_OFLAGS	:=	-O2 -funroll-loops
CC_LFLAGS	:=	-Wl,-s -static
CFLAGS		:=	$(CC_WFLAGS) $(CC_OFLAGS)

# DIRECTORIES
BUILDDIR	:=	build
BINDIR		:=	bin

SRCS		:=	src/main.c src/application.c \
				src/model/md1database.c \
				src/decode_encode/dec_enc_common.c \
				src/decode_encode/encode/enc_wm.c src/decode_encode/encode/enc_sos.c src/decode_encode/encode/encode.c \
				src/decode_encode/decode/dec_wm.c src/decode_encode/decode/dec_sos.c src/decode_encode/decode/decode.c \
				src/decode_encode/convert/convert.c \
				src/view/view.c

OBJS		:=	$(BUILDDIR)/main.o $(BUILDDIR)/application.o \
				$(BUILDDIR)/md1database.o \
				$(BUILDDIR)/dec_enc_common.o \
				$(BUILDDIR)/enc_wm.o $(BUILDDIR)/enc_sos.o $(BUILDDIR)/encode.o \
				$(BUILDDIR)/dec_wm.o $(BUILDDIR)/dec_sos.o $(BUILDDIR)/decode.o \
				$(BUILDDIR)/convert.o \
				$(BUILDDIR)/view.o

RC_FILE		:=	res/manifest.rc
STATIC_LIB	:=	libpokeMail.a

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
	WINRES		:=	windres
	EXECUTABLE	:=	$(BINDIR)/pokeMail.exe
	RES_OBJS	:=	$(BUILDDIR)/res.o
	RM_FLAGS	:=
	RMDIR_FLAGS	:=
	MKDIR		:=	md
	MKDIR_FLAGS	:=
else
	WINRES		:=
	EXECUTABLE	:=	$(BINDIR)/pokeMail
	RES_OBJS	:=
	RM_FLAGS	:=
	RMDIR_FLAGS	:=	-frd
	MKDIR		:=	mkdir
	MKDIR_FLAGS	:=	-p
endif

.PHONY: all
all: $(BUILDDIR) $(EXECUTABLE)

$(EXECUTABLE): $(OBJS) $(BINDIR)
	@$(MSG) "$(YELLOW)Building and linking executable file...$(NOCOLOR)\n"
	$(CC) $(CFLAGS) $(CC_LFLAGS) $(OBJS) -o $@
	@$(MSG) "$(GREEN)Done. The program was build in the $(YELLOW)bin$(GREEN) directory.$(NOCOLOR)\n"
	@$(MSG) "$(GREEN)You can run it by typing: $(YELLOW)cd bin && ./pokeMail$(GREEN). Enjoy.$(NOCOLOR)\n"

$(OBJS):
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR):
	@$(MSG) "$(YELLOW)Creating build directory...$(NOCOLOR)\n"
	$(MKDIR) $(MKDIR_FLAGS) $(BUILDDIR)
	@$(MSG) "$(YELLOW)Building intermediate objects files...$(NOCOLOR)\n"

$(BINDIR):
	@$(MSG) "$(YELLOW)Creating bin directory...$(NOCOLOR)\n"
	$(MKDIR) $(MKDIR_FLAGS) $(BINDIR)

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

.PHONY: clean
clean:
	@$(MSG) "$(ORANGE)Removing intermediate objects files...$(NOCOLOR)\n"
	@$(RM) $(RM_FLAGS) $(OBJS)
	@$(MSG) "$(ORANGE)Removing executable...$(NOCOLOR)\n"
	@$(RM) $(RM_FLAGS) $(EXECUTABLE)
	@$(MSG) "$(ORANGE)Removing directories...$(NOCOLOR)\n"
	@$(RM) $(RMDIR_FLAGS) $(BUILDDIR) $(BINDIR)
	@$(MSG) "$(GREEN)Done.$(NOCOLOR)\n"