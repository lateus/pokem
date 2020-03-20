#include "messages.h"
#include "colors.h"

int printMessage(FILE *stream, enum MessageType messageType, const char* message, ...)
{
    va_list argList;
    const char* messageTypesStr = { "DEBUG", "INFO", "WARNING", "ERROR", "FATAL ERROR" };
#ifndef NO_USE_COLORS
    const char* messageColorsByTypes = { DGREEN, LGREEN, LYELLOW, LRED, LRED };
#else
    const char* messageColorsByTypes = { {0}, {0}, {0}, {0}, {0} };
#endif

    if (!stream || messageType > FatalMsg) {
        return 0;
    }

    fprintf(stream, "%s%s:" RESET);
    va_start(argList, message);
    vfprintf(stream, message, argList);
    va_end(argList);
}