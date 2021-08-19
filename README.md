# TIEMERALDCE
Broken code. Please help. Probably not the final repository though.

Error message when compiling just testBattle.cpp
fatal error: error in backend: Error while trying to spill UBC from class O24: Cannot scavenge register without an emergency spill slot!
PLEASE submit a bug report to https://bugs.llvm.org/ and include the crash backtrace, preprocessed source, and associated run script.
Stack dump:
0.      Program arguments: C:\\CEdev\\bin\\ez80-clang.exe -S -nostdinc -isystem C:\\CEdev/include -Isrc -Dinterrupt=__attribute__((__interrupt__)) -Wno-main-return-type -Xclang -fforce-mangle-main-argc-argv -mllvm -profile-guided-section-prefix=false -D_EZ80 -DNDEBUG -g0 -Wall -Wextra -Oz -fno-exceptions -fno-rtti -Wall -Wextra 
-Oz -Wno-reorder-ctor C:/CEdev/examples/TiEmeraldCE/src/testBattle.cpp -o C:/CEdev/examples/TiEmeraldCE/obj/testBattle.cpp.src
1.      <eof> parser at end of file
2.      Code generation
3.      Running pass 'Function Pass Manager' on module 'C:/CEdev/examples/TiEmeraldCE/src/testBattle.cpp'.
4.      Running pass 'Prologue/Epilogue Insertion & Frame Finalization' on function '@_Z10damageCalc7PokemonS_4MovePh'
 #0 0x766fb512 (C:\WINDOWS\System32\KERNELBASE.dll+0x12b512)
 #1 0x0110e2c6 (C:\CEdev\bin\ez80-clang.exe+0x3ae2c6)
 #2 0x75a73c68 (C:\WINDOWS\System32\ucrtbase.dll+0x33c68)
 #3 0x033202d4 (C:\CEdev\bin\ez80-clang.exe+0x25c02d4)
 #4 0x00d6d867 (C:\CEdev\bin\ez80-clang.exe+0xd867)
 #5 0x0110e4ee (C:\CEdev\bin\ez80-clang.exe+0x3ae4ee)
 #6 0x01d0fd7f (C:\CEdev\bin\ez80-clang.exe+0xfafd7f)
 #7 0x01d0ff53 (C:\CEdev\bin\ez80-clang.exe+0xfaff53)
 #8 0x01d1021e (C:\CEdev\bin\ez80-clang.exe+0xfb021e)
 #9 0x013458cb (C:\CEdev\bin\ez80-clang.exe+0x5e58cb)
ez80-clang: error: clang frontend command failed with exit code 70 (use -v to see invocation)
clang version 12.0.0 (https://github.com/jacobly0/llvm-project 170be88120e3aa88c20eea5615ba76b8f1d6c647)
Target: ez80
Thread model: posix
InstalledDir: C:\CEdev\bin
ez80-clang: note: diagnostic msg: 
********************

PLEASE ATTACH THE FOLLOWING FILES TO THE BUG REPORT:
Preprocessed source(s) and associated run script(s) are located at:
ez80-clang: note: diagnostic msg: C:\Users\admin\AppData\Local\Temp\testBattle-a6d392.cpp
ez80-clang: note: diagnostic msg: C:\Users\admin\AppData\Local\Temp\testBattle-a6d392.sh
ez80-clang: note: diagnostic msg:

********************
make: *** [obj/testBattle.cpp.src] Error 70
  
##YOU SHOULD also try replacing testbattle.cpp with main.cpp, same issue.
