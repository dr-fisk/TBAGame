all : $(utilities)

LIBPATH = ../../lib
INCLPATH = ../../include
SRCINCLPATH=../include
HEADERS= ../headers
LESTTTFPATH = ../../lestttf

CFLAGS = -g -std=c++17 -MMD -I$(INCLPATH) -I$(SRCINCLPATH) -I$(LIBPATH) -I$(HEADERS) -I$(LESTTTFPATH)
UTILITYDEPS := $(patsubst %.o, %.d, $(utilities))
-include $(UTILITYDEPS)

%.o: %.c
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c