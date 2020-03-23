#include "messages.h"

int printMessages = 1;

int printMessage(FILE *stream, enum MessageType messageType, const char* message, ...)
{
    va_list argList;
    int charactersReturned = 0;
    const char* messageTypesStr[] = { "DEBUG", "INFO", "WARNING", "ERROR", "FATAL ERROR" };
#ifndef NO_USE_COLORS
    const char* messageColorsByTypes[] = { DGREEN, LGREEN, LYELLOW, LRED, LRED };
#else
    const char* messageColorsByTypes[] = { {0}, {0}, {0}, {0}, {0} };
#endif

    if (!printMessages || !stream || messageType > FatalMessage) {
        return 0;
    }

    charactersReturned += fprintf(stream, "%s%s: " RESET, messageColorsByTypes[messageType], messageTypesStr[messageType]);
    va_start(argList, message);
    charactersReturned += vfprintf(stream, message, argList);
    va_end(argList);
    return charactersReturned;
}