CFLAGS= -g -Wall
CC=g++


ifeq ($(DEBUG),)
  VERSION=Release
  CFLAGS += -DNDEBUG=1
else
  VERSION=Debug
  CFLAGS += -DDEBUG=1
endif


SRCDIR=$(BASEDIR)/src
OUTDIR=$(BASEDIR)/$(VERSION)

