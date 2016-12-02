/* Left off on tutorial 7.*/

// SDL Includes
#include <SDL.h>
#include <SDL_image.h>

// Standard C++ Includes
#include <stdio.h>
#include <string>

/////////////////// GLOBAL CONSTS /////////////////////

// Screen dimensions.
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const bool STRETCH_IMAGE = false;

// Key press surfaces enum use to identify the different
// surfaces we'll load when we receive user input.
enum KeyPressSurfaces
{
  KEY_PRESS_SURFACE_DEFAULT,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL
};

/////////////////// GLOBAL VARS ///////////////////////

// The window we'll be rendering to.
SDL_Window* g_window_ = NULL;

// The surface contained by the window
SDL_Surface* g_screen_surface_ = NULL;

// The image we will load and show on the screen.
SDL_Surface* g_current_surface_ = NULL;

// Array of images that will correspond to a keypress.
SDL_Surface* g_keypress_surfaces_[KEY_PRESS_SURFACE_TOTAL];

/**************************************************************************************
* Function: init()
* Description: Starts up SDL and creates window.
* Args: none
* Return: bool indicating success/fail
**************************************************************************************/
bool init()
{
  // Initialize SDL.
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return false;
  }
  else
  {
    // Create the window.
    g_window_ = SDL_CreateWindow("SDL Tutorial",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      SCREEN_WIDTH,
      SCREEN_HEIGHT,
      SDL_WINDOW_SHOWN);

    if (g_window_ == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      return false;
    }
    else
    {
      // Initialize SDL-Image Library for PNG loading.
      int img_flags = IMG_INIT_PNG;
      if (!(IMG_Init(img_flags) & img_flags))
      {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
      }
      else
      {
        //Get window surface so we can display the image inside of the window.
        g_screen_surface_ = SDL_GetWindowSurface(g_window_);
      }
    }
  }
  return true;
}

