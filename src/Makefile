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
SRCINCLPATH = ./include
HEADERS= ./headers
PATHTOEXEC = ../objs-wind64
PATHTOEXECLINUX = ../objs-lin64
STATEPATH = ./states
WINDOWPATH = ./window
RESOURCEPATH = ./resource
GUIPATH = ./gui
DRAWABLESPATH = ./drawable
RENDERENGINEPATH = ./renderEngine
GRAPHICSPATH = ./graphics
INPUTPATH = ./input
SRC = ./src
SHADERSPATH = ./shaders
FONTSPATH = ./fonts
DYNLIBSPATH = ./libs
LESTTTFPATH = ../lestttf
FONTPATH = ../TtfFont
UTILITYPATH = ./utility

SHADER = $(SHADERSPATH)/shader1.txt

ifeq (debug, $(BUILD))
CFLAGS = -g
else
CFLAGS = -O2
endif

CFLAGS  += -std=c++17 -Wall -Wextra -MMD -MD -static-libgcc -static-libstdc++ -I$(INCLPATH) -I$(SRCINCLPATH) -I$(HEADERS) -I$(LESTTTFPATH)

LDFLAGS = -L$(DYNLIBSPATH) -L$(LIBPATH) -lglfw3dll -lws2_32 -lglew32 -lglfw3 -lopengl32 -lglu32 -lgdi32 -lzlib1 -static-libgcc -static-libstdc++ -llestpng -llestttf
SOLDFLAGS = -L$(LIBPATH) -lzlib1 -lws2_32 -shared -static-libgcc -static-libstdc++

ifeq (lin64, $(TARGET))
  LDFLAGS = -L$(LIBPATH) -lglfw3dll -lglew32 -lglfw3 -lopengl32 -lglu32 -lgdi32 -lz
else ifeq (win64, $(TARGET))
  LDFLAGS = -L$(LIBPATH) -lglfw3dll -lws2_32 -lglew32 -lglfw3 -lopengl32 -lglu32 -lgdi32 -lzlib1 -L$(DYNLIBSPATH) -llestpng -static-libgcc -static-libstdc++ -llestttf
endif


MAKEFLAGS += -rR --no-print-directory

all : $(programs)

linkFiles  = common.c \
             game.c

stateFiles = state.c \
             mainMenuState.c \
             exceptionState.c

guiFiles   = gui.c

windowFiles = renderWindow.c \
              renderTarget.c \
							mouse.c \
							keyboard.c

resourceFiles = image.c \
                font.c \
								resource.c \
								textureResource.c

drawableFiles = drawable.c \
								text.c \
								sprite.c

renderEngineFiles = renderEngine.c \
										indexBuffer.c \
										shader.c \
										batchBuffer.c \
										vertexBuffer.c \
										vertexArray.c \
										texture.c

inputFiles = input.c

graphicsFiles =

dynLibFiles = png.c

utilityFiles = edgeTable.c \
							 vertexUtility.c

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

window = $(patsubst %.c, %.o, $(windowFiles))
windowObjs = $(addprefix $(WINDOWPATH)/, $(window))

resources = $(patsubst %.c, %.o, $(resourceFiles))
resourceObjs = $(addprefix $(RESOURCEPATH)/, $(resources))

drawables = $(patsubst %.c, %.o, $(drawableFiles))
drawableObjs = $(addprefix $(DRAWABLESPATH)/, $(drawables))

renderEngine = $(patsubst %.c, %.o, $(renderEngineFiles))
renderEngineObjs = $(addprefix $(RENDERENGINEPATH)/, $(renderEngine))

graphics = $(patsubst %.c, %.o, $(graphicsFiles))
graphicsObjs = $(addprefix $(GRAPHICSPATH)/, $(graphics))

inputs = $(patsubst %.c, %.o, $(inputFiles))
inputObjs = $(addprefix $(INPUTPATH)/, $(inputs))

dynLibPrefix = lest

dynamicLibs = $(patsubst %.c, %.dll, $(dynLibFiles))
dynamicLibsDLL = $(addprefix $(dynLibPrefix), $(dynamicLibs))
dynamicLibDLLObjs = $(addprefix $(DYNLIBSPATH)/, $(dynamicLibsDLL))
dynamicLibObjs = $(patsubst %.c, %.o, $(dynLibFiles))
dynamicLibObjsPath = $(addprefix $(DYNLIBSPATH)/, $(dynamicLibObjs))

utilities = $(patsubst %.c, %.o, $(utilityFiles))
utilitiesObjs = $(addprefix $(UTILITYPATH)/, $(utilities))

deps := $(patsubst %.o, %.d, $(objs))
deps += $(patsubst %.o, %.d, $(stateObjs))
deps += $(patsubst %.o, %.d, $(guiObjs))
deps += $(patsubst %.o, %.d, $(windowObjs))
deps += $(patsubst %.o, %.d, $(drawableObjs))
deps += $(patsubst %.o, %.d, $(dynamicLibObjsPath))

# include $(deps)
ifneq ($(DEBUG), 1)
  Q=@
  DEBUG = 0
endif

export

$(DYNLIBSPATH):
	@echo "MAKE	Dynamic Libraries"
	$(Q)$(MAKE)  V=$(V) D=$(D) -C $(DYNLIBSPATH)

