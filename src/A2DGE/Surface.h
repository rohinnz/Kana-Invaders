/** 
 * @file Surface.h
 *
 * @author Rohin Knight
 * @brief Wrapper for SDL surfaces which hold graphics and can be rendered
 * onto each other.
 */
//============================================================================
#ifndef Surface_H_
#define Surface_H_
//============================================================================
#include "Globals.h"
#include "Color.h"
//============================================================================
namespace A2DGE {
//============================================================================
class Surface
{
public:
	Surface( SDL_Surface * surface );
	Surface( string filename, Color colorKey = DEFAULT_COLOR_KEY );
	virtual ~Surface();

	void setSDL_Surface( SDL_Surface * surface ) { m_Surface = surface; }
	SDL_Surface * getSDL_Surface() { return m_Surface; }
	int getWidth() { return m_Surface->w; }
	int getHeight() { return m_Surface->h; }
    void blitSurface( Surface * destination, int x, int y, SDL_Rect* clip = NULL );

private:
	SDL_Surface * m_Surface;
	static Color DEFAULT_COLOR_KEY;
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*Surface_H_*/
//============================================================================
