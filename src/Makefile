SHELL := /bin/bash

CC = x86_64-w64-mingw32-g++-posix
programs = lestgame.exe
entrypoint = main.cxx

ifeq (linux, $(TARGET))
  CC = g++
  programs = lestgame
else ifeq (win64, $(TARGET))
  CC = x86_64-w64-mingw32-g++
  programs = lestgame.exe
endif

LIBPATH = ../lib
INCLPATH = ../include
SRCINCLPATH = ./include
HEADERS= ./headers
PATHTOEXEC = ../objs-wind64
PATHTOEXECLINUX = ../objs-lin64
STATEPATH = ./states
GUIPATH = ./gui
GRAPHICSEVENTPATH = ./graphicsEvent
GRAPHICSPATH = ./graphics
LESTENGINEEVENTSPATH = ./event
SRC = ./src
SHADERSPATH = ./shaders
FONTSPATH = ./fonts
LESTTTFPATH = ../lestttf
LESTRENDERENGINEPATH = ../include/LestRenderEngine/include
FONTPATH = ../TtfFont

SHADER = $(SHADERSPATH)/shader1.txt

ifeq (debug, $(BUILD))
CFLAGS = -g
else
CFLAGS = -O3
endif

ifeq (release, $(BUILD))
CFLAGS += -Wl,-subsystem,windows
endif

CFLAGS  += -std=c++17 -g -Wall -Wextra -MMD -MD -I$(LESTTTFPATH) -I$(LESTRENDERENGINEPATH) -I$(INCLPATH) -I$(SRCINCLPATH)

LDFLAGS = -L$(LIBPATH) -lglfw3dll -lws2_32 -lglew32 -lglfw3 -lopengl32 -lglu32 -lgdi32 -lzlib1 -pthread -llestrenderengine -llestmedia -llestttf -static-libgcc -static-libstdc++
SOLDFLAGS = -L$(LIBPATH) -lzlib1 -lws2_32 -shared -static-libgcc -static-libstdc++

ifeq (linux, $(TARGET))
  LIBPATH = ../liblinux
  CFLAGS += -Wl,-rpath='$(LIBPATH)'
  LDFLAGS = -L$(LIBPATH) -lglfw -lGLU -lGLEW -lGL -lz -llestmedia -llestttf -llestrenderengine
else ifeq (win64, $(TARGET))
  LDFLAGS = -L$(LIBPATH) -lglfw3dll -lws2_32 -lglew32 -lglfw3 -lopengl32 -lglu32 -lgdi32 -lzlib1 -llestmedia -pthread -static-libgcc -static-libstdc++ -llestttf
endif


MAKEFLAGS += -rR --no-print-directory

all : $(programs)

linkFiles  = common.cpp \
             game.cpp

stateFiles = state.cpp \
             mainMenuState.cpp \
             exceptionState.cpp

graphicsFiles = component.cpp \
				label.cpp \
				abstractButton.cpp \
				toggleButton.cpp \
				button.cpp \
				scrollbar.cpp \
				menuItem.cpp \
				menu.cpp \
				popupMenu.cpp \
				modifier.cpp \
				textModifier.cpp \
				componentManager.cpp \
				frame.cpp \
				textbox.cpp

graphicsEventsFiles = itemEvent.cpp

objs := $(patsubst %.cxx, %.o, $(entrypoint))

objs += $(patsubst %.cpp, %.o, $(linkFiles))

states = $(patsubst %.cpp, %.o, $(stateFiles))
stateObjs = $(addprefix $(STATEPATH)/, $(states))

graphics = $(patsubst %.cpp, %.o, $(graphicsFiles))
graphicsObjs = $(addprefix $(GRAPHICSPATH)/, $(graphics))

graphicsEvents = $(patsubst %.cpp, %.o, $(graphicsEventsFiles))
graphicsEventsObjs = $(addprefix $(GRAPHICSEVENTPATH)/, $(graphicsEvents))

lestEngineEvents = $(patsubst %.cpp, %.o, $(lestEngineEventFiles))
lestEngineEventsObjs = $(addprefix $(LESTENGINEEVENTSPATH)/, $(lestEngineEvents))

dynLibPrefix = lest

deps := $(patsubst %.o, %.d, $(objs))
deps += $(patsubst %.o, %.d, $(stateObjs))
deps += $(patsubst %.o, %.d, $(guiObjs))

# include $(deps)
ifneq ($(DEBUG), 1)
  Q=@
  DEBUG = 0
