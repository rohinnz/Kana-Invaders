/** 
 * @file SelectLevelScene.h
 *
 * @author Rohin Knight
 * @brief Scene to select level between 1 - 30
 */
//============================================================================
#ifndef SelectLevelScene_H_
#define SelectLevelScene_H_
//============================================================================
#include "A2DGE/A2DGE.h"
using namespace A2DGE;
#include "common.h"
#include "Menu.h"
#include "KanaReviewScene.h"
//============================================================================
class SelectLevelScene : public Scene, public Menu
{
public:
	SelectLevelScene();
	virtual ~SelectLevelScene();

    virtual void started(string selectedLevel);
    virtual void update();
    virtual void render();

private:
    const int LEVEL_TOTAL;
    //vector< RCPtr<Text> > m_Levels;
    Text* m_Levels[ 30 ];  // replaced LEVEL_TOTAL with 30 because compiler was complaining
    Text* m_Title;
    Image* m_Padlock;
    int m_SelectedLevel;
    int m_HighestCompletedLevel;

    TTF_Font * fontNormal;
    string m_Cheat;

    void setupText( const int START, const int END, const int X_POS,
                    int yPos, const int Y_INCREMENT );
    void highlightSelection( bool highlight );
    void selectHighlightedLevel();
    int getHighlightedOptionIndex();

};
//============================================================================
#endif /*SelectLevelScene_H_*/
//============================================================================

