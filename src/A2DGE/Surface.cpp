/** 
 * @file Surface.cpp
 *
 * @author Rohin Knight
 * @brief Wrapper for SDL surfaces which hold graphics and can be rendered
 * onto each other.
 */
//============================================================================
#include "Surface.h"
//============================================================================
namespace A2DGE {
//============================================================================
Color Surface::DEFAULT_COLOR_KEY( 0, 0, 0 );
//============================================================================
Surface::Surface( SDL_Surface * surface )
{
	m_Surface = surface;
}
//============================================================================
Surface::Surface( string filename, Color colorKey )
	: m_Surface( NULL )
{	
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //Load the image
    if ( (loadedImage = IMG_Load( filename.c_str() )) == NULL ) {
        string error( "Error: SDL Could not load image \'" );
        error += filename;
        error += "\': ";
        error += SDL_GetError();
        throw error;
	}
        
    //Create an optimized surface
    if ( (m_Surface = SDL_DisplayFormat( loadedImage )) == NULL ) {
        string error( "Error: SDL Could not create optimized surface for image" );
        error += filename;
        error += ": ";
        error += SDL_GetError();
        throw error;
    }
    
    //Map the color key
    //Uint32 colorkey = SDL_MapRGB( m_surface->format, 0, 0xFF, 0xFF );
    SDL_SetColorKey( m_Surface, SDL_SRCCOLORKEY,
        SDL_MapRGB( m_Surface->format, colorKey.getRed(), colorKey.getGreen(), colorKey.getBlue() ) );
        
    //Free the old surface
	SDL_FreeSurface( loadedImage );
}
//============================================================================
Surface::~Surface()
{
	if ( m_Surface != NULL )
		SDL_FreeSurface( m_Surface );
}
//============================================================================
void Surface::blitSurface( Surface * destination, int x, int y, SDL_Rect * clip )
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    
    SDL_BlitSurface( m_Surface, clip, destination->getSDL_Surface(), &offset );
}
//============================================================================
} /* namespace A2DGE */
//============================================================================
