# SDL_Tutes
Learn some SDL
Todo: Finish the initial setup part of the readme, add in details.

# MSYS2/MinGW Setup
MSYS2 is a Unix-like shell designed for Windows. MinGW is a runtime environment for the GNU Compiler Collection (GCC). It allows us to compile C and C++ code for Windows. We will be using an MinGW alternate called MinGW-w64, which adds more 64-bit support (more info here)[https://en.wikipedia.org/wiki/MinGW#MinGW-w64]. Download msys2 from their Github page at (msys2.github.io)[msys2.github.io]. It comes in 32 and 64 bit flavors. Grab whichever one is right for  your version of Windows. When the installer asks where you would like to install it, it's very important you choose a location that does not have any spaces in the path. I created a folder called Development under the C: drive and installed it there (C:\Development\msys64).

Once the installation finishes, run msys2. The "Run MSYS2 64bit now" box should be checked already, so it will run when you click "Finish" on the installer. The first thing you'll want to do is update all core packages that are already installed. Run `pacman -Su`, and any required updates will complete automatically. Once the updates are finished, exit the shell, go to the folder where you installed msys2, and run the mingw64.exe executable. This is our mingw64 bash shell, and it's where we'll be doing most of the work from here on out. Run `pacman -Su` once again to update any packages. We then want to install a handful of useful packages for developing in C/C++. Run the command `pacman --needed -Syu git mingw-w64-x86_64-gcc base-devel` to install git, gcc, and a "base developer" package that comes with many handy tools.

Once the installation completes, test that some of the packages are there and up-to-date by running `git --version`, `make --version`, and `gcc --version`.

# SDL Setup
This got a little sketchy, and I need to try setting this up again to see if I actually do have a better way of doing this. My steps:
Download development libraries (here)[http://libsdl.org/download-2.0.php]. Make sure to grab the "SDL2-devel-2.0.5-mingw.tar.gz" library. 
Essentially follow the tutorial on lazyfoo's site.

**OR**

We can try just using the pacman package manager that comes with msys2. It may take care of everything for us, need to verify this. Even if this does work, we still likely need to put the include and library directories in our makefiles. Here are some of the SDL-related packages that appear to be available via pacman:
mingw-w64-x86_64-SDL2
mingw-w64-x86_64-libpng
mingw-w64-x86_64-SDL_ttf
mingw-w64-x86_64-SDL_mixer

# Project Setup
Get Sublime 3 Text from their (site)[https://www.sublimetext.com/3]
Set up desired user settings in Preferences->Settings
Set up SSH key for github repo