$(STATEPATH): $(WINDOWPATH)
	@echo "MAKE	States"
	$(Q)$(MAKE)  V=$(V) D=$(D) -C $(STATEPATH)

$(GUIPATH):
	@echo "MAKE	Gui"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(GUIPATH)

$(DRAWABLESPATH):
	@echo "MAKE	Drawables"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(DRAWABLESPATH)

$(WINDOWPATH):
	@echo "MAKE	Window"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(WINDOWPATH)

$(RENDERENGINEPATH):
	@echo "MAKE	Render Engine"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(RENDERENGINEPATH)

$(RESOURCEPATH):
	@echo "MAKE	Resource"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(RESOURCEPATH)

$(GRAPHICSPATH):
	@echo "MAKE	Graphics"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(GRAPHICSPATH)

$(UTILITYPATH):
	@echo "MAKE	Utilities"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(UTILITYPATH)

$(INPUTPATH):
	@echo "MAKE	Inputs"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(INPUTPATH)

shader:
		@echo "Copying Shaders"
		$(Q)cp -r $(SHADERSPATH) $(PATHTOEXEC)

font:
		@echo "Copying Fonts"
		$(Q)cp -r $(FONTSPATH) $(PATHTOEXEC)

%.exe: $(objs) $(DYNLIBSPATH) $(STATEPATH) $(GUIPATH) $(DRAWABLESPATH) $(WINDOWPATH) $(RENDERENGINEPATH) $(RESOURCEPATH) $(GRAPHICSPATH) $(UTILITYPATH) $(INPUTPATH)
	@echo "MAKE $@"
	$(Q)$(CC) $(CFLAGS) -o $@ $(objs) $(stateObjs) $(guiObjs) $(windowObjs) $(drawableObjs) $(utilitiesObjs) $(renderEngineObjs) $(resourceObjs) $(graphicsObjs) $(inputObjs) $(LDFLAGS)
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
		cp $(LIBPATH)/lestttf.dll $(PATHTOEXEC); \
		cp $(FONTPATH)/Envy\ Code\ R.ttf $(PATHTOEXEC); \
		cp -r $(SHADERSPATH) $(PATHTOEXEC); \
		cp -r $(FONTSPATH) $(PATHTOEXEC); \
	fi
	@echo "Transferring .exe"
	$(Q)cp $@ $(PATHTOEXEC)

%.out: $(objs) $(STATEPATH) $(GUIPATH) $(DRAWABLESPATH) $(WINDOWPATH) $(UTILITYPATH)
	@echo "MAKE $@"
	$(Q)$(CC) $(CFLAGS) -o $@ $(objs) $(stateObjs) $(guiObjs) $(windowObjs) $(drawableObjs) $(utilitiesObjs) $(LDFLAGS)
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

clean_state:
	@echo "Clean States"
	@for item in ${stateObjs}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done

clean_gui:
	@echo "Clean GUI"
	@for item in ${guiObjs}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done

clean_window:
	@echo "Clean Window"
	@for item in ${windowObjs}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done

clean_drawable:
	@echo "Clean Drawable"
	@for item in ${drawableObjs}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done

clean_lib:
	@echo "Clean Libraries"
	@for item in ${dynamicLibDLLObjs}; do \
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

clean_renderengine:
	@echo "Clean Render Engine"
	@for item in ${renderEngineObjs}; do \
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

clean_resource:
	@echo "Clean Resource"
	@for item in ${resourceObjs}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done

clean_utilities:
	@echo "Clean Utilities"
	@for item in ${utilitiesObjs}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done

clean_input:
	@echo "Clean Inputs"
	@for item in ${inputObjs}; do \
	if [ -f $${item} ]; then \
	echo "Rm $${item}"; \
	rm $${item}; \
	fi \
	done

clean_dep:
	@echo "Clean Dependencies"
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(UTILITYPATH)
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(STATEPATH)
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(WINDOWPATH)
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(DRAWABLESPATH)
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(RENDERENGINEPATH)
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(GRAPHICSPATH)
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(RESOURCEPATH)
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(INPUTPATH)

clean_exe:
	@echo "Clean Executable"
	@if [ -f $(programs) ]; then \
		echo "Rm $(programs)"; \
		rm $(programs); \
	fi

clean: clean_state clean_gui clean_window clean_drawable clean_lib clean_main clean_dep clean_exe clean_utilities \
       clean_renderengine clean_graphics clean_resource clean_input
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

.PRECIOUS: %.o $(STATEPATH)/%.o $(GUIPATH)/%.o $(WINDOWPATH)/%.o $(RESOURCEPATH)/%.o $(DRAWABLESPATH)/%.o \
           $(RENDERENGINEPATH)/%.o $(GRAPHICSPATH)/%.o $(DYNLIBSPATH)/%.so $(DYNLIBSPATH)/%.o $(DYNLIBSPATH)/%.dll \
					 $(UTILITYPATH)/%.o $(INPUTPATH)/%.o
.PHONY: $(DYNLIBSPATH) $(STATEPATH) $(GUIPATH) $(DRAWABLESPATH) $(WINDOWPATH) $(RESOURCEPATH) $(UTILITYPATH) \
        $(RENDERENGINEPATH) $(GRAPHICSPATH) $(INPUTPATH)
