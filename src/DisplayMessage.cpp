/** 
 * @file DisplayMessage.cpp
 *
 * @author Rohin Knight
 * @brief Displays a centered, two-line message during a level.
 */
//============================================================================
#include "DisplayMessage.h"
//============================================================================
DisplayMessage::DisplayMessage()
    : displayTime( 2500 )
{
    m_Message = new Text( "", Color(111, 217, 113), Singleton<FontManager>::getPtr()->getFont( "NormalText" ) );
    m_SubMessage =  new Text( "", Color(111, 217, 113), Singleton<FontManager>::getPtr()->getFont( "NormalText" ) );
}
//============================================================================
DisplayMessage::~DisplayMessage()
{

}
//============================================================================
void DisplayMessage::setMessage( string message, string subMessage, bool resetTimer )
{
    m_Message->setText( message );
    m_SubMessage->setText( subMessage );
    
    Display* d = Singleton<Display>::getPtr();
    m_Message->setPosition( (d->getWidth() / 2) - (m_Message->getWidth() / 2),
                            (d->getHeight() / 2) - m_Message->getHeight() );
    m_SubMessage->setPosition( (d->getWidth() / 2) - (m_SubMessage->getWidth() / 2),
                               (d->getHeight() / 2) + 10 );
    
    if ( resetTimer )
        displayTime.reset();
}
//============================================================================
void DisplayMessage::render()
{
    m_Message->paint( Singleton<Display>::getPtr()->getSurface() );
    m_SubMessage->paint( Singleton<Display>::getPtr()->getSurface() );
}
//============================================================================
bool DisplayMessage::isDisplayTimeUp()
{
    return displayTime.intervalReached();
}
//============================================================================
