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
int encodeWonderMail(int argc, const char *argv[]);
int decodeSOSMail(int argc, const char *argv[]);
int encodeSOSMail(int argc, const char *argv[]);
int convertSOSMail(int argc, const char *argv[]);

int WonderMailIsInvalid(const char *password, char packed15BytesPassword[]);
int SOSMailIsInvalid(const char *password, char packed34BytesPassword[]);
int SOSMailIsInvalidForConverting(const char *password, char password54Integers[]);

#endif /* APPLICATION_H */
