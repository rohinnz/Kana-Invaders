/** 
 * @file TempLevelMsg.cpp
 *
 * @author Rohin Knight
 * @brief A tempory message used to display an instant point win/lose message.
 */
//============================================================================
#include "TempLevelMsg.h"
//============================================================================
TempLevelMsg::TempLevelMsg( string text, Color color, TTF_Font * font )
	: Text( text, color, font )
{
    m_Timeout = 50;
}
//============================================================================
TempLevelMsg::~TempLevelMsg()
{

}
//============================================================================
void TempLevelMsg::update()
{
	if ( --m_Timeout == 0 )
		setVisible( false );
	else
		move( 0, -1 );
}
//============================================================================
