TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = pokem

SOURCES += \
    src/decode_encode/decode/dec_sos.c \
    src/decode_encode/decode/dec_wm.c \
    src/decode_encode/decode/decode.c \
    src/decode_encode/encode/enc_sos.c \
    src/decode_encode/encode/enc_wm.c \
    src/decode_encode/encode/encode.c \
    src/decode_encode/dec_enc_common.c \
    src/decode_encode/convert/convert.c \
    src/model/md1database.c \
    src/view/view.c \
    src/application.c \
    src/main.c

HEADERS += \
    include/decode_encode/decode/dec_sos.h \
    include/decode_encode/decode/dec_wm.h \
    include/decode_encode/decode/decode.h \
    include/decode_encode/encode/enc_sos.h \
    include/decode_encode/encode/enc_wm.h \
    include/decode_encode/encode/encode.h \
    include/decode_encode/dec_enc_common.h \
    include/decode_encode/convert/convert.h \
    include/model/md1database.h \
    include/model/md1debugger.h \
    include/model/md1global.h \
    include/view/view.h \
    include/application.h

DISTFILES += \
    res/manifest.rc \
    res/images/png/wondermailgenerator_16.png \
    res/images/png/wondermailgenerator_24.png \
    res/images/png/wondermailgenerator_32.png \
    res/images/png/wondermailgenerator_48.png \
    res/images/png/wondermailgenerator_64.png \
    res/images/png/wondermailgenerator_128.png \
    res/images/png/wondermailgenerator_256.png \
    res/images/png/wondermailgenerator_512.png \
    res/images/png/wondermailgenerator_1024.png \
    res/images/png/wondermailgenerator_2048.png \
    res/images/svg/wondermailgenerator.svg \
    res/images/winicon/winicon.ico \
    README.md \
    COPYING.GPLv2 \
    Makefile
