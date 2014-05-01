# include common defines and rules
BASEDIR=..

include common.mak


BINARY=$(OUTDIR)/synthesizer




all: $(BINARY)


SRCS=$(shell find . -name "*.cpp")
HDRS=$(shell find . -name "*.h")
OBJS=$(SRCS:.cpp=.o)

$(BINARY): $(OBJS) -lSDL2 -lpthread
	$(CC) -o $@ $^ 	


.PHONY: distclean clean



clean::
	rm -f *.o



# include handling of dependencies to header files
include footer.mak
