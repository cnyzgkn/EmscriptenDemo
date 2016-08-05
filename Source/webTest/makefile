# hello_vcs makefile for Mac and Linux
# This makefile only works for emscripten compiler emcc/em++

CC = em++
OUTPUT = test_VCS.bc 

# Source files
INCLUDE = -I../../../../main/source/inc
SRCS = test_VCS.cpp

# Basic flags
CPPFLAGS = $(INCLUDE) -DVCS_EXPORTS -Wconversion -fvisibility-ms-compat -fvisibility-inlines-hidden -D_MAC
LFLAGS = -Wall 

# Platform target: Web or Mac
PLATTARGET = -Web

ifeq ($(PLATTARGET), -Web)
	CC = em++
	OUTPUT = test_VCS.bc 
	# Optimize flag
	OPTIMIZE = -O3
	CPPFLAGS += $(OPTIMIZE)
	CPPFLAGS += --memory-init-file 0
	CPPFLAGS += -s DISABLE_EXCEPTION_CATCHING=0
	CPPFLAGS += -s NO_EXIT_RUNTIME=1
	CPPFLAGS += -s ALLOW_MEMORY_GROWTH=1
endif

ifeq ($(PLATTARGET), -Mac)
	CC = g++
	OUTPUT = test_VCS
	CPPFLAGS += -lVCS
	CPPFLAGS += -L../../../../main/source/src
endif

# Build target
$(OUTPUT) : $(SRCS)
	$(CC) -o $(OUTPUT) $(CPPFLAGS) $(SRCS) 

.PHONY:clean
clean:
	\rm *.o *.so *.a *.js *.html *.o *.bc
