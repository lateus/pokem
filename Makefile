CC			:= gcc
C_WFLAGS		:= -W -Wall -Wextra
C_OFLAGS		:= -O2 -funroll-loops
C_LFLAGS		:= -Wl,-s

SRC			:= src/*.* src/decode_encode/*.* src/decode_encode/encode/*.* src/decode_encode/decode/*.* src/decode_encode/convert/*.* src/model/*.* src/view/*.*
RES			:= res/*.*


# Platform-specific switches
ifeq ($(OS),Windows_NT)
	WINRES		:= windres
	EXECUTABLE	:= app.exe
	RES_OBJ		:= res.o
	RM_RES_OBJ	:= $(RM) RES_OBJ
else
	WINRES		:= windres
	EXECUTABLE	:= app
	RES_OBJ		:=
	RM_RES_OBJ	:=
endif


all: $(RES_OBJ) $(EXECUTABLE)

clean:
	$(RM) $(BIN)/$(EXECUTABLE)
	$(RM) $(BIN)/$(RES_OBJ)

run: all
	./$(EXECUTABLE)

# Rules to make executable
$(RES_OBJ): $(RES)
	$(WINRES) -i $(RES) -o $(RES_OBJ)
$(EXECUTABLE): $(BIN)
	$(CC) $(C_WFLAGS) $(C_OFLAGS) $(C_LFLAGS) $(SRC) $(RES_OBJ) -o $@
