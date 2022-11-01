all : $(drawables)

LIBPATH = ../../lib
INCLPATH = ../../include
HEADERS= ../headers

CFLAGS = -g -std=c++17 -MMD -I$(INCLPATH) -I$(LIBPATH) -I$(HEADERS)
DrawableDeps := $(patsubst %.o, %.d, $(drawableObjs))
-include $(DrawableDeps)



%.o: %.c
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c

