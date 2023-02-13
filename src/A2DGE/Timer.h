/**
 * @file Timer.h
 *
 * @author Rohin Knight
 * @brief Used to time intervals. Still under construction.
 */
//============================================================================
/*

  TODO: 
  - Add code to handle game pauses!

*/
//============================================================================
#ifndef Timer_H_
#define Timer_H_
//============================================================================
#include "Globals.h"
//============================================================================
namespace A2DGE {
//============================================================================
class Timer   //TODO: Add code to handle game pauses!
{
public:
	Timer( unsigned long interval );
	virtual ~Timer();

    //static void pauseAllTimers() { paused = true; }
    //static void unpauseAllTimers() {  paused = false; }
    
    //void unpause();
    void setInterval( unsigned long interval ) { m_Interval = interval; }
    bool intervalReached();
    void reset() { m_TimerReset = true; }
	
private:
    //static bool paused;
    bool m_TimerReset;
    
    unsigned long m_Interval;
    unsigned long m_PrevTicks;
    unsigned long m_PausedTicks;
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*Timer_H_*/
//============================================================================
