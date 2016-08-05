
steps to test emscripten VCS peformance:
1. install emscripten tool
2. add emscripten path to your enviorment using command
export PATH=$PATH:/Users/cnyzgkn/Git/emscripten/emsdk_portable/emscripten/1.29.0
make sure can run emcc in your command window
3. change which VCS test case you needed in test_VCS.cpp
4. type emmake make [-gx] to generate test_VCS.bc 
   where [-gx] could be -g0, -g1, -g2, -g3 or -g4
4. make sure libVCS.bc was generated correctly in WebVCS/Source/webVCSLib folder
5. type 
emcc --memory-init-file 0 -s ALLOW_MEMORY_GROWTH=1 -s NO_EXIT_RUNTIME=1 -s DISABLE_EXCEPTION_CATCHING=0 ../webVCSLib/libVCS.bc test_VCS.bc -o test_VCS.html [-gx]
to generate test_VCS.js and test_VCS.html
please note if you use -g4 it will generate a .hmtl.map file containing debug information
6. open test_VCS.html in web browser and see the time cost

steps to test native VCS peformance in Mac:
1. install emscripten tool
2. add emscripten path to your enviorment using command
export PATH=$PATH:/Users/cnyzgkn/Git/emscripten/emsdk_portable/emscripten/1.29.0
make sure can run emcc in your command window
3. change which VCS test case you needed in test_VCS.cpp
4. type emmake make -f makefile_test PLATTARGET=-Mac to generate test_VCS
5. type otool -L test_VCS to check where test_VCS use libVCS.dylib in running time and make sure it has the correct version of libVCS.dylib in this folder
We suggest use ../../../../main/source/src/libVCS.dylib
You can use install_name_tool -change @rpath/VCS/libVCS.dylib ../../../../main/source/src/libVCS.dylib test_VCS to re-direct the link library
6. type ./test_VCS to see the result

steps to run a simple web sever in your mac:
1. go to the folder where the .html files are, like VCS/Tools/WebVCS/Source/webVCSTest
2. type python -m SimpleHTTPServer 8000 to open the server
3. in web browser, type http://127.0.0.1:8000/test_VCS.html

need to do:
use -rpath or -install_name in makefile to avoid change the path in the created libVCS.dylib manually
but it seems osX not compatible with these flags
just list them here:
CPPFLAGS += -install_name../../../../main/source/src/libVCS.dylib
CPPFLAGS += -Wl,-rpath=../../../../main/source/src
DYLD_FALLBACK_LIBRARY_PATH = ../../../../main/source/src
LD_LIBRARY_PATH = ../../../../main/source/src
LDFLAGS = -rpath../../../../main/source/src