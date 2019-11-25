#ifndef APPLICATION_H
#define APPLICATION_H

#include "../../lib/pokem.h"

#include <stdio.h>
#include <string.h>

int decodeWM(int argc, const char *argv[]);
int encodeWM(int argc, const char *argv[]);
void parseWMData(const char *argv[], struct WonderMail *wm);
int decodeSOSM(int argc, const char *argv[]);
void parseSOSData(const char *argv[], struct SosMail *sos);
int encodeSOSM(int argc, const char *argv[]);
int convertSOS(int argc, const char *argv[]);

#endif /* APPLICATION_H */