/**************************************************************************************
* Function: load_surface()
* Description: Called by load_media(), this handles actually loading the desired image
*              into memory, optimizing it, and pointing an SDL Surface at it. 
* Args: std::string path to the image being loaded into memory.
* Return: A pointer to the sSDL Surface containing the image that was loaded.
**************************************************************************************/
SDL_Surface* load_surface(std::string path)
{
  // The optimized surface image we'll be returning.
  SDL_Surface* optimized_surface = NULL;

  //Load image at specified path
  SDL_Surface* loaded_surface = IMG_Load(path.c_str());
  if (loaded_surface == NULL)
  {
    printf("Unable to load image %s! SDL_Image Error: %s\n", path.c_str(), IMG_GetError());
  }
  else
  {
    // Convert surface to screen format so that it doesn't have to be formatted
    // every time that we blit the image.
    optimized_surface = SDL_ConvertSurface(loaded_surface, g_screen_surface_->format, NULL);
    if (optimized_surface == NULL)
    {
      printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    // We need to free the loaded surface since the optimized one is actually a copy.
    // TODO: Maybe have the loaded surface get returned if the optimization fails?
    SDL_FreeSurface(loaded_surface);
  }

  return optimized_surface;
}

/**************************************************************************************
* Function: load_media()
* Description: Loads media so it can be used some point in the game.
* Args: none
* Return: bool indicating success/fail
**************************************************************************************/
bool load_media()
{
  // Load success flag. Use this method instead of just returning on first failure; this
  // allows us to see all images that fail to load. 
  bool success = true;

  //Load the "default" surface.
  g_keypress_surfaces_[KEY_PRESS_SURFACE_DEFAULT] = load_surface("assets/visuals/press.bmp");
  if (g_keypress_surfaces_[KEY_PRESS_SURFACE_DEFAULT] == NULL)
  {
    printf("Failed to load default image!\n");
    success = false;
  }

  //Load the "up" surface.
  g_keypress_surfaces_[KEY_PRESS_SURFACE_UP] = load_surface("assets/visuals/up.bmp");
  if (g_keypress_surfaces_[KEY_PRESS_SURFACE_UP] == NULL)
  {
    printf("Failed to load up image!\n");
    success = false;
  }

  //Load the "down" surface.
  g_keypress_surfaces_[KEY_PRESS_SURFACE_DOWN] = load_surface("assets/visuals/down.bmp");
  if (g_keypress_surfaces_[KEY_PRESS_SURFACE_DOWN] == NULL)
  {
    printf("Failed to load down image!\n");
    success = false;
  }

  //Load the "left" surface.
  g_keypress_surfaces_[KEY_PRESS_SURFACE_LEFT] = load_surface("assets/visuals/left.bmp");
  if (g_keypress_surfaces_[KEY_PRESS_SURFACE_LEFT] == NULL)
  {
    printf("Failed to load left image!\n");
    success = false;
  }

  //Load the "right" surface.
  g_keypress_surfaces_[KEY_PRESS_SURFACE_RIGHT] = load_surface("assets/visuals/right.bmp");
  if (g_keypress_surfaces_[KEY_PRESS_SURFACE_RIGHT] == NULL)
  {
    printf("Failed to load right image!\n");
    success = false;
  }

  return success;
}

/**************************************************************************************
* Function: close()
* Description: Frees loaded media and shuts down SDL.
* Args: none
* Return: none
**************************************************************************************/
void close()
{
  //Deallocate surfaces and point them all to null.
  for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
  {
    SDL_FreeSurface(g_keypress_surfaces_[i]);
    g_keypress_surfaces_[i] = NULL;
  }

  // Point the current surface to null.
  g_current_surface_ = NULL;

  // Destroy window and point our window to null.
  SDL_DestroyWindow(g_window_);
  g_window_ = NULL;

  // Quit SDL subsystems.
  SDL_Quit();
}

/**************************************************************************************
* Function: main()
* Description: Entry point of the application. Calls functions to run SDL and start our app.
* Args: argc - integer indicating how many arguments are being passed to the application.
        args[] - array of pointers to pointers to the actual arguments being passed in.
* Return: integer return value indicating status
**************************************************************************************/
int main(int argc, char* args[])
{
  // Start up SDL and create window.
  if (!init())
  {
    printf("Failed to initialize!\n");
  }
  else
  {
    // Load media.
    if (!load_media())
    {
      printf("Failed to load media!\n");
    }
    else
    {
      // Main loop flag.
      bool quit = false;

      // SDL Event handler.
      SDL_Event app_event;

      // Set the default surface as our current surface.
      g_current_surface_ = g_keypress_surfaces_[KEY_PRESS_SURFACE_DEFAULT];

      // Main execution loop. Run until the user tells us to quit.
      while (!quit)
      {
        // Handle any events on queue.
        while (SDL_PollEvent(&app_event) != 0)
        {
          // User requests to quit (e.g. by x-ing out the window).
          if (app_event.type == SDL_QUIT)
          {
            quit = true;
          }
          // User presses a key.
          else if (app_event.type == SDL_KEYDOWN)
          {
            // Choose surfaces based on keypress
            switch (app_event.key.keysym.sym)
            {
              case SDLK_UP:
                g_current_surface_ = g_keypress_surfaces_[KEY_PRESS_SURFACE_UP];
                break;
              case SDLK_DOWN:
                g_current_surface_ = g_keypress_surfaces_[KEY_PRESS_SURFACE_DOWN];
                break;
              case SDLK_LEFT:
                g_current_surface_ = g_keypress_surfaces_[KEY_PRESS_SURFACE_LEFT];
                break;
              case SDLK_RIGHT:
                g_current_surface_ = g_keypress_surfaces_[KEY_PRESS_SURFACE_RIGHT];
                break;
              default:
                g_current_surface_ = g_keypress_surfaces_[KEY_PRESS_SURFACE_DEFAULT];
                break;
            }
          }
        }

        if (STRETCH_IMAGE)
        {
          // Apply the image stretched to fit the screen dimensions.
          SDL_Rect stretchRect;
          stretchRect.x = 0;
          stretchRect.y = 0;
          stretchRect.w = SCREEN_WIDTH;
          stretchRect.h = SCREEN_HEIGHT;
          SDL_BlitScaled(g_current_surface_, NULL, g_screen_surface_, &stretchRect);
        }
        // Apply the image using its native dimensions.
        else
        {
          // Apply the image from the hello world surface to the screen surface so that it
          // is ready to be drawn to the screen. This call is drawing the image to the backbuffer.
          SDL_BlitSurface(g_current_surface_, NULL, g_screen_surface_, NULL);
        }

        // Update the surface of our game window now that we have blitted the hello world
        // surface to it. This update is essentially swapping our front and back buffers.
        // Make sure to make all necessary calls to BlitSurface and then only call this
        // update function once per "refresh."
        SDL_UpdateWindowSurface(g_window_);
        
      }
    }
  }

  // Free resources and close SDL.
  close();

  return 0;
}
  

