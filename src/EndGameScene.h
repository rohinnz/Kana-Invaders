/** 
 * @file EndGameScene.cpp
 *
 * @author Rohin Knight
 * @brief Displays end game message scrolling from bottom of screen.
 */
//============================================================================
#ifndef EndGameScene_H_
#define EndGameScene_H_
//============================================================================
#include "A2DGE/A2DGE.h"
using namespace A2DGE;

#include "common.h"
#include "Menu.h"
//============================================================================
class EndGameScene : public Scene, public Menu
{
public:
	EndGameScene();
	virtual ~EndGameScene();

    virtual void started(string args);
    virtual void update();
    virtual void render();
        
private:
    Text * m_Title;
    
    int m_ResetYPos;
    int m_Counter;
    
    vector< Text * > m_Lines;

};
//============================================================================
#endif /*EndGameScene_H_*/
//============================================================================

