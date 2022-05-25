SHELL := /bin/bash
CC = x86_64-w64-mingw32-g++
LIBPATH = ../lib
INCLPATH = ../include
HEADERS= ./headers
PATHTOEXEC = ../objs-wind64
STATEPATH = ./states
RENDERERSPATH = ./renderer
GUIPATH = ./gui
DRAWABLESPATH = ./drawable
SRC = ./src
SHADERSPATH = ./shaders
FONTSPATH = ./fonts

SHADER = $(SHADERSPATH)/shader1.txt

CFLAGS  = -g -std=c++17 -Wall -Wextra -MMD -static-libgcc -static-libstdc++ -I$(INCLPATH) -I$(LIBPATH) -I$(HEADERS)
LDFLAGS = -L$(LIBPATH) -lglfw3dll -lws2_32 -lglew32 -lglfw3 -lopengl32 -lglu32 -lgdi32

MAKEFLAGS += -rR --no-print-directory

programs = main.exe

all : $(programs)

linkFiles  = common.c \
             game.c \
             state.c

stateFiles = mainMenuState.c

guiFiles   = gui.c

rendererFiles =  renderWindow.c \
                 renderTarget.c \
                 font.c

drawableFiles = indexBuffer.c \
                shader.c \
                batchBuffer.c \
                vertexBuffer.c \
                vertexArray.c \
                rectangle.c

objs := $(patsubst %.exe, %.o, $(programs))
objs += $(patsubst %.c, %.o, $(linkFiles))

states = $(patsubst %.c, %.o, $(stateFiles))
stateObjs = $(addprefix $(STATEPATH)/, $(states))

GUI = $(patsubst %.c, %.o, $(guiFiles))
guiObjs = $(addprefix $(GUIPATH)/, $(GUI))

renderers = $(patsubst %.c, %.o, $(rendererFiles))
rendererObjs = $(addprefix $(RENDERERSPATH)/, $(renderers))

drawables = $(patsubst %.c, %.o, $(drawableFiles))
drawableObjs = $(addprefix $(DRAWABLESPATH)/, $(drawables))

ifneq ($(DEBUG), 1)
  Q=@
  DEBUG = 0
endif

deps := $(patsubst %.o, %.d, $(objs))
-include $(deps)

export

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

%.exe: $(objs) $(STATEPATH) $(GUIPATH) $(DRAWABLESPATH) $(RENDERERSPATH)
	@echo "MAKE $@"
	$(Q)$(CC) $(CFLAGS) -o $@ $(objs) $(stateObjs) $(guiObjs) $(rendererObjs) $(drawableObjs) $(LDFLAGS)
	@echo "Checking DIR"
	$(Q)if [ ! -d $(PATHTOEXEC) ]; then \
		echo "Creating Win DIR"; \
		mkdir $(PATHTOEXEC); \
		echo "Adding opengldll"; \
		cp $(LIBPATH)/glfw3.dll $(PATHTOEXEC); \
		cp $(LIBPATH)/glew32.dll $(PATHTOEXEC); \
		cp -r $(SHADERSPATH) $(PATHTOEXEC); \
		cp -r $(FONTSPATH) $(PATHTOEXEC); \
	fi
	@echo "Transferring .exe"
	$(Q)cp $@ $(PATHTOEXEC)

main.o: main.cxx
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c

%.o: %.c
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c 

clean:
	@echo "CLEAN ALL"
	$(Q)rm *.o *.exe *.d $(STATEPATH)/*.o $(STATEPATH)/*.d $(GUIPATH)/*.o $(GUIPATH)/*.d \
	 $(RENDERERSPATH)/*.o $(RENDERERSPATH)/*.d $(DRAWABLESPATH)/*.o $(DRAWABLESPATH)/*.d
	@echo "Checking win DIR"
	$(Q)if [ -d $(PATHTOEXEC) ]; then \
		echo "RM Win DIR"; \
		rm -rf $(PATHTOEXEC); \
	fi

.PRECIOUS: %.o $(STATEPATH)/%.o $(GUIPATH)/%.o $(RENDERERSPATH)/%.o $(DRAWABLESPATH)/%.o
.PHONY: $(STATEPATH) $(GUIPATH) $(DRAWABLESPATH) $(RENDERERSPATH)
