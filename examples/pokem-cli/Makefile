CC_WFLAGS	:=	-W -Wall -Wextra -pedantic
CC_OFLAGS	:=	-O2 -funroll-loops
CC_LFLAGS	:=	-Wl,-s -static
CFLAGS		:=	$(CC_WFLAGS) $(CC_OFLAGS)

# DIRECTORIES
LIBDIR		:=	lib
BUILDDIR	:=	build
BINDIR		:=	bin

SOURCES		:=	src/view/view.c \
				src/application/application.c \
				src/main.c

LIBS		:=	pokem

OBJS		:=	$(BUILDDIR)/main.o $(BUILDDIR)/application.o $(BUILDDIR)/view.o

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

.DEFAULT_GOAL := executable
.PHONY: executable clean help

executable: $(BUILDDIR) $(EXECUTABLE) ## Build Pokem CLI executable (default)

clean: ## Remove all leftovers from the previous build
	@$(MSG) "$(ORANGE)Removing intermediate objects files...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(RC_OBJ) $(OBJS)
	@$(MSG) "$(ORANGE)Removing binaries...$(NOCOLOR)\n"
	$(RM) $(RM_FLAGS) $(EXECUTABLE)
	@$(MSG) "$(ORANGE)Removing directories...$(NOCOLOR)\n"
	$(RMDIR) $(RMDIR_FLAGS) $(BUILDDIR)
	$(RMDIR) $(RMDIR_FLAGS) $(BINDIR)
	@$(MSG) "$(LIGHTGREEN)Example $(WHITE)pokem-cli$(LIGHTGREEN) cleaned.$(NOCOLOR)\n\n"

help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {$(MSG) "$(WHITE)%-20s$(NOCOLOR) %s\n", $$1, $$2}'

$(EXECUTABLE): $(BUILDDIR) $(RC_OBJ) $(OBJS) $(BINDIR)
	@$(MSG) "$(YELLOW)Building and linking executable file...$(NOCOLOR)\n"
	$(CC) -o $@ $(CFLAGS) $(CC_LFLAGS) $(RC_OBJ) $(OBJS) -L$(LIBDIR) -l$(LIBS)
	@$(MSG) "$(LIGHTGREEN)Done. The example $(WHITE)pokem-cli$(LIGHTGREEN) was built in the $(LIGHTBLUE)$(BINDIR)$(LIGHTGREEN) directory. Enjoy.$(NOCOLOR)\n"

$(OBJS):
	@$(MSG) "$(GREEN)Compiling $(BLUE)$<$(GREEN)...$(NOCOLOR)\n"
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

# INTERMEDIATE OBJECTS BUILD RULES
$(BUILDDIR)/main.o:        		src/main.c
$(BUILDDIR)/application.o:		src/application/application.c
$(BUILDDIR)/view.o:				src/view/view.c