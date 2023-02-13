/** 
 * @file Menu.cpp
 *
 * @author Rohin Knight
 * @brief Inherited by scene classes with common functionality.
 */
//============================================================================
#include "Menu.h"
//============================================================================
Menu::Menu()
{

}
//============================================================================
Menu::~Menu()
{

}
//============================================================================
void Menu::highlightText( Text* text, bool highlight )
{
    static TTF_Font * fontSelected = Singleton<FontManager>::getPtr()->getFont( "NormalSelected" );
    static TTF_Font * fontNormal = Singleton<FontManager>::getPtr()->getFont( "NormalText" );
    
    
    if ( highlight ) {
        
        
        text->setFont( fontSelected );
        text->setColor( Color(224, 237, 52) );
        
        text->setPosition(
            text->getXPos() - 2,
            text->getYPos() - 2
        );
    }
    else {
        text->setFont( fontNormal );
        text->setColor( Color(111, 217, 113) );
        
        text->setPosition(
            text->getXPos() + 2,
            text->getYPos() + 2
        );
    }  

}
//============================================================================    
void Menu::playChangedSound()
{
    Singleton<SoundManager>::getPtr()->playSound( "pop" );    
}
//============================================================================    
