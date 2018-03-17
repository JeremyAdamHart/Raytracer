CC=g++

CFLAGS=-std=c++11 -O3 -Wall -g
LINKFLAGS=-O3

#debug = true
ifdef debug
	CFLAGS +=-g
endif

INCDIR= -I./include

LIBDIR=

LIBS=

OS_NAME:=$(shell uname -s)

LIBS += `pkg-config --static --libs glfw3 gl`

SRCDIR=./Raytracer

SRCLIST=$(wildcard $(SRCDIR)/*cpp) 

HEADERDIR=./boilerplate

OBJDIR=./obj

OBJLIST=$(addprefix $(OBJDIR)/,$(notdir $(SRCLIST:.cpp=.o)))

EXECUTABLE=raytrace.out

all: buildDirectories $(EXECUTABLE) 

$(EXECUTABLE): $(OBJLIST)
	$(CC) $(LINKFLAGS) $(OBJLIST) -o $@ $(LIBS) $(LIBDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) -I$(HEADERDIR) $(INCDIR) $(LIBDIR) $< -o $@

.PHONY: buildDirectories
buildDirectories:
	mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	rm -f *.out $(OBJDIR)/*.o; rmdir obj;
