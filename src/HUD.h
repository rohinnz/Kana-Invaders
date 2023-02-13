/** 
 * @file HUD.h
 *
 * @author Rohin Knight
 * @brief Displays players HUD at top of screen during a level. Displays the
 * current level, wave, lives, and score.
 */
//============================================================================
#ifndef HUD_H_
#define HUD_H_
//============================================================================
#include "A2DGE/A2DGE.h"
using namespace A2DGE;
//============================================================================
class HUD
{
public:
	HUD();
	virtual ~HUD();
    
    void update( int level, int wave, int lives, int points );
    void render();
	
private:
    Text * m_Text;
};
//============================================================================
#endif /*HUD_H_*/
//============================================================================

