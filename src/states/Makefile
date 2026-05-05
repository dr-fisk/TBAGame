all : $(states)

LIBPATH = ../../lib
INCLPATH = ../../include
SRCINCLPATH=../include
HEADERS= ../headers
LESTTTFPATH = ../../lestttf
LESTRENDERENGINEPATH = ../../include/LestRenderEngine/include

CFLAGS  += -std=c++17 -Wall -Wextra -MMD -MD -I$(LESTTTFPATH) -I$(LESTRENDERENGINEPATH)  -I$(INCLPATH) -I$(SRCINCLPATH)
StateDeps := $(patsubst %.o, %.d, $(states))
-include $(StateDeps)

%.o: %.cpp
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c

clean_dep:
	@echo "Clean Dependencies"
	@for item in ${StateDeps}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done