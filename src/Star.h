/** 
 * @file Star.h
 *
 * @author Rohin Knight
 * @brief A sprite representing a moving star in the background of a level.
 */
//============================================================================
#ifndef Star_H_
#define Star_H_
//============================================================================
#include "A2DGE/A2DGE.h"
using namespace A2DGE;

#include "common.h"
//============================================================================
class Star : public Sprite
{
public:
	Star();
	virtual ~Star();

    void updatePosition();

private:
    int m_Speed;
    int m_Counter;
    
    Surface * getSurface();
    
};
//============================================================================
#endif /*Star_H_*/
//============================================================================
