/** 
 * @file Color.h
 *
 * @author Rohin Knight
 * @brief Represents an object with Red, Green, and Blue color variables.
 * Includes constants for common color mixes.
 */
//============================================================================
/*

  TODO:
  - add assignment and copy constructors
  - add assignment operator
  
*/
//============================================================================
#ifndef Color_H_
#define Color_H_
//============================================================================
#include "Globals.h"
//============================================================================
namespace A2DGE {
//============================================================================
class Color
{
public:
	static const Color WHITE;
	static const Color BLACK;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color CYAN;
    static const Color MAGENTA;
    static const Color YELLOW;
    static const Color DARK_GRAY;
    static const Color GRAY;
    static const Color LIGHT_GRAY;
    static const Color ORANGE;
    static const Color PINK;
    
	Color( Uint8 r, Uint8 g, Uint8 b );
	virtual ~Color();

    Uint8 getRed() { return m_Color.r; }
    Uint8 getGreen() { return m_Color.g; }
    Uint8 getBlue() { return m_Color.r; }

    void setRed( Uint8 r );
    void setGreen( Uint8 g );
    void setBlue( Uint8 b );
    void setColor( Uint8 r, Uint8 g, Uint8 b );
    SDL_Color getSDL_Color() { return m_Color; }

private:
	SDL_Color m_Color;
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*Color_H_*/
//============================================================================
