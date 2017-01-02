#ifndef _APPLICATION_HPP_
#define _APPLICATION_HPP_

// Source Includes
#include "texture.hpp"

// SDL Includes
#include "SDL.h"
#include "SDL_image.h"

// Standard C++ Includes
#include <stdio.h>
#include <string>

// Class to represent out actual game/app/whatev
class Application
{
  public:
    /**************************************************************************************
    * ctor
    **************************************************************************************/
    Application(int scr_w,
    int scr_h,
    bool viewports);

    /**************************************************************************************
    * dtor
    **************************************************************************************/
    ~Application();

    /**************************************************************************************
    * Function: load_media()
    * Description: Loads media so it can be used some point in the game.
    * Args: none for now, but should probably take args later that can tell it
    *             what to load e.g. if we want to load assets by level.
    * Return: bool indicating success/fail
    **************************************************************************************/
    bool load_media();

    /**************************************************************************************
    * Function: close()
    * Description: Frees loaded media and shuts down SDL.
    * Args: none
    * Return: none
    **************************************************************************************/
    void close();

    /**************************************************************************************
    * Function: execute()
    * Description: The main run loop for the application.
    * Args: none
    * Return: none
    **************************************************************************************/
    void execute();

    /**************************************************************************************
    * Function: render_viewports()
    * Description: Splits up our display window by creating multiple viewports
    *                          that can be rendered to separately. Can be used to overlay
    *                          extra screens over our main screen, e.g. minimaps, menus, etc.
    * Args: none
    * Return: none
    **************************************************************************************/
    //void render_viewports();

private:

// Screen dimensions.
int screen_width_ = 640;
int screen_height_ = 480;

// Display using viewports?
const bool use_viewports_ = false;  

// The window we'll be rendering to.
SDL_Window* g_window_ = NULL;

// The window renderer
SDL_Renderer* g_renderer_ = NULL;

// Scene textures
Texture* foo_texture_ = NULL;
Texture* bg_texture_ = NULL;

};

#endif