#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

// SDL Includes
#include "SDL.h"
#include "SDL_image.h"

// Standard C++ Includes
#include <stdio.h>
#include <string>

// Texture wrapper class
class Texture
{
  public:
    /**************************************************************************************
    * ctor
    **************************************************************************************/
    Texture(SDL_Renderer* renderer);

    /**************************************************************************************
    * dtor
    **************************************************************************************/
    ~Texture();

    /**************************************************************************************
    * Function: load_from_file()
    * Description: Handles loading the desired image into memory as a surface 
    *                         and creating a texture from it. 
    * Args: std::string path to the image being loaded into memory.
    * Return: Boolean success indicator.
    **************************************************************************************/
    bool load_from_file(std::string path);

    /**************************************************************************************
    * Function: free()
    * Description:Deallocates texture.
    * Args: None.
    * Return: None.
    **************************************************************************************/
    void free();

    /**************************************************************************************
    * Function: render()
    * Description: Renders the texture at the given point.
    * Args: x and y coordinates indicating where on the screen to render the texture.
    * Return: None
    **************************************************************************************/
    void render( int x, int y );

    /**************************************************************************************
    * Function: width()
    * Description: Returns the width of the texture.
    * Args: None.
    * Return: Integer width of the texture.
    **************************************************************************************/
    // Gets image dimensions
    int width();

    /**************************************************************************************
    * Function: height()
    * Description: Returns the height of the texture.
    * Args: None.
    * Return: Integer height of the texture.
    **************************************************************************************/
    int height();

    /**************************************************************************************
    * Function: texture()
    * Description: Returns the raw SDL texture being used.
    * Args: None.
    * Return: Pointer to an SDL_Texture.
    **************************************************************************************/
    SDL_Texture* texture();

  private:
    // The actual hardware texture.
    SDL_Texture* texture_ = NULL;

    //The renderer being used to draw the texture.
    SDL_Renderer* renderer_ = NULL;

    // Image dimensions.
    int width_ = 0;
    int height_ = 0;
};

#endif