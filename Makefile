CC = g++
CFLAGS = -O0 -Wall -Werror -g 

INCLUDE_DIR = ./include
TARGET = exe 
SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCLUDE_DIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all : $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -isystem$(INCLUDE_DIR)

.PHONY: clean
clean:
	rm -rf obj/*.o
	rm -rf tests/obj/*.o
	rm -f $(BINDIR)/$(TARGET)
