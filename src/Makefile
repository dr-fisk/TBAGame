SHELL := /bin/bash

CC = x86_64-w64-mingw32-g++
programs = main.exe

ifeq (lin64, $(TARGET))
  CC = g++
  programs = main.out
else ifeq (win64, $(TARGET))
  CC = x86_64-w64-mingw32-g++
  programs = main.exe
endif

LIBPATH = ../lib
INCLPATH = ../include
HEADERS= ./headers
PATHTOEXEC = ../objs-wind64
PATHTOEXECLINUX = ../objs-lin64
STATEPATH = ./states
RENDERERSPATH = ./renderer
GUIPATH = ./gui
DRAWABLESPATH = ./drawable
SRC = ./src
SHADERSPATH = ./shaders
FONTSPATH = ./fonts
DYNLIBSPATH = ./libs

SHADER = $(SHADERSPATH)/shader1.txt

CFLAGS  = -g -std=c++17 -Wall -Wextra -MMD -static-libgcc -static-libstdc++ -I$(INCLPATH) -I$(HEADERS)

LDFLAGS = -L$(DYNLIBSPATH) -L$(LIBPATH) -lglfw3dll -lws2_32 -lglew32 -lglfw3 -lopengl32 -lglu32 -lgdi32 -lzlib1 -static-libgcc -static-libstdc++ -llestpng
SOLDFLAGS = -L$(LIBPATH) -lzlib1 -lws2_32 -shared -static-libgcc -static-libstdc++

ifeq (lin64, $(TARGET))
  LDFLAGS = -L$(LIBPATH) -lglfw3dll -lglew32 -lglfw3 -lopengl32 -lglu32 -lgdi32 -lz
else ifeq (win64, $(TARGET))
  LDFLAGS = -L$(LIBPATH) -lglfw3dll -lws2_32 -lglew32 -lglfw3 -lopengl32 -lglu32 -lgdi32 -lzlib1 -L$(DYNLIBSPATH) -llestpng -static-libgcc -static-libstdc++
endif


MAKEFLAGS += -rR --no-print-directory

all : $(programs)

linkFiles  = common.c \
             game.c \
             state.c

stateFiles = mainMenuState.c \
             exceptionState.c

guiFiles   = gui.c

rendererFiles =  renderWindow.c \
                 renderTarget.c \
                 font.c

drawableFiles = indexBuffer.c \
                shader.c \
                batchBuffer.c \
                vertexBuffer.c \
                vertexArray.c \
                rectangle.c \
                mesh.c \
				text.c

dynLibFiles = png.c

objs := $(patsubst %.exe, %.o, $(programs))

ifeq (lin64, $(TARGET))
  objs := $(patsubst %.out, %.o, $(programs))
else ifeq (win64, $(TARGET))
  objs := $(patsubst %.exe, %.o, $(programs))
endif

objs += $(patsubst %.c, %.o, $(linkFiles))

states = $(patsubst %.c, %.o, $(stateFiles))
stateObjs = $(addprefix $(STATEPATH)/, $(states))

GUI = $(patsubst %.c, %.o, $(guiFiles))
guiObjs = $(addprefix $(GUIPATH)/, $(GUI))

renderers = $(patsubst %.c, %.o, $(rendererFiles))
rendererObjs = $(addprefix $(RENDERERSPATH)/, $(renderers))

drawables = $(patsubst %.c, %.o, $(drawableFiles))
drawableObjs = $(addprefix $(DRAWABLESPATH)/, $(drawables))

dynLibPrefix = lest

dynamicLibs = $(patsubst %.c, %.dll, $(dynLibFiles))
dynamicLibsDLL = $(addprefix $(dynLibPrefix), $(dynamicLibs))
dynamicLibDLLObjs = $(addprefix $(DYNLIBSPATH)/, $(dynamicLibsDLL))
dynamicLibObjs = $(patsubst %.c, %.o, $(dynLibFiles))
dynamicLibObjsPath = $(addprefix $(DYNLIBSPATH)/, $(dynamicLibObjs))

ifneq ($(DEBUG), 1)
  Q=@
  DEBUG = 0
endif

deps := $(patsubst %.o, %.d, $(objs))
deps += $(patsubst %.o, %.d, $(stateObjs))
deps += $(patsubst %.o, %.d, $(guiObjs))
deps += $(patsubst %.o, %.d, $(rendererObjs))
deps += $(patsubst %.o, %.d, $(drawableObjs))
deps += $(patsubst %.o, %.d, $(dynamicLibObjsPath))
-include $(deps)

export

$(DYNLIBSPATH):
	@echo "MAKE	Dynamic Libraries"
	$(Q)$(MAKE)  V=$(V) D=$(D) -C $(DYNLIBSPATH)

$(STATEPATH):
	@echo "MAKE	States"
	$(Q)$(MAKE)  V=$(V) D=$(D) -C $(STATEPATH)

$(GUIPATH):
	@echo "MAKE	Gui"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(GUIPATH)

$(DRAWABLESPATH):
	@echo "MAKE	Drawables"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(DRAWABLESPATH)

