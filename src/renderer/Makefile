all : $(renderers)

LIBPATH = ../../lib
INCLPATH = ../../include
HEADERS= ../headers

CFLAGS = -g -std=c++17 -MMD -I$(INCLPATH) -I$(LIBPATH) -I$(HEADERS)

RendererDeps := $(patsubst %.o, %.d, $(rendererObjs))
-include $(RendererDeps)

%.o: %.c
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c
