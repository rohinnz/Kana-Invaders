/** 
 * @file KanaCharacter.h
 *
 * @author Rohin Knight
 * @brief Represents any Kana character. Used in the kana review scene and
 * level scene.
 */
//============================================================================
#ifndef KanaCharacter_H_
#define KanaCharacter_H_
//============================================================================
#include "A2DGE/A2DGE.h"
using namespace A2DGE;
#include "common.h"
//============================================================================
class KanaCharacter : public Sprite
{
public:
    static const int NUM_ROMANJI;
    static const string ROMANJI[ /*71*/ ];
    static const int MAX_FRAMES;
    static const int LEVEL_LIMIT[];
    
    KanaCharacter( int frameIndex = 0 );
    virtual ~KanaCharacter();

    static vector< KanaCharacter* > getKanaCharacters( int level );

    string getRomanji();
    void playSound();
    
    bool isActive() { return isVisible() && ! m_Destroyed; }
    //void setActive( bool active ) { m_Active = active; }
    
    void setDestroyed( bool destroyed );
    bool isDestroyed() { return m_Destroyed; }

    static void loadAllSounds();
    
    void reset();

private:
    static Surface * m_KanaSurface;
    bool m_Destroyed;
    
    Surface * getKanaSurface();
    
    //static RCPtr<Sound> SOUNDS[];
    
};
//============================================================================

//============================================================================
#endif /*KanaCharacter_H_*/
//============================================================================
