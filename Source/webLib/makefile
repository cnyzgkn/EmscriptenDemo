# VCS makefile for web
# This makefile only works for emscripten compiler emcc/em++

# Source files
INCLUDE = -I../../../../main/source/inc
SRCS = ../../../../main/source/src/*.cpp

# Basic flags
CC = em++
CPPFLAGS = $(INCLUDE) -DVCS_EXPORTS -Wconversion -fvisibility-ms-compat -fvisibility-inlines-hidden -D_MAC
LFLAGS = -Wall 
OUTPUT = lib.bc 

# Optimize flag
OPTIMIZE = -O3
CPPFLAGS += $(OPTIMIZE)
CPPFLAGS += --memory-init-file 0
CPPFLAGS += -s DISABLE_EXCEPTION_CATCHING=0
CPPFLAGS += -s NO_EXIT_RUNTIME=1
CPPFLAGS += -s ALLOW_MEMORY_GROWTH=1

# Build libVCS.bc for emscripten
$(OUTPUT): $(SRCS)
	$(CC) -o $(OUTPUT) $(CPPFLAGS) $(SRCS) 

.PHONY:clean
clean:
	\rm *.o *.d *.bc 
