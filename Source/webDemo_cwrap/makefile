CC=emcc
INCLUDE = -I../../../../main/source/inc  
CPPFLAGS = $(INCLUDE) -Wno-c++11-narrowing -D_MAC

SRCS = ../../../../main/source/src/*.cpp
SRCS += Wrapper.cpp

EXPORTS_FILE=makefile_exports.txt
OUTPUT=VCS.js

# Optimize flag
OPTIMIZE = -O3
CPPFLAGS += $(OPTIMIZE)
CPPFLAGS += --memory-init-file 0

set EMCC_DEBUG=1

$(OUTPUT): $(SRCS)
	$(CC) $(CPPFLAGS) $(SRCS) -o $(OUTPUT) -std=c++11 -s EXPORTED_FUNCTIONS=@$(EXPORTS_FILE)

set EMCC_DEBUG=0

