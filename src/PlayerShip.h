/** 
 * @file PlayerShip.cpp
 *
 * @author Rohin Knight
 * @brief A sprite object representing the player's ship
 */
//============================================================================
#ifndef PlayerShip_H_
#define PlayerShip_H_
//============================================================================
#include "A2DGE/A2DGE.h"
using namespace A2DGE;

#include "common.h"
//============================================================================
class PlayerShip : public Sprite
{
public:
	PlayerShip();
	virtual ~PlayerShip();

    //void update();
    //void resetPosition();
    void reset( int level );
    
    void updatePosition();
    void updateFlashing();
    
    //void setToFlashing() { m_IsFlashing = true; }
    //bool isFlashing() { return m_IsFlashing; }
    
    void destroy();
    bool destroyTimerFinished();
    
    bool isDestroyed() { return m_Destroyed; }
    
    void setFlashing( bool flashing );
    bool isFlashing();
    
private:
    bool m_Destroyed;
    bool m_IsFlashing;
    int m_CurrentLevel;
    
    //static RCPtr<Surface> PlayerShip::getSurface();
    Timer m_DestroyTimer;
    Timer m_FlashingTimer;
};
//============================================================================
#endif /*PlayerShip_H_*/
//============================================================================
