/** 
 * @file InstructionScene.h
 *
 * @author Rohin Knight
 * @brief Displays instruction text on how to play the game.
 */
//============================================================================
#ifndef InstructionsScene_H_
#define InstructionsScene_H_
//============================================================================
#include "A2DGE/A2DGE.h"
using namespace A2DGE;
#include "common.h"

#include "Menu.h"
//============================================================================
class InstructionsScene : public Scene, public Menu
{
public:
	InstructionsScene();
	virtual ~InstructionsScene();

    virtual void started(string arg);
    virtual void update();
    virtual void render();
        
private:
    Text * m_Title;
    vector< Text * > m_Lines;

};
//============================================================================
#endif /*InstructionsScene_H_*/
//============================================================================
