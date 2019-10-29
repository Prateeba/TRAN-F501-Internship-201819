SHELL= /bin/bash
CC:=g++ 

#compilation target name
TARGET := main

#directories for source code and build-files
BUILDDIR :=  build
SRCDIR :=  src
SRCEXT := cpp
INCLUDEDIR := include
SIMDIR := data

#COMPILATION AND LIBARY FLAGS
LDLIBS = #-L /usr/local/lib/  #-lm -lboost_serialization -lgsl

WARNINGS := -Wall -pedantic -Wextra -Wshadow  -Wcast-qual  -Weffc++ -Wfloat-equal -Wunreachable-code   -Wdisabled-optimization

OPTIDEBUG := -O3 -DNDEBUG

CFLAGS := -std=c++17 $(OPTIDEBUG) $(WARNINGS) -I./$(INCLUDEDIR)/

SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPS = $(OBJECTS:%.o=%.d)


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC)  $(CFLAGS)  -o $(TARGET) $(OBJECTS) $(LDLIBS)

./$(BUILDDIR)/%.o : ./$(SRCDIR)/%.$(SRCEXT)
	$(CC) $(CFLAGS)  -c -o $@ $<

dep: $(DEPS)

$(BUILDDIR)/%.d: $(SRCDIR)/%.$(SRCEXT)
	$(CC) $(CFLAGS) -MM  -MT '$(subst .d,.o,$@)'  $< -MF $@ 

clean : 
	rm -f $(TARGET) $(OBJECTS) $(DEPS) $(OBJSUT) $(OBJSPT)

run: all
	./$(TARGET)