/** 
 * @file PlayerShip.cpp
 *
 * @author Rohin Knight
 * @brief A sprite object representing the player's ship
 */
//============================================================================
#include "PlayerShip.h"
//============================================================================
PlayerShip::PlayerShip()
    : Sprite( new Surface( "data/gfx/playership.png", Color::BLACK ), 68, 64, 40, false ),
    m_DestroyTimer( 2000 ),
    m_FlashingTimer( 3000 )
{
    addCollisionRectangle( 32, 1, 4, 53 );
    addCollisionRectangle( 30, 5, 8, 49 );
    addCollisionRectangle( 28, 9, 12, 45 );
    addCollisionRectangle( 26, 13, 16, 41 );
    addCollisionRectangle( 21, 22, 26, 32 );
    addCollisionRectangle( 17, 30, 34, 28 );
    addCollisionRectangle( 7, 49, 14, 9 );
    addCollisionRectangle( 47, 49, 14, 9 );
    addCollisionRectangle( 2, 57, 10, 6 );
    addCollisionRectangle( 56, 57, 10, 6 );
    
    createFrameSequence( "normal", 0, 1 );
    createFrameSequence( "destroy", 2, 11 );
    createFrameSequence( "level30", 12, 13 );
    
    vector<int> * flashingSequence = new vector<int>;
    flashingSequence->push_back( 0 );
    flashingSequence->push_back( 1 );
    flashingSequence->push_back( 11 );
    flashingSequence->push_back( 11 );
        
    addFrameSequence( "flashing", flashingSequence );
    
    vector<int> * flashingSequence2 = new vector<int>;
    flashingSequence2->push_back( 12 );
    flashingSequence2->push_back( 13 );
    flashingSequence2->push_back( 11 );
    flashingSequence2->push_back( 11 );
    
    addFrameSequence( "flashing2", flashingSequence2 );
    
    m_Destroyed = false;
    m_IsFlashing = false;
}
//============================================================================
PlayerShip::~PlayerShip()
{

}
//============================================================================
void PlayerShip::updatePosition()
{
    static const int TOP_BOUNDARY = 0;
    static const int BOTTOM_BOUNDARY = Singleton<Display>::getPtr()->getHeight() - getHeight();
    static const int LEFT_BOUNDARY = 0;
    static const int RIGHT_BOUNDARY = Singleton<Display>::getPtr()->getWidth() - getWidth();
    
    if ( Singleton<Input>::getPtr()->keyDown( SDLK_UP ) ) {        
        move( 0, -5 );
        if ( getYPos() < TOP_BOUNDARY )
            setYPos( TOP_BOUNDARY );
    }
    if ( Singleton<Input>::getPtr()->keyDown( SDLK_DOWN ) ) {
        move( 0, 3 );
        if ( getYPos() > BOTTOM_BOUNDARY )
            setYPos( BOTTOM_BOUNDARY );
    }
    if ( Singleton<Input>::getPtr()->keyDown( SDLK_LEFT ) ) {
        move( -6, 0 );
        if ( getXPos() < LEFT_BOUNDARY )
            setXPos( LEFT_BOUNDARY );
    }
    if ( Singleton<Input>::getPtr()->keyDown( SDLK_RIGHT ) ) {
        move( 6, 0 );
        if ( getXPos() > RIGHT_BOUNDARY )
            setXPos( RIGHT_BOUNDARY );
    }
}
//============================================================================
void PlayerShip::updateFlashing()
{
    if ( isFlashing() && m_FlashingTimer.intervalReached() ) {
         
        if (m_CurrentLevel == 30)
                       setFrameSequence( "level30" );
        else
            setFrameSequence( "normal" );
            
        m_IsFlashing = false;
    }
}
//============================================================================
void PlayerShip::reset( int level )
{
    m_CurrentLevel = level;
     
    setPosition( Singleton<Display>::getPtr()->getWidth() / 2,
                 Singleton<Display>::getPtr()->getHeight() - getHeight() - 20 );
                 
    if ( m_CurrentLevel == 30 )
        setFrameSequence( "level30" );
    else
        setFrameSequence( "normal" );
        
    m_Destroyed = false;
}    
//============================================================================
void PlayerShip::destroy()
{
    Singleton<SoundManager>::getPtr()->playSound( "explosion" );
        
    m_Destroyed = true;
    setFrameSequence( "destroy" );
    m_DestroyTimer.reset();
}
//============================================================================
bool PlayerShip::destroyTimerFinished()
{
    return m_DestroyTimer.intervalReached();
}
//============================================================================
void PlayerShip::setFlashing( bool flashing )
{
    if ( m_CurrentLevel == 30 )
        setFrameSequence( "flashing2" );
    else
        setFrameSequence( "flashing" );
    
    m_IsFlashing = true;
    m_FlashingTimer.reset();
}
//============================================================================
bool PlayerShip::isFlashing()
{
    return m_IsFlashing; 
}
//============================================================================
