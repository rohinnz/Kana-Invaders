/** 
 * @file Color.cpp
 *
 * @author Rohin Knight
 * @brief Represents an object with Red, Green, and Blue color variables.
 * Includes constants for common color mixes.
 */
//============================================================================
#include "Color.h"
//============================================================================
namespace A2DGE {
//============================================================================
const Color Color::WHITE( 255, 255, 255 );
const Color Color::BLACK( 0, 0, 0 );
const Color Color::RED( 255, 0, 0 );
const Color Color::GREEN( 0, 255, 0 );
const Color Color::BLUE( 0, 0, 255 );
const Color Color::CYAN( 0, 255, 255 );
const Color Color::MAGENTA( 255, 0, 255 );
const Color Color::YELLOW( 255, 255, 0 );
//============================================================================
Color::Color( Uint8 r, Uint8 g, Uint8 b )
{
    setColor( r, g, b );
}
//============================================================================
Color::~Color()
{

}
//============================================================================
void Color::setRed( Uint8 r )
{    
    m_Color.r = r;
}
//============================================================================
void Color::setGreen( Uint8 g )
{    
    m_Color.g = g;
}
//============================================================================
void Color::setBlue( Uint8 b )
{    
    m_Color.b = b;
}
//============================================================================
void Color::setColor( Uint8 r, Uint8 g, Uint8 b )
{
    setRed( r );
    setGreen( g );
    setBlue( b );
}
//============================================================================
} /* namespace A2DGE */
//============================================================================
