#include "texture.hpp"

///////////////////////////////////////////////////////////////////////////////
Texture::Texture(SDL_Renderer* renderer) : renderer_(renderer)
{  
  //renderer_ = renderer;
}

///////////////////////////////////////////////////////////////////////////////
Texture:: ~Texture()
{
  // Deallocate memory used by texture.
  free();
}

///////////////////////////////////////////////////////////////////////////////
bool Texture::load_from_file(std::string path)
{
  // Free exitsting texture if one exists.
  free();

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
    // Color key the image to make its background transparent.
    SDL_SetColorKey( loaded_surface, SDL_TRUE, SDL_MapRGB( loaded_surface->format, 0, 0xFF, 0xFF ) );

    // Create texture from surface.
    new_texture = SDL_CreateTextureFromSurface(renderer_, loaded_surface);
    if (new_texture == NULL)
    {
      printf("Unable to create texture ffrom %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    else
    {
      width_ = loaded_surface->w;
      height_ = loaded_surface->h;
    }

    // We need to free the loaded surface since the optimized one is actually a copy.
    SDL_FreeSurface(loaded_surface);
  }

  // Set member texture to the one we just created, and return true if the texture isn't null.
  texture_ = new_texture;
  return texture_ != NULL;
}

///////////////////////////////////////////////////////////////////////////////
void Texture::free()
{
  // Free the texture if it exists.
  if(texture_ != NULL)
  {
    SDL_DestroyTexture(texture_);
    texture_ = NULL;
    renderer_ = NULL;
    width_ = 0;
    height_ = 0;
  }
}

///////////////////////////////////////////////////////////////////////////////
void Texture::render(int x, int y)
{
  // Set the rendering location and render to the screen.
  SDL_Rect render_quad{x, y, width_, height_};
  SDL_RenderCopy(renderer_, texture_, NULL, &render_quad);
}

///////////////////////////////////////////////////////////////////////////////
int Texture::width()
{
  return width_;
}

///////////////////////////////////////////////////////////////////////////////
int Texture::height()
{
  return height_;
}

///////////////////////////////////////////////////////////////////////////////
SDL_Texture* Texture::texture()
{
  return texture_;
}