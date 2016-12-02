# SDL_Tutes
Learn me some SDL
Todo: Finish the initial setup part of the readme, add in details.

# MSYS2/MinGW Background and Setup
MSYS2 is a Unix-like shell designed for Windows. MinGW is a runtime environment for the GNU Compiler Collection (GCC). It allows us to compile C and C++ code for Windows. We will be using an MinGW alternate called MinGW-w64, which adds more 64-bit support [more info here](https://en.wikipedia.org/wiki/MinGW#MinGW-w64). Download msys2 from their Github page at [msys2.github.io](msys2.github.io). It comes in 32 and 64 bit flavors. Grab whichever one is right for  your version of Windows. When the installer asks where you would like to install it, it's very important you choose a location that does not have any spaces in the path. I created a folder called Development under the C: drive and installed it there (C:\Development\msys64).

Once the installation finishes, run msys2. The "Run MSYS2 64bit now" box should be checked already, so it will run when you click "Finish" on the installer. The first thing you'll want to do is update all core packages that are already installed. Run `pacman -Su`, and any required updates will complete automatically. Once the updates are finished, exit the shell, go to the folder where you installed msys2, and run the mingw64.exe executable. This is our mingw64 bash shell, and it's where we'll be doing most of the work from here on out. Run `pacman -Su` once again to update any packages. We then want to install a handful of useful packages for developing in C/C++. Run the command `pacman --needed -Syu git mingw-w64-x86_64-gcc base-devel` to install git, gcc, and a "base developer" package that comes with many handy tools.

Once the installation completes, test that some of the packages are there and up-to-date by running `git --version`, `make --version`, and `gcc --version`.

# SDL Setup
This got a little sketchy, and I need to try setting this up again to see if I actually do have a better way of doing this. My steps:
* Download development libraries [here](http://libsdl.org/download-2.0.php). 
* Make sure to grab the "SDL2-devel-2.0.5-mingw.tar.gz" library. 
* Essentially follow the tutorial on [lazyfoo's](http://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/mingw/index.php) site.

**OR**

We can try just using the pacman package manager that comes with msys2. It may take care of everything for us, need to verify this. Even if this does work, we still likely need to put the include and library directories in our makefiles. Using  `pacman -Ss SDL` shows some of the SDL-related packages that are available:

* mingw-w64-x86_64-SDL2                 <-- Main SDL library
* mingw-w64-x86_64-SDL2_image  <-- Library for loading images of various formats
* mingw-w64-x86_64-SDL_ttf              <-- SDL TrueType fonts library

**ACTUALLY**

It appears to be a mix of the two? Looks like I need to manually download the tar balls and unpack them, then copy the contents of the top-level 64bit folder into some folder that I can point to with my makefile. I put mine into /var/lib/x86_64-w64-mingw32. Next, run the pacman command `pacman --needed -Syu <package>` to (I guess) handle setting up the compiler to look in the proper place(s) for dll files and stuff. Before trying to build, we need to add lines in the makefile to make sure the Library (the `LIBRARY_PATHS` line) & Include (the `INCLUDE_PATHS` line) directories for the SDL packages are located. We also need to add a line for `LINKER_FLAGS` and add an entry for every SDL library we want to link to.

As we add more SDL libraries to our system, the above steps essentially just repeat. We'll download the tar, then add the x86_64-w64-mingw32 folder to the one already in /var/lib. This will merge the two and keep us from needing to add more Library or Include lines to the makefile. We just have to add the entry in the Linker line so that the program can find the right DLLs, and we're good to go!

This still seems like a weird method, and is likely due to me messing up the manual way, or a bug or something in the pacman way. Still needs a bit more investigation. 

# Project Setup
* Get Sublime 3 Text from their [site](https://www.sublimetext.com/3)
* Set up desired user settings in Preferences->Settings
* Set up SSH key for github repo
* Clone in project via SSH link
