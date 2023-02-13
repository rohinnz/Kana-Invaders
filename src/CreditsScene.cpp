/** 
 * @file CreditsScene.cpp
 *
 * @author Rohin Knight
 * @brief Displays the game credits scrolling from bottom of screen.
 */
//============================================================================
#include "CreditsScene.h"
//============================================================================
CreditsScene::CreditsScene()
{
    TTF_Font * fontTitle = Singleton<FontManager>::getPtr()->getFont( "SceneTitle" );
    m_Title = new Text( "Credits", Color(111, 217, 113), fontTitle );
    m_Title->setPosition( (Singleton<Display>::getPtr()->getWidth() / 2) - (m_Title->getWidth() / 2), 20 );
    
    string line;
    const string FILENAME = "data/credits.dat";
    ifstream in( FILENAME.c_str() );

    if ( ! in.is_open() ) {
        string error( "CreditsScene::CreditsScene()\n"
                      "Unable to open file " );
        error += FILENAME;
        throw error;
    }
    
    TTF_Font * fontHeading = Singleton<FontManager>::getPtr()->getFont( "CreditsHeader" );
    TTF_Font * fontMessage = Singleton<FontManager>::getPtr()->getFont( "CreditsText" );
    
    while ( ! in.eof() )
    {
        getline( in, line );
        
        if ( ! line.empty() ) {  
            Text* text;
              
            if ( line[0] == ' ' )     
                text = new Text( line, Color(111, 217, 113), fontHeading );
            else
                text = new Text( line, Color(111, 217, 113), fontMessage );

            m_Lines.push_back( text );
        }
    }
    in.close();
}
//============================================================================
CreditsScene::~CreditsScene()
{
    delete m_Title;
                             
    for ( vector< Text* >::iterator iter = m_Lines.begin(); iter != m_Lines.end(); ++iter )
        delete *iter;
}
//============================================================================
void CreditsScene::started(string arg)
{
    //TODO: Refactor this code.
    
    const int SCREEN_CENER = Singleton<Display>::getPtr()->getWidth() / 2;
    int yPos = Singleton<Display>::getPtr()->getHeight() - 90;
    
    for ( vector< Text* >::iterator iter = m_Lines.begin(); iter != m_Lines.end(); ++iter ) {
        Text* text = *iter;
        
        if ( text->getText()[ 0 ] == ' ' )
            yPos += 70;
        else
            yPos += 35;
        
        text->setPosition( SCREEN_CENER - text->getWidth() / 2, yPos );
        
        if ( text->getText()[ 0 ] == ' ' )
            yPos += 10;
    }
    
    m_ResetYPos = yPos;
    m_Counter = 0;
    
    Singleton<Input>::getPtr()->getLastKey();  // remove last key pressed so Input::newKeyPressed() will not return true if Enter was pressed to get to this scene.
}
//============================================================================
void CreditsScene::update()
{
    Input* input = Singleton<Input>::getPtr();
    
    if (  input->newKeyPressed() )
        Singleton<SceneManager>::getPtr()->setCurrentScene( "MainMenu" );
        
    if ( m_Counter % 2 == 0 ) {
        for ( vector< Text* >::iterator iter = m_Lines.begin(); iter != m_Lines.end(); ++iter ) {
            Text* text = *iter;
            
            if ( text->getYPos() < 70 )
                text->setYPos( m_ResetYPos );
            else
                text->move( 0, -1 );
        }
    }
    
    if ( m_Counter == 1 )
        m_Counter = 0;
    else
        ++m_Counter;
}
//============================================================================
void CreditsScene::render()
{
    Surface * screen = Singleton<Display>::getPtr()->getSurface();
    Singleton<Display>::getPtr()->clearSurface( 0x000000 );

    m_Title->paint( screen );
    
    for ( vector< Text* >::iterator iter = m_Lines.begin(); iter != m_Lines.end(); ++iter )
        (*iter)->paint( screen );
}
//============================================================================

