/** 
 * @file MainMenuScene.h
 *
 * @author Rohin Knight
 * @brief The main menu scene
 */
//============================================================================
#ifndef MenuScene_H_
#define MenuScene_H_
//============================================================================
#include "A2DGE/A2DGE.h"
using namespace A2DGE;
#include "common.h"
#include "Menu.h"
//============================================================================
class MainMenuScene : public Scene, public Menu
{
public:
	MainMenuScene();
	virtual ~MainMenuScene();

    virtual void started(string arg);
    virtual void update();
    virtual void render();
    
private:
    enum OPTIONS { NEW_GAME, INSTRUCTIONS, CREDITS, EXIT };
    
    Text * m_Title;
    vector< Text * > m_Options;
    int m_Index;
    
    void highlightSelection( bool highlight );
    void selectHighlightedOption();
    int getHighlightedOptionIndex();

};
//============================================================================
#endif /*MenuScene_H_*/
//============================================================================

