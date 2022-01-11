# Install GCC
## Step by step
1. Download and install MSYS2(x86_64) https://www.msys2.org/
2. Open the MSYS2 Shell window
3. in the shell...
```
$ pacman -Syu
$ -S mingw-w64-x86_64-toolchain
$ pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-extra-cmake-modules
```
- Instead the last line above, I select a number _3) mingw-w64-x86_64-gcc_
  - At first, I installed _15) mingw-w64-x86_64-make_ instead of entering it because I overlooked the part of the command and it didn't work
4. (Continued) Add ~/mingw64/bin to environment variable Path (You can find the location in C:\msys64\)
5. Open cmd and put _gcc -v_ to check if the installation is successfully done and what the version is
