/* Left off on tutorial 10.*/

// Source Includes
#include "texture.hpp"
#include "application.hpp"

// SDL Includes
#include "SDL.h"
#include "SDL_image.h"

// Standard C++ Includes
#include <stdio.h>
#include <string>

/**************************************************************************************
* Function: main()
* Description: Entry point of the application. Calls functions to run SDL and start our app.
* Args: argc - integer indicating how many arguments are being passed to the application.
        args[] - array of pointers to pointers to the actual arguments being passed in.
* Return: integer return value indicating status
**************************************************************************************/
int main(int argc, char* args[])
{
 
 // Create an instace of our application.
 Application my_app(640, 480, false);

// Execute the app.
 my_app.execute();

  return 0;
}
  

