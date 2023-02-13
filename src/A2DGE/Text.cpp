/** 
 * @file Text.cpp
 *
 * @author Rohin Knight
 * @brief Displays True Type Font text
 */
//============================================================================
#include "Text.h"
//============================================================================
namespace A2DGE {
//============================================================================
Text::Text( string text, Color color, TTF_Font * font ) 
    : m_Text( text ),
      m_Color( color ),
      m_Font( font )
{
    if ( text.empty() )
        text = " ";
        
    m_Surface = new Surface( TTF_RenderText_Solid( font, text.c_str(), color.getSDL_Color() ) );
}
//============================================================================
Text::~Text()
{

}
//============================================================================
void Text::paint( Surface * destination )
{
    if ( m_Visible )
        m_Surface->blitSurface( destination, m_XPos, m_YPos );
}
//============================================================================
void Text::setText( string text )
{
    //delete m_Surface;
    m_Surface->setSDL_Surface( TTF_RenderText_Solid( m_Font, text.c_str(), m_Color.getSDL_Color() ) );
    //m_Surface = new Surface( TTF_RenderText_Solid( font, text.c_str(), m_color.getSDL_Color() ) );
}
//============================================================================
void Text::setText( string text, Color color, TTF_Font * font )
{
    if ( text.empty() )
        text = " ";
    
    m_Text = text;
    m_Color = color;
    m_Font = font;
        
    m_Surface->setSDL_Surface( TTF_RenderText_Solid( m_Font, m_Text.c_str(), m_Color.getSDL_Color() ) );
//    setColor( color );
//    setFont( font );
//    setText( text );
}
//============================================================================
void Text::setColor( Color color, bool update )
{
    m_Color = color;
    if ( update )
        m_Surface->setSDL_Surface( TTF_RenderText_Solid( m_Font, m_Text.c_str(), m_Color.getSDL_Color() ) );
}
//============================================================================
void Text::setFont( TTF_Font * font, bool update )
{
    m_Font = font;
    if ( update )
        m_Surface->setSDL_Surface( TTF_RenderText_Solid( m_Font, m_Text.c_str(), m_Color.getSDL_Color() ) );
}
//============================================================================
} /* namespace A2DGE */
//============================================================================
