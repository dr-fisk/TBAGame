all : $(dynamicLibsDLL)

LIBPATH = ../../lib
INCLPATH = ../include
HEADERS= ../headers
EXEC= ../../objs-wind64

CFLAGS = -g -std=c++17 -MMD -I$(INCLPATH) -I$(LIBPATH) -I$(HEADERS)
-include $(dynLibFiles:.cpp=.d)

%.o : %.cpp
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(SOLDFLAGS) -fPIC -c

%.so: $(dynamicLibObjs)
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(SOLDFLAGS) -shared -o $@

%.dll: $(dynamicLibObjs)
	@echo "MAKE $@"
	$(Q)$(CC) $(CFLAGS) $< $(SOLDFLAGS) -o $@
	$(Q)if [ -d $(EXEC) ]; then \
		cp $@ $(EXEC); \
	fi