endif

export

$(STATEPATH):
	@echo "MAKE	States"
	$(Q)$(MAKE)  V=$(V) D=$(D) -C $(STATEPATH)

$(GRAPHICSPATH):
	@echo "MAKE	Graphics"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(GRAPHICSPATH)

$(GRAPHICSEVENTPATH):
	@echo "MAKE	Graphics Events"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(GRAPHICSEVENTPATH)
	
shader:
		@echo "Copying Shaders"
		$(Q)cp -r $(SHADERSPATH) $(PATHTOEXEC)

font:
		@echo "Copying Fonts"
		$(Q)cp -r $(FONTSPATH) $(PATHTOEXEC)

ifneq (linux, $(TARGET))
$(programs): $(objs) $(STATEPATH) \
       $(GRAPHICSPATH) $(GRAPHICSEVENTPATH)
	@echo "MAKE $@"
	$(Q)$(CC) $(CFLAGS) -o $@ $(objs) $(stateObjs) \
	$(graphicsObjs) $(graphicsEventsObjs) $(LDFLAGS)
	@echo "Checking DIR"
	$(Q)if [ ! -d $(PATHTOEXEC) ]; then \
		echo "Creating Win DIR"; \
		mkdir $(PATHTOEXEC); \
		echo "Adding opengldll"; \
		cp $(LIBPATH)/glfw3.dll $(PATHTOEXEC); \
		cp $(LIBPATH)/glew32.dll $(PATHTOEXEC); \
		cp $(LIBPATH)/zlib1.dll $(PATHTOEXEC); \
		cp $(LIBPATH)/libwinpthread-1.dll $(PATHTOEXEC); \
		echo "Adding custom dll"; \
		cp $(LIBPATH)/lestmedia.dll $(PATHTOEXEC); \
		cp $(LIBPATH)/lestrenderengine.dll $(PATHTOEXEC); \
		cp $(LIBPATH)/lestttf.dll $(PATHTOEXEC); \
		cp $(FONTPATH)/Envy\ Code\ R.ttf $(PATHTOEXEC); \
		cp -r $(SHADERSPATH) $(PATHTOEXEC); \
		cp -r $(FONTSPATH) $(PATHTOEXEC); \
	else \
		echo "Checking dynamic libraries exist"; \
		if [ ! -f $(PATHTOEXEC)/lestmedia.dll ]; then \
			cp $(LIBPATH)/lestmedia.dll $(PATHTOEXEC)/lestmedia.dll; \
		fi; \
		if [ ! -f $(PATHTOEXEC)/lestrenderengine.dll ]; then \
			cp $(LIBPATH)/lestrenderengine.dll $(PATHTOEXEC)/lestrenderengine.dll; \
		fi; \
		if [ ! -f $(PATHTOEXEC)/lestttf.dll ]; then \
			cp $(LIBPATH)/lestttf.dll $(PATHTOEXEC)/lestttf.dll; \
		fi; \
		if [ ! -f $(PATHTOEXEC)/glfw3.dll ]; then \
			cp $(LIBPATH)/glfw3.dll $(PATHTOEXEC)/glfw3.dll; \
		fi; \
		if [ ! -f $(PATHTOEXEC)/glew32.dll ]; then \
			cp $(LIBPATH)/glew32.dll $(PATHTOEXEC)/glew32.dll; \
		fi; \
		if [ ! -f $(PATHTOEXEC)/zlib1.dll ]; then \
			cp $(LIBPATH)/zlib1.dll $(PATHTOEXEC)/zlib1.dll; \
		fi; \
		if [ ! -f $(PATHTOEXEC)/libwinpthread-1.dll ]; then \
			cp $(LIBPATH)/libwinpthread-1.dll $(PATHTOEXEC)/libwinpthread-1.dll; \
		fi; \
	fi
	@echo "Transferring .exe"
	$(Q)cp $@ $(PATHTOEXEC)
