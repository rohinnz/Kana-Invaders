/** 
 * @file CreditsScene.h
 *
 * @author Rohin Knight
 * @brief Displays the game credits scrolling from bottom of screen.
 */
//============================================================================
#ifndef CreditsScene_H_
#define CreditsScene_H_
//============================================================================
#include "A2DGE/A2DGE.h"
using namespace A2DGE;
#include "common.h"
//============================================================================
class CreditsScene : public Scene
{
public:
	CreditsScene();
	virtual ~CreditsScene();

    virtual void started(string arg);
    virtual void update();
    virtual void render();
    
private:
    Text * m_Title;
    //RCPtr<Text> m_Message;
    
    int m_ResetYPos;
    int m_Counter;

    vector< Text * > m_Lines;
    
};
//============================================================================
#endif /*CreditsScene_H_*/
//============================================================================
