/** 
 * @file HUD.cpp
 *
 * @author Rohin Knight
 * @brief Displays players HUD at top of screen during a level. Displays the
 * current level, wave, lives, and score.
 */
//============================================================================
#include "HUD.h"
//============================================================================
HUD::HUD()
{
    m_Text = new Text( "", Color(111, 217, 113), Singleton<FontManager>::getPtr()->getFont( "HUD" ) );
    m_Text->setPosition( 10, 10 );
}
//============================================================================
HUD::~HUD()
{
    
}
//============================================================================
void HUD::update( int level, int wave, int lives, int points )
{
    //TODO: Calculate where each variable should be displayed. Current method is dirty and needs to be changed whenever the screen width is changed.
    
    char str[500];
    sprintf( str, "Level: %d                  Wave: %d                      Lives: %d                      Points: %d", level, wave, lives, points );
    m_Text->setText( str );
}
//============================================================================
void HUD::render()
{
    m_Text->paint( Singleton<Display>::getPtr()->getSurface() );
}
//============================================================================

