/** 
 * @file EndGameScene.cpp
 *
 * @author Rohin Knight
 * @brief Displays end game message scrolling from bottom of screen.
 */
//============================================================================
#include "EndGameScene.h"
//============================================================================
EndGameScene::EndGameScene()
{
    TTF_Font * fontTitle = Singleton<FontManager>::getPtr()->getFont( "SceneTitle" );
    m_Title = new Text( "Game Over", Color(111, 217, 113), fontTitle );
    m_Title->setPosition( (Singleton<Display>::getPtr()->getWidth() / 2) - (m_Title->getWidth() / 2), 20 );
    
    string line;
    const string FILENAME = "data/endgame.dat";
    ifstream in( FILENAME.c_str() );

    if ( ! in.is_open() ) {
        string error( "EndGameScene::EndGameScene()\n"
                      "Unable to open file " );
        error += FILENAME;
        throw error;
    }
    
    //TTF_Font * fontHeading = Singleton<FontManager>::getPtr()->getFont( "CreditsHeader" );
    TTF_Font * fontMessage = Singleton<FontManager>::getPtr()->getFont( "NormalText" );
    
    while ( ! in.eof() )
    {
        getline( in, line );
        
        if ( ! line.empty() ) {  
            Text* text;
              
            if ( line[0] == '-' )      // TODO: refactor this code. This is a good example of how not to code when in a hurry.
                text = new Text( line, Color::WHITE, fontMessage ); 
            else
                text = new Text( line, Color(111, 217, 113), fontMessage );

            m_Lines.push_back( text );
        }
    }
    in.close();
}
//============================================================================
EndGameScene::~EndGameScene()
{
    delete m_Title;
    for ( vector< Text * >::iterator iter = m_Lines.begin(); iter != m_Lines.end(); ++iter )
    	delete *iter; 
}
//============================================================================
void EndGameScene::started(string level)
{    
    //TODO: Refactor this code.
    
    const int SCREEN_CENER = Singleton<Display>::getPtr()->getWidth() / 2;
    int yPos = Singleton<Display>::getPtr()->getHeight();
    
    for ( vector< Text* >::iterator iter = m_Lines.begin(); iter != m_Lines.end(); ++iter ) {
        Text* text = *iter;
        
        if ( text->getText()[ 0 ] == '-' )
            yPos += 110;
        else
            yPos += 20;
        
        text->setPosition( 60, yPos );
    }
    
    m_ResetYPos = yPos;
    m_Counter = 0;
    
    Singleton<Input>::getPtr()->getLastKey();  // remove last key pressed so Input::newKeyPressed() will not return true if Enter was pressed to get to this scene.
}
//============================================================================
void EndGameScene::update()
{
    Input* input = Singleton<Input>::getPtr();
    
    if (  input->newKeyPressed() )
        Singleton<SceneManager>::getPtr()->setCurrentScene( "MainMenu" );
        
    if ( m_Counter % 3 == 0 ) {
        for ( vector< Text* >::iterator iter = m_Lines.begin(); iter != m_Lines.end(); ++iter ) {
            Text* text = *iter;
            
            if ( text->getYPos() < 70 )
                text->setYPos( m_ResetYPos );
            else
                text->move( 0, -1 );
        }
    }
    
    if ( m_Counter == 2 )
        m_Counter = 0;
    else
        ++m_Counter;
}
//============================================================================
void EndGameScene::render()
{
    Surface * screen = Singleton<Display>::getPtr()->getSurface();
    Singleton<Display>::getPtr()->clearSurface( 0x000000 );

    m_Title->paint( screen );
    
    for ( vector< Text* >::iterator iter = m_Lines.begin(); iter != m_Lines.end(); ++iter ) {
        Text* text = *iter;
        
        if ( text->getText()[ 0 ] != '-' )
                text->paint( screen );
    }
}
//============================================================================

