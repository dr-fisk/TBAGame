SHELL := /bin/bash

CC = x86_64-w64-mingw32-g++-posix
programs = lestgame.exe
entrypoint = main.cxx

ifeq (lin64, $(TARGET))
  CC = g++
  programs = main.out
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
WINDOWPATH = ./window
RESOURCEPATH = ./resource
GUIPATH = ./gui
GRAPHICSEVENTPATH = ./graphicsEvent
DRAWABLESPATH = ./drawable
RENDERENGINEPATH = ./renderEngine
RENDERERPATH = ./renderer
GRAPHICSPATH = ./graphics
LESTENGINEEVENTSPATH = ./event
INPUTPATH = ./input
SRC = ./src
SHADERSPATH = ./shaders
FONTSPATH = ./fonts
LESTTTFPATH = ../lestttf
FONTPATH = ../TtfFont
UTILITYPATH = ./utility

SHADER = $(SHADERSPATH)/shader1.txt

ifeq (debug, $(BUILD))
CFLAGS = -g
else
CFLAGS = -O3
endif

ifeq (release, $(BUILD))
CFLAGS += -Wl,-subsystem,windows
endif

CFLAGS  += -std=c++17 -Wall -Wextra -MMD -MD -I$(INCLPATH) -I$(SRCINCLPATH) -I$(HEADERS) -I$(LESTTTFPATH)

LDFLAGS = -L$(LIBPATH) -lglfw3dll -lws2_32 -lglew32 -lglfw3 -lopengl32 -lglu32 -lgdi32 -lzlib1 -pthread -llestpng -llestttf -static-libgcc -static-libstdc++
SOLDFLAGS = -L$(LIBPATH) -lzlib1 -lws2_32 -shared -static-libgcc -static-libstdc++

ifeq (lin64, $(TARGET))
  LDFLAGS = -L$(LIBPATH) -lglfw3dll -lglew32 -lglfw3 -lopengl32 -lglu32 -lgdi32 -lz
else ifeq (win64, $(TARGET))
  LDFLAGS = -L$(LIBPATH) -lglfw3dll -lws2_32 -lglew32 -lglfw3 -lopengl32 -lglu32 -lgdi32 -lzlib1 -llestpng -pthread -static-libgcc -static-libstdc++ -llestttf
endif


MAKEFLAGS += -rR --no-print-directory

all : $(programs)

linkFiles  = common.cpp \
             game.cpp

stateFiles = state.cpp \
             mainMenuState.cpp \
             exceptionState.cpp \
						 sandboxState.cpp

windowFiles = renderWindow.cpp \
              renderTarget.cpp \
							window.cpp

resourceFiles = image.cpp \
                font.cpp

drawableFiles = dot.cpp \
								text.cpp \
								sprite.cpp \
								nineSlicedSprite.cpp

renderEngineFiles = indexBuffer.cpp \
										shader.cpp \
										vertexBuffer.cpp \
										vertexArray.cpp \
										texture2D.cpp \
										frameBuffer.cpp

rendererFiles = renderer2D.cpp \
                camera.cpp

inputFiles = input.cpp \
						 mouse.cpp \
						 keyboard.cpp \
						 mouseEvent.cpp \
						 keyboardEvent.cpp \
						 windowEvent.cpp

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
								frame.cpp

graphicsEventsFiles = itemEvent.cpp

lestEngineEventFiles =
dynLibFiles = png.cpp

utilityFiles = edgeTable.cpp \
							 transform.cpp

objs := $(patsubst %.cxx, %.o, $(entrypoint))

objs += $(patsubst %.cpp, %.o, $(linkFiles))

states = $(patsubst %.cpp, %.o, $(stateFiles))
stateObjs = $(addprefix $(STATEPATH)/, $(states))

window = $(patsubst %.cpp, %.o, $(windowFiles))
windowObjs = $(addprefix $(WINDOWPATH)/, $(window))

resources = $(patsubst %.cpp, %.o, $(resourceFiles))
resourceObjs = $(addprefix $(RESOURCEPATH)/, $(resources))

drawables = $(patsubst %.cpp, %.o, $(drawableFiles))
drawableObjs = $(addprefix $(DRAWABLESPATH)/, $(drawables))

renderEngine = $(patsubst %.cpp, %.o, $(renderEngineFiles))
renderEngineObjs = $(addprefix $(RENDERENGINEPATH)/, $(renderEngine))

renderer = $(patsubst %.cpp, %.o, $(rendererFiles))
rendererObjs = $(addprefix $(RENDERERPATH)/, $(renderer))

graphics = $(patsubst %.cpp, %.o, $(graphicsFiles))
graphicsObjs = $(addprefix $(GRAPHICSPATH)/, $(graphics))

graphicsEvents = $(patsubst %.cpp, %.o, $(graphicsEventsFiles))
graphicsEventsObjs = $(addprefix $(GRAPHICSEVENTPATH)/, $(graphicsEvents))

lestEngineEvents = $(patsubst %.cpp, %.o, $(lestEngineEventFiles))
lestEngineEventsObjs = $(addprefix $(LESTENGINEEVENTSPATH)/, $(lestEngineEvents))

inputs = $(patsubst %.cpp, %.o, $(inputFiles))
inputObjs = $(addprefix $(INPUTPATH)/, $(inputs))

