all : $(GUI)

LIBPATH = ../../lib
INCLPATH = ../../include
HEADERS= ../headers

CFLAGS = -g -std=c++17 -MMD -I$(INCLPATH) -I$(LIBPATH) -I$(HEADERS)

%.o: %.cpp
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c
