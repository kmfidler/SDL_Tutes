// Source Includes
#include "texture.hpp"
#include "application.hpp"

// SDL Includes
#include "SDL.h"
#include "SDL_image.h"

// Standard C++ Includes
#include <stdio.h>
#include <string>

///////////////////////////////////////////////////////////////////////////////
Application::Application(int scr_w,
    int scr_h,
    bool viewports) : 
    screen_width_(scr_w), 
    screen_height_(scr_h), 
    use_viewports_(viewports)
{
  // Initialize SDL.
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    // throw an error
  }
  else
  {
    // Create the window.
    g_window_ = SDL_CreateWindow("SDL Tutorial",
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      screen_width_,
      screen_height_,
      SDL_WINDOW_SHOWN);

    if (g_window_ == NULL)
    {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      // throw an error
    }
    else
    {
      g_renderer_ = SDL_CreateRenderer(g_window_, -1, SDL_RENDERER_ACCELERATED);  
      if(g_renderer_ == NULL)      
      {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        // throw error
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
          // throw error 
        }
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
Application::~Application()
{
}

///////////////////////////////////////////////////////////////////////////////
bool Application::load_media()
{
  // Load success flag. Use this method instead of just returning on first failure; this
  // allows us to see all images that fail to load. 
  bool success = true;

  foo_texture_ = new Texture(g_renderer_);
  if(!foo_texture_)
  {
    printf("Failed to create foo_texture_!\n");
    success = false;
  }
  else
  {
    if(!foo_texture_->load_from_file("assets/visuals/hello_world.bmp"))
    {
      printf( "Failed to load foo_texture_ image!\n" );
      success = false;
    }
  }

  bg_texture_ = new Texture(g_renderer_);
  if(!bg_texture_)
  {
    printf("Failed to create bg_texture_!\n");
    success = false;
  }
  else
  {
    if(!bg_texture_->load_from_file( "assets/visuals/texture.png" ))
    {
      printf( "Failed to load bg_texture_ image!\n" );
      success = false;
    }
  }

  return success;
}

///////////////////////////////////////////////////////////////////////////////
void Application::close()
{
  // Free loaded image(s)
  foo_texture_->free();
  bg_texture_->free();

  // Destroy window    
  SDL_DestroyRenderer(g_renderer_);
  SDL_DestroyWindow(g_window_);
  g_window_ = NULL;
  g_renderer_ = NULL;

  // Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}

///////////////////////////////////////////////////////////////////////////////
void Application::execute()
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

    // Set up our main viewport.
    SDL_Rect main_viewport;
    main_viewport.x = 0;
    main_viewport.y = 0;
    main_viewport.w = screen_width_;
    main_viewport.h = screen_height_;

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
      SDL_RenderClear(g_renderer_ );
    
      // Set the main viewport every time we render.
      SDL_RenderSetViewport(g_renderer_, &main_viewport );

      // Render texture to screen.
      bg_texture_->render(screen_width_/2 - bg_texture_->width()/2,
                                              screen_height_/2 - bg_texture_->height()/2);

       // Render our little viewport (menu, minimap, etc) if we're using that feature.
      if(use_viewports_)
      {
        render_viewports();
      }

      // Update screen so we actually see the new image.
      SDL_RenderPresent(g_renderer_);
    } 
  }

  // Free resources and close SDL.
  close();
}

///////////////////////////////////////////////////////////////////////////////
void Application::render_viewports()
{
  // Top left corner viewport.
  SDL_Rect top_left_viewport;

  top_left_viewport.x = 0;
  top_left_viewport.y = 0;
  top_left_viewport.w = foo_texture_->width();
  top_left_viewport.h = foo_texture_->height();
  SDL_RenderSetViewport(g_renderer_, &top_left_viewport );
  
  // Render texture to screen.
  SDL_RenderCopy(g_renderer_, foo_texture_->texture(), NULL, NULL );
}