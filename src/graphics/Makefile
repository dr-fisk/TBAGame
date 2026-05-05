all : $(graphics)

LIBPATH = ../../lib
INCLPATH = ../../include
SRCINCLPATH=../include
HEADERS= ../headers
LESTTTFPATH= ../../lestttf
LESTRENDERENGINEPATH = ../../include/LestRenderEngine/include

CFLAGS  += -std=c++17 -Wall -g -Wextra -MMD -MD -I$(LESTTTFPATH) -I$(LESTRENDERENGINEPATH)  -I$(INCLPATH) -I$(SRCINCLPATH)
GRAPHICSDEPS := $(patsubst %.o, %.d, $(graphics))
-include $(GRAPHICSDEPS)

%.o: %.cpp
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c

clean_dep:
	@echo "Clean Dependencies"
	@for item in ${GRAPHICSDEPS}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done