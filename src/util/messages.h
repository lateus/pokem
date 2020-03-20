#ifndef MESSAGES_H
#define MESSAGES_H

#include <stdio.h>
#include <stdarg.h>

/* Message type */
enum MessageType { DebugMsg, InfoMsg, WarnMsg, ErrMsg, FatalMsg };

int printMessage(FILE *stream, enum MessageType messageType, const char* message, ...);

#endif /* MESSAGES_H */