$(RENDERERSPATH):
	@echo "MAKE	Renderers"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(RENDERERSPATH)

shader:
		@echo "Copying Shaders"
		$(Q)cp -r $(SHADERSPATH) $(PATHTOEXEC)

font:
		@echo "Copying Fonts"
		$(Q)cp -r $(FONTSPATH) $(PATHTOEXEC)

%.exe: $(objs) $(DYNLIBSPATH) $(STATEPATH) $(GUIPATH) $(DRAWABLESPATH) $(RENDERERSPATH)
	@echo "MAKE $@"
	$(Q)$(CC) $(CFLAGS) -o $@ $(objs) $(stateObjs) $(guiObjs) $(rendererObjs) $(drawableObjs) $(LDFLAGS)
	@echo "Checking DIR"
	$(Q)if [ ! -d $(PATHTOEXEC) ]; then \
		echo "Creating Win DIR"; \
		mkdir $(PATHTOEXEC); \
		echo "Adding opengldll"; \
		cp $(LIBPATH)/glfw3.dll $(PATHTOEXEC); \
		cp $(LIBPATH)/glew32.dll $(PATHTOEXEC); \
		cp $(LIBPATH)/zlib1.dll $(PATHTOEXEC); \
		echo "Adding custom dll"; \
		cp $(DYNLIBSPATH)/lestpng.dll $(PATHTOEXEC); \
		cp -r $(SHADERSPATH) $(PATHTOEXEC); \
		cp -r $(FONTSPATH) $(PATHTOEXEC); \
	fi
	@echo "Transferring .exe"
	$(Q)cp $@ $(PATHTOEXEC)

%.out: $(objs) $(STATEPATH) $(GUIPATH) $(DRAWABLESPATH) $(RENDERERSPATH)
	@echo "MAKE $@"
	$(Q)$(CC) $(CFLAGS) -o $@ $(objs) $(stateObjs) $(guiObjs) $(rendererObjs) $(drawableObjs) $(LDFLAGS)
	@echo "Checking DIR"
	$(Q)if [ ! -d $(PATHTOEXECLINUX) ]; then \
		echo "Creating Lin DIR"; \
		mkdir $(PATHTOEXECLINUX); \
		echo "Adding opengldll"; \
		cp $(LIBPATH)/glfw3.dll $(PATHTOEXECLINUX); \
		cp $(LIBPATH)/glew32.dll $(PATHTOEXECLINUX); \
		echo "Adding custom dll"; \
		cp $(DYNLIBSPATH)/liblestpng.dll $(PATHTOEXECLINUX); \
		cp -r $(SHADERSPATH) $(PATHTOEXECLINUX); \
		cp -r $(FONTSPATH) $(PATHTOEXECLINUX); \
	fi
	@echo "Transferring .out"
	$(Q)cp $@ $(PATHTOEXECLINUX)

main.o: main.cxx
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c

%.o: %.c
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c 

clean:
	@echo "Checking win DIR"
	$(Q)if [ -d $(PATHTOEXEC) ]; then \
		echo "RM Win DIR"; \
		rm -rf $(PATHTOEXEC); \
	fi
	@echo "CLEAN ALL"
	@for item in ${stateObjs}; do \
		if [ -f $${item} ]; then \
		echo "Rm $${item}"; \
		rm $${item}; \
		fi \
	done
	@for item in ${guiObjs}; do \
		if [ -f $${item} ]; then \
		echo "Rm $${item}"; \
		rm $${item}; \
		fi \
	done
	@for item in ${rendererObjs}; do \
		if [ -f $${item} ]; then \
		echo "Rm $${item}"; \
		rm $${item}; \
		fi \
	done
	@for item in ${drawableObjs}; do \
		if [ -f $${item} ]; then \
		echo "Rm $${item}"; \
		rm $${item}; \
		fi \
	done
	@for item in ${dynamicLibDLLObjs}; do \
		if [ -f $${item} ]; then \
		echo "Rm $${item}"; \
		rm $${item}; \
		fi \
	done
	@for item in ${objs}; do \
		if [ -f $${item} ]; then \
		echo "Rm $${item}"; \
		rm $${item}; \
		fi \
	done
	@for item in ${deps}; do \
		if [ -f $${item} ]; then \
		echo "Rm $${item}"; \
		rm $${item}; \
		fi \
	done
	@if [ -f $(programs) ]; then \
		echo "Rm $(programs)"; \
		rm $(programs); \
	fi
help:
	@echo "Make commands"
	@echo "make TARGET=[lin64, win64]"
	@echo "Makefile will be expanded in the future"

.PRECIOUS: %.o $(STATEPATH)/%.o $(GUIPATH)/%.o $(RENDERERSPATH)/%.o $(DRAWABLESPATH)/%.o $(DYNLIBSPATH)/%.so $(DYNLIBSPATH)/%.o $(DYNLIBSPATH)/%.dll
.PHONY: $(DYNLIBSPATH) $(STATEPATH) $(GUIPATH) $(DRAWABLESPATH) $(RENDERERSPATH) 
