#include "messages.h"

#include <stdarg.h>

#if !defined(NO_USE_COLORS)
    #define RESETCOLORS "\x1B[0m"   /* all attributes off */
    #define DARKGREEN   "\x1B[32m"
    #define LIGHTRED    "\x1B[31;1m"
    #define LIGHTGREEN  "\x1B[32;1m"
    #define LIGHTYELLOW "\x1B[33;1m"
#else
    #define RESETCOLORS ""
    #define DARKGREEN   ""
    #define LIGHTRED    ""
    #define LIGHTGREEN  ""
    #define LIGHTYELLOW ""
#endif

int printMessages = 1;

int printMessage(FILE *stream, enum MessageType messageType, const char* message, ...)
{
    va_list argList;
    int charactersReturned = 0;
    const char* messageTypesStr[] = { "DEBUG", "INFO", "WARNING", "ERROR", "FATAL ERROR" };
    const char* messageColorsByTypes[] = { DARKGREEN, LIGHTGREEN, LIGHTYELLOW, LIGHTRED, LIGHTRED };

    if (!printMessages || !stream || messageType > FatalMessage) {
        return 0;
    }

    charactersReturned += fprintf(stream, "%s%s: " RESETCOLORS, messageColorsByTypes[messageType], messageTypesStr[messageType]);
    va_start(argList, message);
    charactersReturned += vfprintf(stream, message, argList);
    va_end(argList);
    return charactersReturned;
}