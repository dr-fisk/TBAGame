all : $(resources)

LIBPATH = ../../lib
INCLPATH = ../../include
SRCINCLPATH=../include
HEADERS= ../headers
LESTTTFPATH = ../../lestttf

CFLAGS = -g -std=c++17 -MMD -I$(INCLPATH) -I$(SRCINCLPATH) -I$(LIBPATH) -I$(HEADERS) -I$(LESTTTFPATH)
RESOURCEDEPS := $(patsubst %.o, %.d, $(resources))
-include $(RESOURCEDEPS)

%.o: %.c
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c