/** 
 * @file Star.cpp
 *
 * @author Rohin Knight
 * @brief A sprite representing a moving star in the background of a level.
 */
//============================================================================
#include "Star.h"
//============================================================================
Star::Star()
    : Sprite( getSurface(), 1, 1, 0, true, true )
{
    setPosition( 1 + (rand() % (Singleton<Display>::getPtr()->getWidth() - 2)), (rand() % Singleton<Display>::getPtr()->getHeight()) - 10 );
    m_Speed = rand() % 3;
    setFrameIndex( m_Speed );
    m_Counter = 0;
}
//============================================================================
Star::~Star()
{
    
}
//============================================================================
void Star::updatePosition()
{
    ///Display* display = Singleton<Display>::getPtr();
    
    if ( getYPos() > Singleton<Display>::getPtr()->getHeight() ) {
        setPosition( 1 + (rand() % (Singleton<Display>::getPtr()->getWidth() - 2)), 0 - (rand() % 10) );
        m_Speed = rand() % 3;
        setFrameIndex( m_Speed );
        m_Counter = 0;
    }
    else {
        int dy = 0; // set to 0 to prevent compiler warnings
        
        switch ( m_Speed ) {
        case 0:
            dy = (m_Counter % 2 == 0 ? 1 : 0 );
            break;
        case 1:
            dy = (m_Counter % 3 == 0 ? 1 : 0 );
            break;
        case 2:
            dy = (m_Counter % 4 == 0 ? 1 : 0 );
            break;
        }
        
        if ( dy > 0 )
            move( 0, dy );
            
        m_Counter++;
    }
}
//============================================================================
Surface * Star::getSurface()
{
    static Surface* surface =
    	Singleton<GarbageCollector>::getPtr()->addSurface(  // Must use Garbage collector
    		new Surface( "data/gfx/star.png", Color::BLACK )
    	);
 

//    static Surface * surface = new Surface( "data/gfx/star.png", Color::BLACK );
    return surface;
}
//============================================================================
