CC=emcc
INCLUDE = -I../../../../main/source/inc  
CPPFLAGS = $(INCLUDE) -Wno-c++11-narrowing -D_MAC -w

SRCS = ../../../../main/source/src/*.cpp
SRCS += VCSWrapper.cpp

OUTPUT=VCSWrapper.js

# Optimize flag
OPTIMIZE = -O3
CPPFLAGS += $(OPTIMIZE)
CPPFLAGS += --memory-init-file 0

set EMCC_DEBUG=1

$(OUTPUT): $(SRCS)
	$(CC) --bind $(CPPFLAGS) $(SRCS) -o $(OUTPUT) -std=c++11 

set EMCC_DEBUG=0

