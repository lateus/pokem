#ifndef MESSAGES_H
#define MESSAGES_H

#include <stdio.h>
#include <stdarg.h>
#include "colors.h"

/* Message type */
enum MessageType { DebugMessage, InfoMessage, WarningMessage, ErrorMessage, FatalMessage };

int printMessage(FILE *stream, enum MessageType messageType, const char* message, ...);

#endif /* MESSAGES_H */