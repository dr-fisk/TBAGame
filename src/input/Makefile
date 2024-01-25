all : $(inputs)

LIBPATH = ../../lib
INCLPATH = ../../include
SRCINCLPATH=../include
HEADERS= ../headers
LESTTTFPATH = ../../lestttf

CFLAGS = -g -std=c++17 -MMD -I$(INCLPATH) -I$(SRCINCLPATH) -I$(LIBPATH) -I$(HEADERS) -I$(LESTTTFPATH)
InputDeps := $(patsubst %.o, %.d, $(inputs))
-include $(InputDeps)

%.o: %.cpp
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c

clean_dep:
	@echo "Clean Dependencies"
	@for item in ${InputDeps}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done