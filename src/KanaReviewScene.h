/** 
 * @file KanaReviewScene.h
 *
 * @author Rohin Knight
 * @brief Scene to review new Kana characters before starting a level.
 */
//============================================================================
#ifndef KanaReviewScene_H_
#define KanaReviewScene_H_
//============================================================================
#include "A2DGE/A2DGE.h"
using namespace A2DGE;
#include "common.h"
#include "Menu.h"
#include "KanaCharacter.h"
#include "LevelScene.h"
//============================================================================
class KanaReviewScene : public Scene, public Menu
{
public:
	KanaReviewScene();
	virtual ~KanaReviewScene();

    virtual void started(string level);
    virtual void update();
    virtual void render();
    
    void setKanaCharacters();
    
private:
    bool m_StartlevelSelected;
    int m_Index;
    int m_Level;
    
    Text * m_Title;
    Text * m_Message_1;
    Text * m_Message_2;
    Text * m_Level30_Message;
    Text * m_StartLevel;
    
    //RCPtr<Sound> m_ExampleSound;
    
    vector< KanaCharacter * > m_KanaCharacters;
    vector< Text * > m_Romanji;
    
    void highlightSelection( bool highlight );
    void selectHighlightedOption();
    int getHighlightedOptionIndex();

};
//============================================================================
#endif /*KanaReviewScene_H_*/
//============================================================================

