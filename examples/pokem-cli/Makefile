CC_WFLAGS	:=	-W -Wall -Wextra -pedantic
CC_OFLAGS	:=	-O2 -funroll-loops
CC_LFLAGS	:=	-Wl,-s -static
CFLAGS		:=	$(CC_WFLAGS) $(CC_OFLAGS)

# Tools
RM			:=	rm
RM_FLAGS	:=	-rf
MKDIR		:=	mkdir
MKDIR_FLAGS	:=	-p
WINDRES		:=	$(shell which windres)

# Directories
LIBDIR		:=	lib
BUILDDIR	:=	build
BINDIR		:=	bin

SOURCES		:=	src/view/view.c \
				src/application/application.c \
				src/utils/utils.c \
				src/main.c

LIBS		:=	pokem

OBJS		:=	$(BUILDDIR)/view.o \
				$(BUILDDIR)/application.o \
				$(BUILDDIR)/utils.o \
				$(BUILDDIR)/main.o

RC_FILE		:=	res/manifest.rc
RC_OBJ		:=	$(BUILDDIR)/res.o

# If no `windres` tool available, the RC object file must be skipped
ifeq ($(WINDRES),)
	RC_OBJ	=
endif

EXECUTABLE	:=	$(BINDIR)/pokeM

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
.PHONY: all clean help

all: $(EXECUTABLE) ## Build Pokem CLI executable (default)

clean: ## Remove all leftovers from the previous build
	@$(MSG) "$(ORANGE)Removing intermediate objects files...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(RC_OBJ) $(OBJS)
	@$(MSG) "$(ORANGE)Removing binaries...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(EXECUTABLE)
	@$(MSG) "$(ORANGE)Removing directories...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(BUILDDIR)
	$(RM) $(RM_FLAGS) $(BINDIR)
	@$(MSG) "$(LIGHTGREEN)Example $(WHITE)pokem-cli$(LIGHTGREEN) cleaned.$(NOCOLOR)\n\n"

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "$(WHITE)%-10s$(NOCOLOR) %s\n", $$1, $$2}'

$(EXECUTABLE): $(BUILDDIR) $(OBJS) $(RC_OBJ) $(BINDIR)
	@$(MSG) "Object files: $(OBJS)\n"
	@$(MSG) "$(YELLOW)Building and linking executable file...$(NOCOLOR)\n"
	$(CC) -o $@ $(CFLAGS) $(CC_LFLAGS) $(OBJS) $(RC_OBJ) -L$(LIBDIR) -l$(LIBS)
	@$(MSG) "$(LIGHTGREEN)Done. The example $(WHITE)pokem-cli$(LIGHTGREEN) was built in the $(LIGHTBLUE)$(BINDIR)$(LIGHTGREEN) directory. Enjoy.$(NOCOLOR)\n"

$(OBJS):
	@$(MSG) "$(GREEN)Compiling $(BLUE)$<$(GREEN)...$(NOCOLOR)\n"
	$(CC) -c $(CFLAGS) $< -o $@

$(RC_OBJ):
	@$(MSG) "$(YELLOW)Building MS Windows's RC file...$(NOCOLOR)\n"
	$(WINDRES) -i $(RC_FILE) -o $@
	@$(MSG) "$(YELLOW)Building intermediate objects files...$(NOCOLOR)\n"

$(BUILDDIR):
	@$(MSG) "$(YELLOW)Creating $@ directory...$(NOCOLOR)\n"
	$(MKDIR) $(MKDIR_FLAGS) $(BUILDDIR)

$(BINDIR):
	@$(MSG) "$(YELLOW)Creating $@ directory...$(NOCOLOR)\n"
	$(MKDIR) $(MKDIR_FLAGS) $(BINDIR)

# Intermediate objects build rules
$(BUILDDIR)/main.o:        		src/main.c
$(BUILDDIR)/application.o:		src/application/application.c
$(BUILDDIR)/view.o:				src/view/view.c
$(BUILDDIR)/utils.o:			src/utils/utils.c