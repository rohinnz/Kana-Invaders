/** 
 * @file Display.cpp
 *
 * @author Rohin Knight
 * @brief Holds the primary surface for rendering graphics.
 */
//============================================================================
#include "Display.h"
//============================================================================
namespace A2DGE {
//============================================================================
const int Display::DEFAULT_WIDTH = 640;
const int Display::DEFAULT_HEIGHT = 480;
const int Display::DEFAULT_BPP = 0;
const Uint32 Display::DEFAULT_FLAGS = SDL_SWSURFACE;
//============================================================================
Display::Display()
{

}
//============================================================================
Display::~Display()
{

}
//============================================================================
void Display::initialize( int width, int height, int bpp, Uint32 flags )
{
	/* WHEN SCREEN_BPP IS SET TO 0 IT IS TREATED AS THE CURRENT DISPLAY'S BITS PER PIXEL
	 * 
	 * ------------------
     * VIDEO FLAG OPTIONS
     * ------------------
     * SDL_SWSURFACE   	Create the video surface in system memory
	 * SDL_HWSURFACE 	Create the video surface in video memory
	 * SDL_ASYNCBLIT 	Enables the use of asynchronous to the display surface. This will usually slow down blitting on single CPU machines, but may provide a speed increase on SMP systems.
	 * SDL_ANYFORMAT 	Normally, if a video surface of the requested depth ( bpp ) is not available, SDL will emulate one with a shadow surface. Passing SDL_ANYFORMAT prevents this and causes SDL to use the video surface, regardless of its depth.
	 * SDL_HWPALETTE 	Give SDL exclusive palette access. Without this flag you may not always get the the colors you request with SDL_SetColors .
	 * SDL_DOUBLEBUF 	Enable double buffering; only valid with SDL_HWSURFACE. Calling SDL_Flip will flip the buffers and update the screen. If double buffering could not be enabled then SDL_Flip will just perform a SDL_UpdateRect on the entire screen.
	 * SDL_FULLSCREEN 	SDL will attempt to use a fullscreen mode
	 * SDL_OPENGL 	Create an OpenGL rendering context. You should have previously set OpenGL video attributes with SDL_GL_SetAttribute .
	 * SDL_OPENGLBLIT 	Create an OpenGL rendering context, like above, but allow normal blitting operations.
	 * SDL_RESIZABLE 	Create a resizable window. When the window is resized by the user a SDL_VIDEORESIZE event is generated and SDL_SetVideoMode can be called again with the new size.
	 * SDL_NOFRAME 	If possible, SDL_NOFRAME causes SDL to create a window with no title bar or frame decoration. Fullscreen modes automatically have this flag set.
     */ 
    SDL_Surface * screen;

    if ( (screen = SDL_SetVideoMode( width, height, bpp, flags )) == NULL ) {
        string error( "SDL Could not create Video Surface." );
        error += SDL_GetError();
        throw error;
    }
    
    m_Width = width;
    m_Height = height;
    
    m_Screen = new Surface( screen );
}
//============================================================================
void Display::shutdown()
{
    delete m_Screen;
}
//============================================================================
void Display::setWindowCaption( string caption )
{
    SDL_WM_SetCaption( caption.c_str(), NULL );  // second argument is for the window icon.
}
//============================================================================
void Display::clearSurface( Uint32 color )
{
	SDL_FillRect( m_Screen->getSDL_Surface(), NULL, color ) ;
}
//============================================================================
void Display::swapBuffers()
{
	// Update the screen using double buffering
	if( SDL_Flip( m_Screen->getSDL_Surface() ) == -1 )
	{
		string error( "void Display::swapBuffers()\n"
                      "SDL Failed to render: " );
		error += SDL_GetError();
		throw error;
	}
}
//============================================================================
} /* namespace A2DGE */
//============================================================================
