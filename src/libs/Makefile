all : $(dynamicLibsDLL)

LIBPATH = ../../lib
INCLPATH = ../../include
HEADERS= ../headers

CFLAGS = -g -std=c++17 -MMD -I$(INCLPATH) -I$(LIBPATH) -I$(HEADERS)
DynamicLibDeps := $(patsubst %.dll, %.d, $(dynamicLibDLLObjs))
-include $(DynamicLibDeps)


%.o : %.c
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(SOLDFLAGS) -fPIC -c

%.so: $(dynamicLibObjs)
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(SOLDFLAGS) -shared -o $@

%.dll: $(dynamicLibObjs)
	@echo "MAKE $@"
	$(Q)$(CC) $(CFLAGS) $< $(SOLDFLAGS) -o $@