dynLibPrefix = lest

utilities = $(patsubst %.cpp, %.o, $(utilityFiles))
utilitiesObjs = $(addprefix $(UTILITYPATH)/, $(utilities))

deps := $(patsubst %.o, %.d, $(objs))
deps += $(patsubst %.o, %.d, $(stateObjs))
deps += $(patsubst %.o, %.d, $(guiObjs))
deps += $(patsubst %.o, %.d, $(windowObjs))
deps += $(patsubst %.o, %.d, $(drawableObjs))

# include $(deps)
ifneq ($(DEBUG), 1)
  Q=@
  DEBUG = 0
endif

export

$(STATEPATH): $(WINDOWPATH)
	@echo "MAKE	States"
	$(Q)$(MAKE)  V=$(V) D=$(D) -C $(STATEPATH)

$(DRAWABLESPATH):
	@echo "MAKE	Drawables"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(DRAWABLESPATH)

$(WINDOWPATH):
	@echo "MAKE	Window"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(WINDOWPATH)

$(RENDERENGINEPATH):
	@echo "MAKE	Render Engine"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(RENDERENGINEPATH)

$(RENDERERPATH):
	@echo "MAKE	Renderer"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(RENDERERPATH)

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

$(GRAPHICSEVENTPATH):
	@echo "MAKE	Graphics Events"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(GRAPHICSEVENTPATH)

$(LESTENGINEEVENTSPATH):
	@echo "MAKE	Lest Engine Events"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(LESTENGINEEVENTSPATH)

shader:
		@echo "Copying Shaders"
		$(Q)cp -r $(SHADERSPATH) $(PATHTOEXEC)

font:
		@echo "Copying Fonts"
		$(Q)cp -r $(FONTSPATH) $(PATHTOEXEC)

$(programs): $(objs) $(STATEPATH) $(DRAWABLESPATH) $(WINDOWPATH) $(RENDERENGINEPATH) $(RENDERERPATH) \
       $(RESOURCEPATH) $(GRAPHICSPATH) $(UTILITYPATH) $(INPUTPATH) $(GRAPHICSEVENTPATH) $(LESTENGINEEVENTSPATH)
	@echo "MAKE $@"
	$(Q)$(CC) $(CFLAGS) -o $@ $(objs) $(stateObjs) $(windowObjs) $(drawableObjs) $(utilitiesObjs) $(renderEngineObjs) \
	$(rendererObjs) $(resourceObjs) $(graphicsObjs) $(inputObjs) $(graphicsEventsObjs) $(lestEngineEventsObjs) $(LDFLAGS)
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
		cp $(LIBPATH)/lestpng.dll $(PATHTOEXEC); \
		cp $(LIBPATH)/lestttf.dll $(PATHTOEXEC); \
		cp $(FONTPATH)/Envy\ Code\ R.ttf $(PATHTOEXEC); \
		cp -r $(SHADERSPATH) $(PATHTOEXEC); \
		cp -r $(FONTSPATH) $(PATHTOEXEC); \
	else \
		echo "Checking dynamic libraries exist"; \
		if [ ! -f $(PATHTOEXEC)/lestpng.dll ]; then \
			cp $(LIBPATH)/lestpng.dll $(PATHTOEXEC)/lestpng.dll; \
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

%.out: $(objs) $(STATEPATH) $(DRAWABLESPATH) $(WINDOWPATH) $(UTILITYPATH)
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
		cp $(DYNLIBSPATH)/liblestpng.dll $(PATHTOEXECLINUX); \
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

clean_renderengine:
	@echo "Clean Render Engine"
	@for item in ${renderEngineObjs}; do \
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

clean_renderer:
	@echo "Clean Renderer"
	@for item in ${rendererObjs}; do \
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
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(RENDERERPATH)
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(GRAPHICSPATH)
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(RESOURCEPATH)
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(INPUTPATH)
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(GRAPHICSEVENTPATH)
	$(Q)$(MAKE) clean_dep V=$(V) D=$(D) -C $(LESTENGINEEVENTSPATH)

clean_exe:
	@echo "Clean Executable"
	@if [ -f $(programs) ]; then \
		echo "Rm $(programs)"; \
		rm $(programs); \
	fi

clean: clean_state clean_window clean_drawable clean_main clean_dep clean_exe clean_utilities \
       clean_renderengine clean_renderer clean_graphics clean_resource clean_input clean_graph_events \
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

.PRECIOUS: %.o $(STATEPATH)/%.o $(WINDOWPATH)/%.o $(RESOURCEPATH)/%.o $(DRAWABLESPATH)/%.o $(RENDERENGINEPATH)/%.o \
           $(GRAPHICSPATH)/%.o $(UTILITYPATH)/%.o $(INPUTPATH)/%.o $(RENDERERPATH)/%.o $(GRAPHICSEVENTPATH)/%.o \
					 $(LESTENGINEEVENTSPATH)/%.o
.PHONY: $(STATEPATH) $(DRAWABLESPATH) $(WINDOWPATH) $(RESOURCEPATH) $(UTILITYPATH) $(RENDERENGINEPATH) \
        $(GRAPHICSPATH) $(INPUTPATH) $(RENDERERPATH) $(GRAPHICSEVENTPATH) $(LESTENGINEEVENTSPATH)
