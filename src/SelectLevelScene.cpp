/** 
 * @file SelectLevelScene.cpp
 *
 * @author Rohin Knight
 * @brief Scene to select level between 1 - 30
 */
//============================================================================
#include "SelectLevelScene.h"
//============================================================================
SelectLevelScene::SelectLevelScene()
    : LEVEL_TOTAL( 30 ),
      m_SelectedLevel( 0 ),
      m_HighestCompletedLevel( 0 )
{
	m_Padlock = new Image( "data/gfx/padlock.png" );
	
    TTF_Font * fontTitle = Singleton<FontManager>::getPtr()->getFont( "SceneTitle" );
    m_Title = new Text( "Select Level", Color(111, 217, 113), fontTitle );
    m_Title->setPosition( (Singleton<Display>::getPtr()->getWidth() / 2) - (m_Title->getWidth() / 2), 20 );
        
    fontNormal = Singleton<FontManager>::getPtr()->getFont( "NormalText" );
    Text * dummyText = new Text( "Level xx", Color(111, 217, 113), fontNormal );
    
    
    //const int PADDING_FROM_CENTER = 50;
    const int Y_POS = 130;
    const int Y_INCREMENT = 30; //24;
    
    const int X_POS_2 = (Singleton<Display>::getPtr()->getWidth() / 2) - (dummyText->getWidth() / 2);
    const int X_POS_1 = X_POS_2 - (dummyText->getWidth() * 2) - 5;
    const int X_POS_3 = X_POS_2 + (dummyText->getWidth() * 2) + 5;
    
    setupText( 0, 10,
        X_POS_1,
        Y_POS,
        Y_INCREMENT );
        
    setupText( 10, 20,
        X_POS_2,
        Y_POS,
        Y_INCREMENT );
        
    setupText( 20, LEVEL_TOTAL,
        X_POS_3,
        Y_POS,
        Y_INCREMENT );  

    delete dummyText;
}
//============================================================================
SelectLevelScene::~SelectLevelScene()
{
    for (int i = 0; i < LEVEL_TOTAL; ++i) {
        delete m_Levels[i];
    }

    delete m_Title;
    delete m_Padlock;
}
//============================================================================
void SelectLevelScene::started(string selectedLevel)
{
    Repository* repository = Singleton<Repository>::getPtr();
    
    int hcl;
    repository->getData( "HCL", hcl );
    m_HighestCompletedLevel = hcl - 1;  // subtract 1 so we can use it as array index
    
    highlightSelection( false );
    m_SelectedLevel = convert_string_to_int(selectedLevel) - 1;
    highlightSelection( true );
    
    m_Cheat = "";
}
//============================================================================
void SelectLevelScene::update()
{
    Input* input = Singleton<Input>::getPtr();
  
    if ( input->leftMBClicked() ) {
        int index = getHighlightedOptionIndex();
        
        if ( index != -1 )
            selectHighlightedLevel();
    }
    else if ( input->mouseMoved() ) {
        int index = getHighlightedOptionIndex();
        
        if ( index != -1 ) {
            highlightSelection( false );
            m_SelectedLevel = index;
            highlightSelection( true );
        }
    }
    
    if ( input->keyPressed( SDLK_UP ) ) {        
        m_Cheat = "";
        highlightSelection( false );
        
        if ( m_SelectedLevel == 0 )
            m_SelectedLevel = LEVEL_TOTAL - 1;
        else
            --m_SelectedLevel;

        highlightSelection( true );            
    }
    else if ( input->keyPressed( SDLK_DOWN ) ) {
        m_Cheat = "";
        highlightSelection( false );
        
        if ( m_SelectedLevel + 1 == LEVEL_TOTAL )
            m_SelectedLevel = 0;
        else
            ++m_SelectedLevel;
            
        highlightSelection( true );
    }
    else if ( input->keyPressed( SDLK_LEFT ) ) {
        m_Cheat = "";
        highlightSelection( false );
        
        if ( m_SelectedLevel < 10 )
            m_SelectedLevel += 20;
        else
            m_SelectedLevel -= 10;
            
        highlightSelection( true );
    }
    else if ( input->keyPressed( SDLK_RIGHT ) ) {
        m_Cheat = "";
        highlightSelection( false );
        
        if ( m_SelectedLevel >= 20 )
            m_SelectedLevel -= 20;
        else
            m_SelectedLevel += 10;
            
        highlightSelection( true );
    }
    else if ( input->keyPressed( SDLK_RETURN ) ) {   
        selectHighlightedLevel();
    }
    else if ( input->keyPressed( SDLK_ESCAPE ) ) {
        playChangedSound();
        
        Singleton<SceneManager>::getPtr()->setCurrentScene( "MainMenu" );
    }
    else if ( input->newKeyPressed() ) {
        Uint16 key = Singleton<Input>::getPtr()->getLastKey();
        
        if ( key >= 'a' && key <= 'z' )
            m_Cheat += key;
        else if ( key >= 'A' && key <= 'Z' )
            m_Cheat += tolower( key );
            
        if ( m_Cheat == "kana" ) {            
            m_HighestCompletedLevel = m_SelectedLevel;
            
            int hcl = m_HighestCompletedLevel + 1;
            
            Repository* repository = Singleton<Repository>::getPtr();
            repository->setData( "HCL", hcl );
            repository->saveToDisk();
            
            m_Cheat = "";
        }
    }
}
//============================================================================
void SelectLevelScene::render()
{
    Surface* screen = Singleton<Display>::getPtr()->getSurface();
    Singleton<Display>::getPtr()->clearSurface( 0x000000 );

    m_Title->paint( screen );
    
    for ( int i = 0; i < LEVEL_TOTAL; ++i ) {
        m_Levels[ i ]->paint( screen );
        if ( i > m_HighestCompletedLevel ) {
            m_Padlock->setPosition( m_Levels[ i ]->getXPos() - 15, m_Levels[ i ]->getYPos() );
            m_Padlock->paint( screen );
        }
    }
}
//============================================================================
void SelectLevelScene::setupText( const int START, const int END, const int X_POS,
                                  int yPos, const int Y_INCREMENT )
{
    TTF_Font * font = Singleton<FontManager>::getPtr()->getFont( "NormalText" );
    for ( int i = START; i < END; ++i ) {
        char text[10];
        sprintf( text, "Level %d", i + 1 );
        
        m_Levels[ i ] = new Text( text, Color(111, 217, 113), font );
        m_Levels[ i ]->setPosition( X_POS, yPos );
        yPos += Y_INCREMENT;
    }
}
//============================================================================
void SelectLevelScene::highlightSelection( bool highlight )
{
    highlightText( m_Levels[ m_SelectedLevel ], highlight );
}
//============================================================================
void SelectLevelScene::selectHighlightedLevel()
{
        if ( m_SelectedLevel <= m_HighestCompletedLevel ) {
            playChangedSound();
            Singleton<SceneManager>::getPtr()->setCurrentScene( "KanaReview", convert_int_to_string(m_SelectedLevel + 1) );
        }
        else
            Singleton<SoundManager>::getPtr()->playSound( "error" );
        
}
//============================================================================
int SelectLevelScene::getHighlightedOptionIndex()
{
    Input* input = Singleton<Input>::getPtr();
    
    for ( int i = 0; i < LEVEL_TOTAL; ++i ) {
        if ( input->getMouseXPos() > m_Levels[ i ]->getXPos() && 
                 input->getMouseXPos() < m_Levels[ i ]->getXPos() + m_Levels[ i ]->getWidth() &&
                 input->getMouseYPos() > m_Levels[ i ]->getYPos() &&
                 input->getMouseYPos() < m_Levels[ i ]->getYPos() + m_Levels[ i ]->getHeight() )
        {
            return i;
        }
    }
    
    return -1;
}
//============================================================================
