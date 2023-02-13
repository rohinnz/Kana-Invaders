/** 
 * @file Missile.h
 *
 * @author Rohin Knight
 * @brief A sprite object which is fired from the player's ship
 */
//============================================================================
#ifndef Missile_H_
#define Missile_H_
//============================================================================
#include "A2DGE/A2DGE.h"
using namespace A2DGE;

#include "common.h"
//============================================================================
class Missile : public Sprite
{
public:
	Missile();
	virtual ~Missile();
    
    bool isDestroyed() { return m_Destroyed; }
    void setDestroyed( bool destroyed );
    
    void updateRomanji();
    void clearRomanji() { m_Romanji = ""; }
    string getRomanji() { return m_Romanji; }
    
    bool isActive() { return ! m_Destroyed && isVisible(); }
    
    void updateAnimation();
    void updatePosition();
    void reset();
    
private:
    string m_Romanji;
    bool m_Destroyed;
    bool m_Active;
};
//============================================================================
#endif /*Missile_H_*/
//============================================================================
