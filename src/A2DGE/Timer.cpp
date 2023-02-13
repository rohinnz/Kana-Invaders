/** 
 * @file Timer.cpp
 *
 * @author Rohin Knight
 * @brief Used to time intervals. Still under construction.
 */
//============================================================================
#include "Timer.h"
//============================================================================
namespace A2DGE {
//============================================================================
Timer::Timer( unsigned long interval )
    : m_TimerReset( true ),
      m_Interval( interval ),
      m_PrevTicks( 0 )
{

}
//============================================================================
Timer::~Timer()
{

}
//============================================================================
bool Timer::intervalReached()
{
    unsigned long newTicks = SDL_GetTicks();
    
    if ( m_TimerReset ) {
        m_PrevTicks = newTicks;
        m_TimerReset = false;
    }
    
    if ( newTicks - m_PrevTicks > m_Interval ) {
        m_PrevTicks = newTicks;
        return true;
    } 
    else
        return false;
}
//============================================================================
} /* namespace A2DGE */
//============================================================================

