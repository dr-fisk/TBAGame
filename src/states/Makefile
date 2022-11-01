all : $(states)

LIBPATH = ../../lib
INCLPATH = ../../include
HEADERS= ../headers

CFLAGS = -g -std=c++17 -MMD -I$(INCLPATH) -I$(LIBPATH) -I$(HEADERS)
StateDeps := $(patsubst %.o, %.d, $(stateObjs))
-include $(StateDeps)

%.o: %.c
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c
