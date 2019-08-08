#ifndef APPLICATION_H
#define APPLICATION_H

#include "decode_encode/dec_enc_common.h"
#include "decode_encode/decode/decode.h"
#include "decode_encode/encode/encode.h"
#include "decode_encode/convert/convert.h"
#include "view/view.h"
#include "model/md1global.h"
#include "model/md1database.h"

#include <stdio.h>
#include <string.h>

int decodeWM(int argc, const char *argv[]);
int encodeWM(int argc, const char *argv[]);
void parseWMData(const char *argv[], struct WONDERMAIL *wm);
int decodeSOSM(int argc, const char *argv[]);
void parseSOSData(const char *argv[], struct SOSMAIL *sos);
int encodeSOSM(int argc, const char *argv[]);
int convertSOS(int argc, const char *argv[]);

#endif /* APPLICATION_H */
