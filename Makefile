CC_WFLAGS	:=	-W -Wall -Wextra
CC_OFLAGS	:=	-O2 -funroll-loops
CC_LFLAGS	:=	-Wl,-s -static
CFLAGS		:=	$(CC_WFLAGS) $(CC_OFLAGS) $(CC_LFLAGS)

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

MSG			:=	echo

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
	@$(MSG) "Creating executable file..."
	$(CC) $(CFLAGS) $(OBJS) -o $@
	@$(MSG) "Done. The program was build in the \"bin\" directory."
	@$(MSG) "You can run it by typing \"cd bin && ./pokeMail\". Enjoy."

$(OBJS):
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILDDIR):
	@$(MSG) "Creating build directory..."
	$(MKDIR) $(MKDIR_FLAGS) $(BUILDDIR)

$(BINDIR):
	@$(MSG) "Creating bin directory..."
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
	@$(MSG) "Removing intermediate objects files..."
	@$(RM) $(RM_FLAGS) $(OBJS)
	@$(MSG) "Removing executable..."
	@$(RM) $(RM_FLAGS) $(EXECUTABLE)
	@$(MSG) "Removing directories..."
	@$(RM) $(RMDIR_FLAGS) $(BUILDDIR) $(BINDIR)
	@$(MSG) "Done."