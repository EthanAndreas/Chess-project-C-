CC = g++
CFLAGS = -O3 -pipe -Wall -Werror -Wextra -g 

INCLUDE_DIR = ./include
TARGET = exe 
SRCDIR = src
OBJDIR = obj
BINDIR = bin

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCLUDE_DIR)/*.h)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all : $(BINDIR)/$(TARGET)

.PHONY : docs
docs:
	@echo "\033[95mBuilding documentation...\033[0m"
	@doxygen ./Doxyfile > /dev/null 2>&1
	@echo "\033[92mDocumentation built!\033[0m"

$(BINDIR)/$(TARGET): $(OBJECTS)
	mkdir -p $(BINDIR)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "\033[92mCompiled\033[0m"
$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -isystem$(INCLUDE_DIR)

.PHONY: clean
clean:
	rm -rf obj/*.o
	rm -rf tests/obj/*.o
	rm -f $(BINDIR)/$(TARGET)
	@echo "\033[92mCleaned\033[0m"
