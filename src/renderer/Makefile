all : $(renderer)

LIBPATH = ../../lib
INCLPATH = ../../include
SRCINCLPATH=../include
HEADERS= ../headers
LESTTTFPATH = ../../lestttf

CFLAGS = -g -std=c++17 -MMD -I$(INCLPATH) -I$(SRCINCLPATH) -I$(LIBPATH) -I$(HEADERS) -I$(LESTTTFPATH)
RendererDeps := $(patsubst %.o, %.d, $(renderer))
-include $(RendererDeps)

%.o: %.cpp
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c

clean_dep:
	@echo "Clean Dependencies"
	@for item in ${RendererDeps}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done