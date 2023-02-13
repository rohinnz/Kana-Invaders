/** 
 * @file KanaReviewScene.cpp
 *
 * @author Rohin Knight
 * @brief Scene to review new Kana characters before starting a level.
 */
//============================================================================
#include "KanaReviewScene.h"
//============================================================================
KanaReviewScene::KanaReviewScene()
    : m_StartlevelSelected( true ),
      m_Index( 0 )
{
    TTF_Font * fontTitle = Singleton<FontManager>::getPtr()->getFont( "SceneTitle" );
    m_Title = new Text( "Level 00", Color(111, 217, 113), fontTitle );
    m_Title->setPosition( (Singleton<Display>::getPtr()->getWidth() / 2) - (m_Title->getWidth() / 2), 20 );

    TTF_Font * fontNormalText = Singleton<FontManager>::getPtr()->getFont( "NormalText" );
    
    m_Message_1 = new Text( "Try and memorize each character's romanji text before starting the level.", Color(111, 217, 113), fontNormalText );
    m_Message_2 = new Text( "Select the romanji text to hear how it is pronounced.", Color(111, 217, 113), fontNormalText );
    m_Message_1->setPosition( 30, 100 );
    m_Message_2->setPosition( 30, 125 );
    
    m_Level30_Message = new Text( "The Kana are now dangerously close to Earth! You must stop them!", Color::RED, fontNormalText );
    m_Level30_Message->setPosition( (Singleton<Display>::getPtr()->getWidth() / 2) - (m_Level30_Message->getWidth() / 2), 155 );
    
    //TTF_Font * fontNormal = Singleton<FontManager>::getPtr()->getFont( "Normal" );
    m_StartLevel = new Text( "Start Level", Color(111, 217, 113), fontNormalText );
    m_StartLevel->setPosition( Singleton<Display>::getPtr()->getWidth() - m_StartLevel->getWidth() - 24,
        Singleton<Display>::getPtr()->getHeight() - m_StartLevel->getHeight() - 14 );
        
    //m_ExampleSound = new Sound( "sound/kana/be.wav" );
}
//============================================================================
KanaReviewScene::~KanaReviewScene()
{
    delete m_Title;
    delete m_Message_1;
    delete m_Message_2;
    delete m_Level30_Message;
    delete m_StartLevel;
        
    for ( vector< KanaCharacter * >::iterator iter = m_KanaCharacters.begin(); iter != m_KanaCharacters.end(); ++iter )
   		delete *iter;  

    for ( vector< Text * >::iterator iter = m_Romanji.begin(); iter != m_Romanji.end(); ++iter )
   		delete *iter; 
}
//============================================================================
void KanaReviewScene::started(string level)
{	
    m_Level = convert_string_to_int(level);
    
    int hcl;
    Repository* repository = Singleton<Repository>::getPtr();
    repository->getData( "HCL", hcl );
    
    if ( m_Level > hcl ) {  // Bump the HCL (Highest completed level) variable if user has advanced to the next level
        repository->setData( "HCL", m_Level );
        repository->saveToDisk();
    }
    
    setKanaCharacters();
    
    char title[10];    
    sprintf( title, "Level %s", level.c_str() );
    m_Title->setText( title );
    
    highlightSelection( false );  
    m_Index = 0;     
    m_StartlevelSelected = true;
    highlightSelection( true );
}
//============================================================================
void KanaReviewScene::update()
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
            
            m_StartlevelSelected = ( index == static_cast<int>(m_Romanji.size()) );
            
            if ( ! m_StartlevelSelected )
                m_Index = index;
            
            highlightSelection( true );
        }
    }
    
    if ( input->keyPressed( SDLK_UP ) ) { 
        highlightSelection( false );
        m_StartlevelSelected = ! m_StartlevelSelected;
        highlightSelection( true );
    }
    else if ( input->keyPressed( SDLK_DOWN ) ) {
        highlightSelection( false );
        m_StartlevelSelected = ! m_StartlevelSelected;
        highlightSelection( true );
    }
    else if ( input->keyPressed( SDLK_LEFT ) ) {
        highlightSelection( false );
        
        if ( ! m_StartlevelSelected ) {
            if ( m_Index == 0 )
                m_Index = m_Romanji.size() - 1;
            else
                --m_Index;
        }
        
        highlightSelection( true );
    }
    else if ( input->keyPressed( SDLK_RIGHT ) ) {
        highlightSelection( false );
        
        if ( ! m_StartlevelSelected ) {
            if ( m_Index + 1 == static_cast<int>(m_Romanji.size()) )
                m_Index = 0;
            else
                ++m_Index;
        }
        
        highlightSelection( true );
    }
    else if ( input->keyPressed( SDLK_RETURN ) ) { 
        selectHighlightedOption();
    }
    else if ( input->keyPressed( SDLK_ESCAPE ) ) {
        playChangedSound();
        Singleton<SceneManager>::getPtr()->setCurrentScene( "SelectLevel", convert_int_to_string(m_Level));
    }

}
//============================================================================
void KanaReviewScene::render()
{
    Surface * screen = Singleton<Display>::getPtr()->getSurface();
    Singleton<Display>::getPtr()->clearSurface( 0x000000 );

    //TODO: display scrolling background of stars
    

    m_Title->paint( screen );
    
    if ( m_Level == 30 )   //TODO: Replace 30 with a constant from the Level Scene.
        m_Level30_Message->paint( screen );
        
    m_Message_1->paint( screen );
    m_Message_2->paint( screen );
    
    m_StartLevel->paint( screen );
    
    for ( int i = 0; i < static_cast<int>(m_KanaCharacters.size()); ++i ) {
        m_KanaCharacters[ i ]->paint( screen );
        m_Romanji[ i ]->paint( screen );
    }
}
//============================================================================
void KanaReviewScene::setKanaCharacters()
{
    // Clean up old objects
    
    if (! m_KanaCharacters.empty()) {
    	for ( vector< KanaCharacter * >::iterator iter = m_KanaCharacters.begin(); iter != m_KanaCharacters.end(); ++iter )
   			delete *iter;
    
    	for ( vector< Text * >::iterator iter = m_Romanji.begin(); iter != m_Romanji.end(); ++iter )
   			delete *iter;
    }
    
    // get new objects
    m_KanaCharacters = KanaCharacter::getKanaCharacters( m_Level );

    m_Romanji.clear();
    //TTF_Font * font = Singleton<FontManager>::getPtr()->getFont( "Kana" );
    TTF_Font * font = Singleton<FontManager>::getPtr()->getFont( "NormalText" );
    
    static const int CHARACTER_SPACING = 45;
    int xPos = 
        (Singleton<Display>::getPtr()->getWidth() / 2) -
        (((m_KanaCharacters.size() - 1) * (m_KanaCharacters[ 0 ]->getWidth() + CHARACTER_SPACING)
        + m_KanaCharacters[ 0 ]->getWidth()) / 2); // Ensure the characters are centered.
        
    for ( vector< KanaCharacter * >::iterator iter = m_KanaCharacters.begin(); iter != m_KanaCharacters.end(); ++iter )
    {
        (*iter)->setPosition( xPos, 200 );        
        Text * text = new Text( (*iter)->getRomanji(), Color(111, 217, 113), font );
        text->setPosition( xPos + ((*iter)->getWidth() / 2) - (text->getWidth() / 2), 200 + (*iter)->getHeight() );
        m_Romanji.push_back( text );
        
        xPos += (*iter)->getWidth() + CHARACTER_SPACING;
    }
}
//============================================================================
void KanaReviewScene::highlightSelection( bool highlight )
{
    if ( m_StartlevelSelected )
        highlightText( m_StartLevel, highlight );
    else {
        
         /* Bugfix: After highlighting the 4th or 5th romanji text, 
            when you tried to view the Kana Review Scene for a level 
            with 3 characters instead of 5, a runtime exception would be thrown.
            This if statement should fix this problem. */
        if ( m_Index < static_cast<int>(m_KanaCharacters.size()) ) 
            highlightText( m_Romanji[ m_Index ], highlight );
    }
}
//============================================================================
void KanaReviewScene::selectHighlightedOption()
{
        if ( m_StartlevelSelected ) {
            playChangedSound();
            //dynamic_cast<LevelScene*>( Singleton<SceneManager>::getPtr()->getScene( "Level" ) )->setLevel( m_Level );
            Singleton<SceneManager>::getPtr()->setCurrentScene( "Level", convert_int_to_string(m_Level));
        }
        else {
            m_KanaCharacters[ m_Index ]->playSound();
        }        
}
//============================================================================
int KanaReviewScene::getHighlightedOptionIndex()
{
    Input* input = Singleton<Input>::getPtr();
    int index = 0;
       
    if ( input->getMouseXPos() > m_StartLevel->getXPos() && 
         input->getMouseXPos() < m_StartLevel->getXPos() + m_StartLevel->getWidth() &&
         input->getMouseYPos() > m_StartLevel->getYPos() &&
         input->getMouseYPos() < m_StartLevel->getYPos() + m_StartLevel->getHeight() )
    {
        return m_Romanji.size();
    }
        
    for ( vector< Text * >::iterator iter = m_Romanji.begin(); iter != m_Romanji.end(); ++iter ) {
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
