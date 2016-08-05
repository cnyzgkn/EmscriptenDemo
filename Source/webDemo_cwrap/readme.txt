steps to run webVCS demo using cwrap:
1. install emscripten tool
2. add emscripten path to your enviorment using command
export PATH=$PATH:/Users/cnyzgkn/Git/emscripten/emsdk_portable/emscripten/1.29.0
make sure can run emcc in your command window
3. go to webVCSDemo_cwrap folder
4. type emmake make OPTIMIZE=[-gx] to generate VCS.js 
   where [-gx] could be -g0, -g1, -g2, -g3 or -g4
   note if use -g4 you’ll get an extra VCS.js.map containing debug information
5. open run_vcs_sample_cwrap.html in web browser
