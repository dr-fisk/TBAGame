SHELL := /bin/bash
CC = x86_64-w64-mingw32-g++
LIBPATH = ../lib
INCLPATH = ../include
HEADERS= ./headers
PATHTOEXEC = ../objs-wind64
STATEPATH = ./states
GRAPHICSPATH = ./graphics
GUIPATH = ./gui
SRC = ./src
SHADERSPATH = ./shaders
CFLAGS  = -g -std=c++17 -Wall -Wextra -MMD -I$(INCLPATH) -I$(LIBPATH) -I$(HEADERS)
LDFLAGS = -L$(LIBPATH) -lglfw3dll -lws2_32 -lglew32 -lglfw3 -lopengl32 -lglu32 -lgdi32

MAKEFLAGS += -rR

programs = main.exe

all : $(programs)

linkFiles  = common.c \
             game.c \
             state.c \
             rectangle.c

stateFiles = mainMenuState.c

guiFiles   = gui.c

graphicFiles = renderWindow.c \
               renderTarget.c \
               vertexBuffer.c \
               vertexArray.c \
               indexBuffer.c \
               shader.c \
               batchBuffer.c

objs := $(patsubst %.exe, %.o, $(programs))

objs += $(patsubst %.c, %.o, $(linkFiles))

states = $(patsubst %.c, %.o, $(stateFiles))
stateObjs = $(addprefix $(STATEPATH)/, $(states))

GUI = $(patsubst %.c, %.o, $(guiFiles))
guiObjs = $(addprefix $(GUIPATH)/, $(GUI))

graphics = $(patsubst %.c, %.o, $(graphicFiles))
graphicObjs = $(addprefix $(GRAPHICSPATH)/, $(graphics))

ifneq ($(DEBUG), 1)
  Q=@
  DEBUG = 0
endif

deps := $(patsubst %.o, %.d, $(objs))
-include $(deps)

export

$(STATEPATH)/%.o : $(STATEPATH)/%.c
	@echo "MAKE	States"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(STATEPATH)

$(GUIPATH)/%.o : $(GUIPATH)/%.c
	@echo "MAKE	Gui"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(GUIPATH)

$(GRAPHICSPATH)/%.o : $(GRAPHICSPATH)/%.c
	@echo "MAKE	Graphics"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(GRAPHICSPATH)

%.exe: $(objs) $(stateObjs) $(guiObjs) $(graphicObjs)
	@echo "MAKE $@"
	$(Q)$(CC) $(CFLAGS) -o $@ $(objs) $(stateObjs) $(guiObjs) $(graphicObjs) $(LDFLAGS)
	@echo "Checking DIR"
	$(Q)if [ ! -d $(PATHTOEXEC) ]; then \
	  	echo "Creating Win DIR"; \
		mkdir $(PATHTOEXEC); \
		echo "Adding opengldll"; \
		cp $(LIBPATH)/glfw3.dll $(PATHTOEXEC); \
		cp $(LIBPATH)/glew32.dll $(PATHTOEXEC); \
		cp -r $(SHADERSPATH) $(PATHTOEXEC); \
	fi
	@echo "Transfering .exe"
	$(Q)cp $@ $(PATHTOEXEC)

%.o: %.cxx
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c

%.o: %.c
	@echo "MAKE $<"
	$(Q)$(CC) $(CFLAGS) $< $(LDFLAGS) -c 

clean:
	@echo "CLEAN ALL"
	$(Q)rm *.o *.exe *.d $(STATEPATH)/*.o $(STATEPATH)/*.d $(GUIPATH)/*.o $(GUIPATH)/*.d
	@echo "Checking win DIR"
	$(Q)if [ -d $(PATHTOEXEC) ]; then \
		echo "RM Win DIR"; \
		rm -rf $(PATHTOEXEC); \
	fi

.PRECIOUS: %.o $(STATEPATH)/%.o $(GUIPATH)/%.o $(GRAPHICSPATH)/%.o
