/** 
 * @file Missile.cpp
 *
 * @author Rohin Knight
 * @brief A sprite object which is fired from the player's ship
 */
//============================================================================
#include "Missile.h"
//============================================================================
Missile::Missile()
    : Sprite( new Surface( "data/gfx/missile.png", Color::BLACK ), 35, 35, 40, false ),
      m_Destroyed( false )
{
    createFrameSequence( "destroy", 2, 11 );
    createFrameSequence( "normal", 0, 1, true );
    
    addCollisionRectangle( 14, 0, 7, 30 );
}
//============================================================================
Missile::~Missile()
{

}
//============================================================================
void Missile::setDestroyed( bool destroyed )
{ 
    m_Destroyed = destroyed; 
    
    if ( m_Destroyed )
        setFrameSequence( "destroy" );
    else
        setFrameSequence( "normal" );
}
//============================================================================
void Missile::updateRomanji()
{ 
    if ( Singleton<Input>::getPtr()->keyPressed( SDLK_BACKSPACE ) && ! m_Romanji.empty() ) {
            m_Romanji.erase( m_Romanji.size() - 1 );
    }
    else if ( m_Romanji.size() < 3 && Singleton<Input>::getPtr()->newKeyPressed() ) {
        Uint16 key = Singleton<Input>::getPtr()->getLastKey();
        
        if ( key >= 'a' && key <= 'z' )
            m_Romanji += key;
        else if ( key >= 'A' && key <= 'Z' )
            m_Romanji += tolower( key );
    }
}
//============================================================================
void Missile::updateAnimation()
{
    if ( m_Destroyed && isLastFrame() ) {
        setVisible( false );
        setDestroyed( false );
    }
    else {
        updateFrame();
    }
}
//============================================================================
void Missile::updatePosition()
{
    if ( ! m_Destroyed ) {
        if ( getYPos() > (0 - getHeight()) )
            move( 0, -10 );
        else
            reset();
    }
    else
        move( 0, -1 );
}
//============================================================================
void Missile::reset()
{
    m_Destroyed = false;
    setVisible( false );
    setFrameSequence( "normal" );
    clearRomanji();
}
//============================================================================
