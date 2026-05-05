all : $(graphicsEvents)

LIBPATH = ../../lib
INCLPATH = ../../include
SRCINCLPATH=../include
HEADERS= ../headers
LESTTTFPATH = ../../lestttf
LESTRENDERENGINEPATH = ../../include/LestRenderEngine/include

CFLAGS  += -std=c++17 -Wall -Wextra -MMD -MD -I$(LESTTTFPATH) -I$(LESTRENDERENGINEPATH)  -I$(INCLPATH) -I$(SRCINCLPATH)
GraphicEventsDeps := $(patsubst %.o, %.d, $(graphicsEvents))
-include $(GraphicEventsDeps)

%.o: %.cpp
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c

clean_dep:
	@echo "Clean Dependencies"
	@for item in ${GraphicEventsDeps}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done