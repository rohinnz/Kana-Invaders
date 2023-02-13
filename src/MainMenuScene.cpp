/** 
 * @file MainMenuScene.cpp
 *
 * @author Rohin Knight
 * @brief The main menu scene
 */
//============================================================================
#include "MainMenuScene.h"
//============================================================================
MainMenuScene::MainMenuScene()
    : m_Index( 0 )
{
    TTF_Font * fontTitle = Singleton<FontManager>::getPtr()->getFont( "SceneTitle" );
    m_Title = new Text( "Kana Invaders", Color(111, 217, 113) /*( 64, 120, 120 )*/, fontTitle );
    m_Title->setPosition( (Singleton<Display>::getPtr()->getWidth() / 2) - (m_Title->getWidth() / 2), 20 );
    
    TTF_Font * fontMenuOption = Singleton<FontManager>::getPtr()->getFont( "NormalText" );
    m_Options.push_back( new Text( "New Game", Color(111, 217, 113), fontMenuOption ) );
    m_Options.push_back( new Text( "Instructions", Color(111, 217, 113), fontMenuOption ) );
    m_Options.push_back( new Text( "Credits", Color(111, 217, 113), fontMenuOption ) );
    m_Options.push_back( new Text( "Exit", Color(111, 217, 113), fontMenuOption ) );
        
    int yPos = 180;
    for ( vector< Text* >::iterator iter = m_Options.begin(); iter != m_Options.end(); ++iter ) {
        (*iter)->setPosition( 100, yPos );
        yPos += 50;
    }
    
 /*
    // Add to the layer manager which will take care of cleaning up resoruces later
    Singleton<LayerManager>::getPtr()->addLayer( "MainMenu", m_Title );

    for ( vector< Text* >::iterator iter = m_Options.begin(); iter != m_Options.end(); ++iter )
    	Singleton<LayerManager>::getPtr()->addLayer( "MainMenu", *iter );
    */
    
    //m_Background = new Image( "data/gfx/Japan.PNG" );
    //sound = new Sound( "sound/SPACEBO.WAV" );
}
//============================================================================
MainMenuScene::~MainMenuScene()
{	
    delete m_Title;
    
    vector< Text * >::iterator iter;
    for ( iter = m_Options.begin(); iter != m_Options.end(); ++iter )
    	delete *iter;
}
//============================================================================
void MainMenuScene::started(string arg)
{
    highlightSelection( false );
    m_Index = 0;
    highlightSelection( true );
}
//============================================================================
void MainMenuScene::update()
{
    Input* input = Singleton<Input>::getPtr();
  
    if ( input->leftMBClicked() ) {
        int index = getHighlightedOptionIndex();
        
        if ( index != -1 )
            selectHighlightedOption();
    }
    else if ( input->mouseMoved() ) {
        int index = getHighlightedOptionIndex();
        
        if ( index != -1 ) {
            highlightSelection( false );
            m_Index = index;
            highlightSelection( true );
        }
    }
    
    if ( input->keyPressed( SDLK_UP ) ) {
        highlightSelection( false );
        
        if ( m_Index == 0 )
            m_Index = m_Options.size() - 1;
        else
            --m_Index;
            
        highlightSelection( true );
    }
    else if ( input->keyPressed( SDLK_DOWN ) ) {
        highlightSelection( false );
        
        if ( m_Index + 1 == static_cast<int>(m_Options.size()) )
            m_Index = 0;
        else
            ++m_Index;
        
        highlightSelection(  true );
    }
    else if ( input->keyPressed( SDLK_RETURN ) ) {
        selectHighlightedOption();
    }
    else if ( input->keyPressed( SDLK_ESCAPE ) ) {
        playChangedSound();
        Singleton<Engine>::getPtr()->quit();
    }
}
//============================================================================
void MainMenuScene::render()
{
    Singleton<Display>::getPtr()->clearSurface( 0x000000 );
    Surface * screen = Singleton<Display>::getPtr()->getSurface();   

    //m_Background->paint( screen );
    
    m_Title->paint( screen );
        
    for ( vector< Text * >::iterator iter = m_Options.begin(); iter != m_Options.end(); ++iter )
        (*iter)->paint( screen ); 
}
//============================================================================
void MainMenuScene::highlightSelection( bool highlight )
{
    highlightText( m_Options[ m_Index ], highlight );
}
//============================================================================
void MainMenuScene::selectHighlightedOption()
{
    if ( m_Index != EXIT )
        playChangedSound();
 
    switch ( m_Index ) {
    case NEW_GAME:
        Singleton<SceneManager>::getPtr()->setCurrentScene( "SelectLevel", "1");
        break;
    case INSTRUCTIONS:
        Singleton<SceneManager>::getPtr()->setCurrentScene( "Instructions" );
        break;
    case CREDITS:
        Singleton<SceneManager>::getPtr()->setCurrentScene( "Credits" );
        break;
    case EXIT:
        Singleton<Engine>::getPtr()->quit();
        break;
    }
}
//============================================================================
int MainMenuScene::getHighlightedOptionIndex()
{
    Input* input = Singleton<Input>::getPtr();
    int index = 0;
    
    for ( vector< Text * >::iterator iter = m_Options.begin(); iter != m_Options.end(); ++iter ) {
        Text * text = *iter;
                
        if ( input->getMouseXPos() > text->getXPos() && 
                 input->getMouseXPos() < text->getXPos() + text->getWidth() &&
                 input->getMouseYPos() > text->getYPos() &&
                 input->getMouseYPos() < text->getYPos() + text->getHeight() )
        {
            return index;
        }
        
        index++;
    }
    
    return -1;
}
//============================================================================
