
steps to build lib.bc and lib.js
1. type make OPTIMIZE=[-gx] to get libVCS.bc
   where [-gx] could be -g0, -g1, -g2 or -g3
2. type emcc [-gx] libVCS.bc -o libVCS.js to get libVCS.js
   where [-gx] could be -g0, -g1, -g2 or -g3
Please note use same [-gx] flag for .bc and .js