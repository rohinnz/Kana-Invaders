/** 
 * @file InstructionScene.cpp
 *
 * @author Rohin Knight
 * @brief Displays instruction text on how to play the game.
 */
//============================================================================
#include "InstructionsScene.h"
//============================================================================
InstructionsScene::InstructionsScene()
{
    TTF_Font * fontTitle = Singleton<FontManager>::getPtr()->getFont( "SceneTitle" );
    m_Title = new Text( "Instructions", Color(111, 217, 113), fontTitle );
    m_Title->setPosition( (Singleton<Display>::getPtr()->getWidth() / 2) - (m_Title->getWidth() / 2), 20 );
    
    string line;
    const string FILENAME = "data/instructions.dat";
    ifstream in( FILENAME.c_str() );

    if ( ! in.is_open() ) {
        string error( "InstructionsScene::InstructionsScene()\n"
                      "Unable to open file " );
        error += FILENAME;
        throw error;
    }
    
    TTF_Font * fontMessage = Singleton<FontManager>::getPtr()->getFont( "NormalText" );
    int yPos = 120;    
    
    while ( ! in.eof() ) {
        getline( in, line );
        
        if ( ! line.empty() ) {  
            Text* text = new Text( line, Color(111, 217, 113), fontMessage );
            text->setPosition( 65, yPos );
            
            m_Lines.push_back( text );
        }
        
        yPos += 20;
    }
    in.close();
}
//============================================================================
InstructionsScene::~InstructionsScene()
{
    delete m_Title;
    for ( vector< Text * >::iterator iter = m_Lines.begin(); iter != m_Lines.end(); ++iter )
    	delete *iter;
}
//============================================================================
void InstructionsScene::started(string level)
{
    Singleton<Input>::getPtr()->getLastKey();  // remove last key pressed so Input::newKeyPressed() will not return true if Enter was pressed to get to this scene.
}
//============================================================================
void InstructionsScene::update()
{
    Input* input = Singleton<Input>::getPtr();
    
    if (  input->newKeyPressed() ) {
        playChangedSound();
        Singleton<SceneManager>::getPtr()->setCurrentScene( "MainMenu" );
    }
}
//============================================================================
void InstructionsScene::render()
{
    Surface * screen = Singleton<Display>::getPtr()->getSurface();
    Singleton<Display>::getPtr()->clearSurface( 0x000000 );

    m_Title->paint( screen );
    
    for ( vector< Text * >::iterator iter = m_Lines.begin(); iter != m_Lines.end(); ++iter )
        (*iter)->paint( screen );
}
//============================================================================