else
$(programs): $(objs) $(STATEPATH) $(GRAPHICSPATH) $(GRAPHICSEVENTPATH)
	@echo "MAKE $@"
	$(Q)$(CC) $(CFLAGS) -o $@ $(objs) $(stateObjs) $(graphicsObjs) $(graphicsEventsObjs) $(LDFLAGS)
	@echo "Checking DIR"
	$(Q)if [ ! -d "$(PATHTOEXEC)" ]; then \
		echo "Creating Win DIR"; \
		mkdir $(PATHTOEXEC); \
		cp $(LIBPATH)/liblestmedia.so $(PATHTOEXEC); \
		cp $(LIBPATH)/liblestrenderengine.so $(PATHTOEXEC); \
		cp $(LIBPATH)/liblestttf.so $(PATHTOEXEC); \
		cp $(FONTPATH)/Envy\ Code\ R.ttf $(PATHTOEXEC); \
		cp -r $(SHADERSPATH) $(PATHTOEXEC); \
		cp -r $(FONTSPATH) $(PATHTOEXEC); \
	else \
		echo "Checking dynamic libraries exist"; \
		if [ ! -f $(PATHTOEXEC)/liblestmedia.so ]; then \
			cp $(LIBPATH)/liblestmedia.so $(PATHTOEXEC)/liblestmedia.so; \
		fi; \
		if [ ! -f $(PATHTOEXEC)/liblestrenderengine.so ]; then \
			cp $(LIBPATH)/liblestrenderengine.so $(PATHTOEXEC)/liblestrenderengine.so; \
		fi; \
		if [ ! -f $(PATHTOEXEC)/liblestttf.so ]; then \
			cp $(LIBPATH)/liblestttf.so $(PATHTOEXEC)/liblestttf.so; \
		fi; \
	fi
	@echo "Transferring .exe"
	$(Q)cp $@ $(PATHTOEXEC)
endif

%.out: $(objs) $(STATEPATH) $(DRAWABLESPATH) $(UTILITYPATH)
	@echo "MAKE $@"
	$(Q)$(CC) $(CFLAGS) -o $@ $(objs) $(stateObjs) $(windowObjs) $(drawableObjs) $(utilitiesObjs) $(LDFLAGS)
	@echo "Checking DIR"
	$(Q)if [ ! -d $(PATHTOEXECLINUX) ]; then \
		echo "Creating Lin DIR"; \
		mkdir $(PATHTOEXECLINUX); \
		echo "Adding opengldll"; \
		cp $(LIBPATH)/glfw3.dll $(PATHTOEXECLINUX); \
		cp $(LIBPATH)/glew32.dll $(PATHTOEXECLINUX); \
		echo "Adding custom dll"; \
		cp $(DYNLIBSPATH)/liblestmedia.dll $(PATHTOEXECLINUX); \
		cp -r $(SHADERSPATH) $(PATHTOEXECLINUX); \
		cp -r $(FONTSPATH) $(PATHTOEXECLINUX); \
	fi
	@echo "Transferring .out"
	$(Q)cp $@ $(PATHTOEXECLINUX)

main.o: main.cxx
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c

%.o: %.cpp
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c 

clean_state:
	@echo "Clean States"
	@for item in ${stateObjs}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done

clean_graph_events:
	@echo "Clean Graphics Events"
	@for item in ${graphicsEventsObjs}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done

clean_main:
	@echo "Clean Main Files"
	@for item in ${objs}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done

clean_lestengineevents:
	@echo "Clean Lest Engine Events"
	@for item in ${lestEngineEventsObjs}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done

clean_graphics:
	@echo "Clean Graphics"
	@for item in ${graphicsObjs}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done

clean_dep:
	@echo "Clean Dependencies"
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(STATEPATH)
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(GRAPHICSPATH)
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(GRAPHICSEVENTPATH)

clean_exe:
	@echo "Clean Executable"
	@if [ -f $(programs) ]; then \
		echo "Rm $(programs)"; \
		rm $(programs); \
	fi

clean: clean_state clean_main clean_dep clean_exe \
       clean_graphics clean_resource clean_graph_events \
			 clean_lestengineevents
	@echo "Checking win DIR"
	$(Q)if [ -d $(PATHTOEXEC) ]; then \
		echo "RM Win DIR"; \
		rm -rf $(PATHTOEXEC); \
	fi
	@echo "CLEAN ALL"

help:
	@echo "Make commands"
	@echo "make TARGET=[lin64, win64]"
	@echo "Makefile will be expanded in the future"

.PRECIOUS: %.o $(STATEPATH)/%.o $(GRAPHICSPATH)/%.o $(GRAPHICSEVENTPATH)/%.o $(LESTENGINEEVENTSPATH)/%.o
.PHONY: $(STATEPATH) $(GRAPHICSPATH) $(GRAPHICSEVENTPATH) $(LESTENGINEEVENTSPATH)
