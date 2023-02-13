/** 
 * @file LevelScene.cpp
 *
 * @author Rohin Knight
 * @brief The level scene is where all the action happens. It controls
 * several objects including the Kana characters and the player's ship.
 */
//============================================================================
#include "LevelScene.h"
//============================================================================
const int LevelScene::MAX_WAVES = 4;
const int LevelScene::MAX_LEVELS = 30;
const int LevelScene::WAVE_TARGET_POINTS[ MAX_WAVES ] = { 70, 80, 90, 100 };
const int LevelScene::MAX_FALLING_KANA[ MAX_WAVES ] = { 3, 4, 5, 3 };
const int LevelScene::KANA_SPEED[ MAX_WAVES ] = { 1, 1, 1, 2 };
const unsigned int LevelScene::KANA_COLUMNS = 6;
const int LevelScene::POINT_INCREMENT = 5;
const int LevelScene::POINT_DECREMENT = 10;
//============================================================================
LevelScene::LevelScene()
{
    m_PlayerShip = new PlayerShip();
    m_Missile = new Missile();
    m_Target = new Image( new Surface( "data/gfx/target.png", Color::BLACK ) );
    m_Background = new Image( "data/gfx/bk_L30.png" );
    
    for ( int i = 0; i < 70; ++i ) { // create stars
        Star * star = new Star();        
        m_Stars.push_back( star );
    }
    
    for ( unsigned int i = 0; i < KANA_COLUMNS; ++i ) {  // create kana characters
        KanaCharacter * kana = new KanaCharacter();
        kana->addCollisionRectangle( 10, 10, 60, 60 );
        kana->setXPos( i * 100 );
        m_KanaCharacters.push_back( kana );
    }
}
//============================================================================
LevelScene::~LevelScene()
{

	delete m_PlayerShip;
	delete m_Missile;
	delete m_Target;
	delete m_Background;

	
	for ( vector< KanaCharacter* >::iterator iter = m_KanaCharacters.begin(); iter != m_KanaCharacters.end(); ++iter )
		delete *iter;

/*			
	for ( vector< Star* >::iterator iter = m_Stars.begin(); iter != m_Stars.end(); ++iter )
		delete *iter;
*/	
	clearTempMsgs();

}
//============================================================================
void LevelScene::started(string level)
{   
	m_Level = convert_string_to_int(level); // strConvert.c_str()); 
	
//	m_Level = reinterpret_cast<int>(level);
    //m_Level = (int)level;
    m_Wave = 1;
    m_Lives = 3;
    m_Points = 0;
    
    m_LevelCheatsEnabled = true;
    
    m_Target->setVisible(false);
    m_Missile->reset();
    
    m_PlayerShip->reset( m_Level );
    
    for ( unsigned int i = 0; i < KANA_COLUMNS; ++i )
        m_KanaCharacters[ i ]->reset();
    
    clearTempMsgs();
   
    showNextWaveMessage();
}
//============================================================================
void LevelScene::showNextWaveMessage()
{
    m_LevelState = DELAY_MESSAGE;
    m_MessageState = WAVE_STARTS_MSG;
    char msg1[100];
    char msg2[100];
    sprintf( msg1, "Wave %d", m_Wave );
    sprintf( msg2, "Get %d points", WAVE_TARGET_POINTS[ m_Wave - 1 ] );                
    m_DisplayMessage.setMessage( msg1, msg2 );    
}
//============================================================================
void LevelScene::update()
{    
    Input* input = Singleton<Input>::getPtr();
    
    if ( input->modifierKeyDown( KMOD_CTRL ) && m_LevelCheatsEnabled ) {
        if ( input->keyPressed( SDLK_l ) )
            gotoNextLevel();
        else if ( input->keyPressed( SDLK_w ) && m_Wave < MAX_WAVES )
            gotoNextWave();
    }
                      
    for ( vector< Star * >::iterator iter = m_Stars.begin(); iter != m_Stars.end(); ++iter ) {
        Star * star = *iter;
        star->updatePosition();
    }
    
    if ( Singleton<Input>::getPtr()->keyPressed( SDLK_ESCAPE ) )
        Singleton<SceneManager>::getPtr()->setCurrentScene( "KanaReview", convert_int_to_string(m_Level) );
    
    switch ( m_LevelState ) {
    case DELAY_MESSAGE:
        if ( m_DisplayMessage.isDisplayTimeUp() ) {
            switch ( m_MessageState ) {
            
            case NEXT_WAVE:
                //m_MessageState = WAVE_STARTS_MSG; 
                
                showNextWaveMessage();
                break;
            
            case WAVE_STARTS_MSG:
                m_LevelState = PLAYING;
                break;
            case WIN_MSG:
                if ( m_Wave == MAX_WAVES )
                    gotoNextLevel();
                else
                    m_Wave++;

                break;
            case LOSE_MSG:
                Singleton<SceneManager>::getPtr()->setCurrentScene( "KanaReview", convert_int_to_string(m_Level));
                break;
            }
        }
        break;
    case PLAYING:
        updatePlayingState();
        break;
    }
}
//============================================================================
void LevelScene::render()
{
    // clear screen black
    Singleton<Display>::getPtr()->clearSurface( 0x000000 );
    Surface * screen = Singleton<Display>::getPtr()->getSurface();    
    
    if ( m_Level == MAX_LEVELS ) {  // if last level display image of earth instead of rendering stars
        m_Background->paint( screen );
    }
    else {
        for ( vector< Star * >::iterator iter = m_Stars.begin(); iter != m_Stars.end(); ++iter ) {
            Star * star = *iter;
            star->paint( screen );
        }
    }
    
    if ( m_LevelState == DELAY_MESSAGE ) {
        m_DisplayMessage.render();
    }
    else {
        //m_Background->paint( screen );
        
        for ( unsigned int i = 0; i < KANA_COLUMNS; ++i ) {
            if ( m_KanaCharacters[ i ]->isVisible() || m_KanaCharacters[ i ]->isDestroyed() )
                m_KanaCharacters[ i ]->paint( screen );
        }
        
        m_Missile->paint( screen );
        m_PlayerShip->paint( screen );
        renderTempLevelMsgs( screen );
        m_HUD.render();
        
        if ( m_Target->isVisible() ) {
            m_Target->paint( screen );
            m_DisplayMessage.render();
        }
    }
}
//============================================================================
void LevelScene::updatePlayingState()
{
    updatePlayerShip();
    updateMissile();
    updateKana();
    updateTempLevelMsgs();

    //===============================
    // Is it time to update the wave?
     
    if ( m_Points >= WAVE_TARGET_POINTS[ m_Wave - 1 ] && ! m_PlayerShip->isDestroyed() ) {
        
        if ( m_Wave == MAX_WAVES ) {
            m_LevelState = DELAY_MESSAGE;
            m_MessageState = WIN_MSG;
            char msg[100];
            sprintf( msg, "Level %d complete", m_Level );
            m_DisplayMessage.setMessage( msg, " " );
        }
        else {
            
            gotoNextWave();
            
        }
        
        clearTempMsgs();
    }
        
    m_HUD.update( m_Level, m_Wave, m_Lives, m_Points );
}
//============================================================================
void LevelScene::updatePlayerShip()
{
     if ( m_PlayerShip->isDestroyed() )
     {            
        if ( m_PlayerShip->destroyTimerFinished() ) {
            if ( m_Lives > 1 ) {
                //m_LevelState = PLAYING;
                m_Lives--;
                m_PlayerShip->reset( m_Level );
                m_PlayerShip->setFlashing( true );
                m_Missile->reset();
            }
            else {
                m_LevelState = DELAY_MESSAGE;
                m_MessageState = LOSE_MSG;
                m_DisplayMessage.setMessage( "Game Over", "No Ships Left" );
            }
        }
        else if ( ! m_PlayerShip->isLastFrame() )
            m_PlayerShip->updateFrame();
    }
    else {
        m_PlayerShip->updatePosition();
        m_PlayerShip->updateFlashing();
        m_PlayerShip->updateFrame();
    }
}
//============================================================================
void LevelScene::updateMissile()
{
    if ( m_Missile->isVisible() ) {
        m_Missile->updateAnimation();
        m_Missile->updatePosition();        
    }  
    else if ( ! m_PlayerShip->isDestroyed() && findTarget() ) {        
        
        if ( m_KanaRomanjiLength == static_cast<int>(m_Missile->getRomanji().size()) ) {
        //if ( Singleton<Input>::getPtr()->keyPressed( SDLK_RETURN ) ) { 
            m_Missile->setPosition( m_PlayerShip->getXPos() + (m_PlayerShip->getWidth() / 2) - (m_Missile->getWidth() / 2), m_PlayerShip->getYPos() );
            m_Missile->setVisible( true );
            //m_Missile->clearRomanji();
            m_Target->setVisible( false );
        }
        else
            m_Missile->updateRomanji();

        m_DisplayMessage.setMessage( "Enter Kana Romanji", m_Missile->getRomanji() + "_" );
    }
}
//============================================================================
void LevelScene::updateKana()
{
    // Update kana movements
    int activeKanas = 0;
    
    for ( unsigned int i = 0; i < KANA_COLUMNS; ++i ) {
        if ( m_KanaCharacters[ i ]->isActive() ) {
            if ( m_KanaCharacters[ i ]->getYPos() > Singleton<Display>::getPtr()->getHeight() ) {
                m_KanaCharacters[ i ]->setVisible( false );
                
                if ( ! (m_PlayerShip->isDestroyed() || m_PlayerShip->isFlashing()) ) {
                   
                   m_Points -= POINT_DECREMENT;
                   
                   // TODO: Put point update message in function
                   TempLevelMsg* msg = new TempLevelMsg( "-10", Color::RED, Singleton<FontManager>::getPtr()->getFont( "TempMessage" ) );
                   msg->setPosition( m_KanaCharacters[ i ]->getXPos() + 32, Singleton<Display>::getPtr()->getHeight());                                      
                   m_TempMsgs.push_back(msg);
                   
                   if ( m_Points < 0 )
                      m_Points = 0;
                }
            }
            else if ( ! m_PlayerShip->isFlashing() && m_KanaCharacters[ i ]->collisionWith( m_PlayerShip ) ) {
                //m_KanaCharacters[ i ]->setVisible( false );
                m_KanaCharacters[ i ]->setDestroyed( true );
                
                m_PlayerShip->destroy();
                m_Target->setVisible( false );
                m_Missile->setVisible( false );            
            }
            else if ( m_Missile->isActive() && 
                      m_KanaCharacters[ i ]->collisionWith( m_Missile, Sprite::BOX_BOX ) && 
                      m_KanaCharacters[ i ]->collisionWith( m_Missile ) ) {
//                m_Missile->setVisible( false );
                m_Missile->setDestroyed( true );
                m_KanaCharacters[ i ]->playSound();
                
                if ( m_Missile->getRomanji() == m_KanaCharacters[ i ]->getRomanji() ) {
                    
                    m_KanaCharacters[ i ]->setDestroyed( true );
                    
                    if ( ! m_PlayerShip->isDestroyed() ) {
                        m_Points += POINT_INCREMENT;
                        
                        // TODO: Put point update message in function
                   		TempLevelMsg* msg = new TempLevelMsg( "+5", Color::GREEN, Singleton<FontManager>::getPtr()->getFont( "TempMessage" ) );
                   		msg->setPosition( m_KanaCharacters[ i ]->getXPos() + 32, m_KanaCharacters[ i ]->getYPos());                                      
                   		m_TempMsgs.push_back(msg);
                    }
                }
                
                m_Missile->clearRomanji();
            }
            else {
                m_KanaCharacters[ i ]->move( 0, KANA_SPEED[ m_Wave - 1 ] );
                activeKanas++;
            }
        }
        else if ( m_KanaCharacters[ i ]->isDestroyed() ) {
            if ( m_KanaCharacters[ i ]->isLastFrame() ) {
                m_KanaCharacters[ i ]->setDestroyed( false );
                m_KanaCharacters[ i ]->setVisible( false );
            }    
            else {
                m_KanaCharacters[ i ]->updateFrame();
                m_KanaCharacters[ i ]->move( 0, 1 );
                
                
            }
        }
    }
    
    //========================
    // Add new kana characters
    
    // determine if we should add more kana to the level
    if ( activeKanas < MAX_FALLING_KANA[ m_Wave - 1 ] ) {
        // make a kana active
        vector< KanaCharacter * > nonActiveKana;
        
        for ( unsigned int i = 0; i < KANA_COLUMNS; ++i )
            if ( ! m_KanaCharacters[ i ]->isVisible() /*&& ! m_KanaCharacters[ i ]->isDestroyed()*/ )
                nonActiveKana.push_back( m_KanaCharacters[ i ] );
               
        if ( ! nonActiveKana.empty() ) {
                
            //TODO: Choose a character at random from the vector
            KanaCharacter * kana = nonActiveKana[ rand() % nonActiveKana.size() ];
        
            kana->setYPos( 0 ); // 0 - rand() % Singleton<Display>::getPtr()->getHeight() );
            kana->setVisible( true );
        
            int newFrame;
        
        
        
            if ( m_Level > 1 ) {
                if ( m_Wave == 1 ) {  // only display new characters for first wave
                   newFrame = KanaCharacter::LEVEL_LIMIT[ m_Level - 2 ] + (rand() % (KanaCharacter::LEVEL_LIMIT[m_Level - 2] - KanaCharacter::LEVEL_LIMIT[m_Level - 1]));
                 
                }
                else {
                    if ( rand() % 5 == 3 )  // add a higher probability of one of the new characters appearing
                        newFrame = KanaCharacter::LEVEL_LIMIT[ m_Level - 2 ] + (rand() % (KanaCharacter::LEVEL_LIMIT[m_Level - 2] - KanaCharacter::LEVEL_LIMIT[m_Level - 1]));
                    else
                        newFrame = rand() % KanaCharacter::LEVEL_LIMIT[ m_Level - 1 ]; 
                }
            }
            else {
                newFrame = rand() % KanaCharacter::LEVEL_LIMIT[ 0 ];
            }
            
            kana->setFrameIndex( newFrame );
            kana->setYPos( 0 - (kana->getHeight() + ((rand() % 5) * kana->getHeight()) ) );
        }
    }
}
//============================================================================
void LevelScene::updateTempLevelMsgs()
{
	if (! m_TempMsgs.empty()) {		
		TempLevelMsg* msg = m_TempMsgs.front();
		
		if ( ! msg->isVisible() ) {			
			m_TempMsgs.pop_front();
			delete msg;
		}
		
		deque< TempLevelMsg* >::iterator iter;
	
		for ( iter = m_TempMsgs.begin(); iter != m_TempMsgs.end(); ++iter ) {
			(*iter)->update();
		}
	}
}
//============================================================================
void LevelScene::renderTempLevelMsgs( Surface* screen )
{
	deque< TempLevelMsg* >::iterator iter;
	
	for ( iter = m_TempMsgs.begin(); iter != m_TempMsgs.end(); ++iter ) {
		(*iter)->paint( screen );
	}
}
//============================================================================
void LevelScene::gotoNextWave()
{
    m_LevelState = DELAY_MESSAGE;
    m_Target->setVisible( false );
    m_Missile->reset();
    m_PlayerShip->reset( m_Level );
    m_Missile->clearRomanji();
    
    for ( unsigned int i = 0; i < KANA_COLUMNS; ++i )
        m_KanaCharacters[ i ]->reset();
            
    m_MessageState = NEXT_WAVE;
    
    char msg[100];
    sprintf( msg, "Wave %d complete", m_Wave );
    m_DisplayMessage.setMessage( msg, " " );
            
    m_Points = 0;
    m_Wave++;
}
//============================================================================
void LevelScene::gotoNextLevel()
{
    if ( m_Level == MAX_LEVELS )
        Singleton<SceneManager>::getPtr()->setCurrentScene( "EndGame" );
    else
        Singleton<SceneManager>::getPtr()->setCurrentScene( "KanaReview", convert_int_to_string(m_Level + 1));     
}
//============================================================================
bool LevelScene::findTarget()
{
    //TODO: determine if target is active by working first which column the player ship is in.
    int shipCenterPos = m_PlayerShip->getXPos() + (m_PlayerShip->getWidth() / 2);
    //m_KanaCharacters[ i ]->getXPos()
    
    for ( unsigned int i = 0; i < KANA_COLUMNS; ++i ) {
        if ( m_KanaCharacters[ i ]->isVisible() &&
             /*m_KanaCharacters[ i ]->isTargetable() && */
             shipCenterPos > m_KanaCharacters[ i ]->getXPos() &&
             shipCenterPos < m_KanaCharacters[ i ]->getXPos() + m_KanaCharacters[ i ]->getWidth() &&
             m_KanaCharacters[ i ]->getYPos() >= 0 &&
             m_PlayerShip->getYPos() > m_KanaCharacters[ i ]->getYPos() ) {
            //TODO add target to ;
            
            m_Target->setPosition( m_KanaCharacters[ i ]->getXPos(), m_KanaCharacters[ i ]->getYPos() );
            m_Target->setVisible( true );
            
            m_KanaRomanjiLength = m_KanaCharacters[ i ]->getRomanji().size();
            return true;
        }
    }
    
    m_Missile->clearRomanji();
    m_Target->setVisible( false );
    return false;
}
//============================================================================
void LevelScene::clearTempMsgs()
{
    if (! m_TempMsgs.empty() ) {    
   		for ( deque< TempLevelMsg* >::iterator iter = m_TempMsgs.begin(); iter != m_TempMsgs.end(); ++iter )
			delete *iter;
	
		m_TempMsgs.erase( m_TempMsgs.begin(), m_TempMsgs.end() );
    }
}
//============================================================================
