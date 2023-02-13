/** 
 * @file LevelScene.h
 *
 * @author Rohin Knight
 * @brief The level scene is where all the action happens. It controls
 * several objects including the Kana characters and the player's ship.
 */
//============================================================================
#ifndef LevelScene_H_
#define LevelScene_H_
//============================================================================
#include "A2DGE/A2DGE.h"
using namespace A2DGE;

#include "common.h"
#include "PlayerShip.h"
#include "Missile.h"
#include "KanaCharacter.h"
#include "HUD.h"
#include "DisplayMessage.h"
#include "Star.h"
#include "TempLevelMsg.h"
//============================================================================
class LevelScene : public Scene
{
public:
	LevelScene();
	virtual ~LevelScene();

    virtual void started(string level);
    virtual void update();
    virtual void render();
    
    //void setLevel( int level ) { m_Level = level; }
    
private:
    enum LEVEL_STATE { DELAY_MESSAGE, PLAYING /*, WRONG_MID, SHIP_DESTROYED */ };
    enum MESSAGE_STATE { NEXT_WAVE, WAVE_STARTS_MSG, LOSE_MSG, WIN_MSG };
    static const int MAX_WAVES;
    static const int MAX_LEVELS;
    static const int WAVE_TARGET_POINTS[ /*MAX_WAVES*/ ]; /* Number of ... */
    static const int WAVE_CHARACTERS[ /*MAX_WAVES*/ ];   /* Number of characters that should fall for each wave */
    static const int MAX_FALLING_KANA[ /*MAX_WAVES*/ ];
    static const int KANA_SPEED[ /*MAX_WAVES*/ ];
    static const unsigned int KANA_COLUMNS;
    static const int POINT_INCREMENT;
    static const int POINT_DECREMENT;

    
    // State variables
    LEVEL_STATE m_LevelState;
    MESSAGE_STATE m_MessageState;
    
    // Moving objects    
    PlayerShip * m_PlayerShip;
    Missile * m_Missile;
    Image * m_Target;
    Image * m_Background;
    

	deque< TempLevelMsg* > m_TempMsgs;

    vector< KanaCharacter * > m_KanaCharacters; //[ KANA_COLUMNS ];
    //RCPtr<KanaCharacter> m_TargetKana;

    // Text
    DisplayMessage m_DisplayMessage;
    HUD m_HUD;
    //string m_MissileID;
    
    // Sound
    //RCPtr<Sound> m_MissileFired;
    //RCPtr<Sound> m_Destroyed;
    //RCPtr<Music> m_BGMusic;
    
    // Other
    int m_Level;
    int m_Wave;
    int m_Lives;
    int m_Points;
    int m_TargetPoints;
    //bool m_TargetActive;
    
    int m_KanaRomanjiLength;
    //bool m_MissileActive;
    
    bool m_LevelCheatsEnabled;
    
    
    vector< Star * > m_Stars;
    
    // Private methods    
    void updatePlayingState();
    bool findTarget();
    void showNextWaveMessage();
    
    void updateTempLevelMsgs();
    void renderTempLevelMsgs( Surface* screen );

    void gotoNextWave();
    void gotoNextLevel();
    
    void updatePlayerShip();
    void updateMissile();
    void updateKana();

	void clearTempMsgs();

};
//============================================================================
#endif /*LevelScene_H_*/
//============================================================================
