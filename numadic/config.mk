PREFIX=/usr/local

CC=cc

CFLAGS=-Wall -Wextra -std=c99 -pedantic -O2
LDFLAGS=-s -lm

BIN=separate
OBJ=$(BIN:=.o)
HDR=stb_image.h stb_image_write.h
CONF=config.mk
