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
const bool VIEWPORTS = true;

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

//The window renderer
SDL_Renderer* g_renderer_ = NULL;

//Current displayed texture
SDL_Texture* g_texture_ = NULL;

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
      g_renderer_ = SDL_CreateRenderer(g_window_, -1, SDL_RENDERER_ACCELERATED);  
      if(g_renderer_ == NULL)      
      {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
      }
      else
      {
        // Initialize renderer color.
        SDL_SetRenderDrawColor(g_renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
      
        // Initialize SDL-Image Library for PNG loading.
        int img_flags = IMG_INIT_PNG;
        if (!(IMG_Init(img_flags) & img_flags))
        {
          printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
          return false;
        }
      }
    }
  }
  return true;
}

/**************************************************************************************
* Function: render_viewports()
* Description: Splits up our display window by creating multiple viewports
*                          that can be rendered to separately. Can be used to overlay
*                          extra screens over our main screen, e.g. minimaps, menus, etc.
* Args: none
* Return: none
**************************************************************************************/
void render_viewports()
{
  // Background viewport. Comment out any of the other viewports below in
  // order to see how viewports can be layered on backgrounds like this one.
  SDL_Rect bg_viewport;
  bg_viewport.x = 0;
  bg_viewport.y = 0;
  bg_viewport.w = SCREEN_WIDTH;
  bg_viewport.h = SCREEN_HEIGHT;
  SDL_RenderSetViewport( g_renderer_, &bg_viewport );
  
  // Render texture to screen.
  SDL_RenderCopy( g_renderer_, g_texture_, NULL, NULL );

  // Top left corner viewport.
  SDL_Rect top_left_viewport;
  top_left_viewport.x = 0;
  top_left_viewport.y = 0;
  top_left_viewport.w = SCREEN_WIDTH / 2;
  top_left_viewport.h = SCREEN_HEIGHT / 2;
  SDL_RenderSetViewport( g_renderer_, &top_left_viewport );
  
  // Render texture to screen.
  SDL_RenderCopy( g_renderer_, g_texture_, NULL, NULL );

  // Top right viewport.
  SDL_Rect top_right_viewport;
  top_right_viewport.x = SCREEN_WIDTH / 2;
  top_right_viewport.y = 0;
  top_right_viewport.w = SCREEN_WIDTH / 2;
  top_right_viewport.h = SCREEN_HEIGHT / 2;
  SDL_RenderSetViewport( g_renderer_, &top_right_viewport );
  
  // Render texture to screen.
  SDL_RenderCopy( g_renderer_, g_texture_, NULL, NULL );

  // Bottom viewport.
  SDL_Rect bottom_viewport;
  bottom_viewport.x = 0;
  bottom_viewport.y = SCREEN_HEIGHT / 2;
  bottom_viewport.w = SCREEN_WIDTH;
  bottom_viewport.h = SCREEN_HEIGHT / 2;
  SDL_RenderSetViewport( g_renderer_, &bottom_viewport );
  
  // Render texture to screen.
  SDL_RenderCopy( g_renderer_, g_texture_, NULL, NULL );
}

/**************************************************************************************
* Function: load_surface()
* Description: Called by load_media(), this handles actually loading the desired image
*              into memory, creating a texture from it, and returning a pointer to it. 
* Args: std::string path to the image being loaded into memory.
* Return: A pointer to the SDL Texture creating from the image that was loaded.
**************************************************************************************/
SDL_Texture* load_texture(std::string path)
{
  // The texture we'll be returning.
  SDL_Texture* new_texture = NULL;

  //Load image at specified path
  SDL_Surface* loaded_surface = IMG_Load(path.c_str());
  if (loaded_surface == NULL)
  {
    printf("Unable to load image %s! SDL_Image Error: %s\n", path.c_str(), IMG_GetError());
  }
  else
  {
    // Create texture from surface.
    new_texture = SDL_CreateTextureFromSurface(g_renderer_, loaded_surface);
    if (new_texture == NULL)
    {
      printf("Unable to create texture ffrom %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    // We need to free the loaded surface since the optimized one is actually a copy.
    SDL_FreeSurface(loaded_surface);
  }

  return new_texture;
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

  //Load PNG texture
    g_texture_ = load_texture( "assets/visuals/texture.png" );
    if( g_texture_ == NULL )
    {
        printf( "Failed to load texture image!\n" );
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
  // Free loaded image
    SDL_DestroyTexture( g_texture_);
    g_texture_ = NULL;

    // Destroy window    
    SDL_DestroyRenderer( g_renderer_);
    SDL_DestroyWindow( g_window_);
    g_window_ = NULL;
    g_renderer_ = NULL;

    // Quit SDL subsystems
    IMG_Quit();
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
        }

        // Clear screen and fill it with the color that was last set with SDL_SetRenderDrawColor.
        SDL_RenderClear( g_renderer_ );

        // Split up the screen using viewports, if we're using that feature.
        if(VIEWPORTS)
        {
          render_viewports();
        }
        else
        {
          // Render texture to screen.
          SDL_RenderCopy( g_renderer_, g_texture_, NULL, NULL );
        }

        // Update screen so we actually see the new image.
        SDL_RenderPresent( g_renderer_);
      }
    }
  }

  // Free resources and close SDL.
  close();

  return 0;
}
  

