/** 
 * @file Sprite.cpp
 *
 * @author Rohin Knight
 * @brief Implementation of a Sprite object which can store multiple frame
 * sequences.
 */
//============================================================================
#include "Sprite.h"
//============================================================================
namespace A2DGE {
//============================================================================
unsigned long Sprite::default_frame_delay = 100; // 100 milliseconds.
//============================================================================
Sprite::Sprite( Surface * surface, int frameWidth, int frameHeight, unsigned long frameDelay, bool createDefaultFrameSequence, bool isSharedSurface )
    : Layer( isSharedSurface ),
      m_FrameIndex( 0 ),
      m_CurrentFrameSequence( NULL ),
      m_FRAME_WIDTH( frameWidth ),
      m_FRAME_HEIGHT( frameHeight ),
      m_PrevTicks( 0 ),
      m_FrameDelay( frameDelay )
{
/*    A2DGE_ASSERT(
        surface.isValid(),
        "Sprite::Sprite( RCPtr<Surface> surface, int frameWidth, int frameHeight, unsigned long frameDelay, bool createDefaultFrameSequence )\n"
            "Surface is NULL."
    ) */
                  
    //char msg[255];
    //sprintf( msg, "Invalid value for frame width: %d", frameWidth );
                            
    A2DGE_ASSERT( 
        surface->getWidth() % frameWidth == 0,
        "Sprite::Sprite( RCPtr<Surface> surface, int frameWidth, int frameHeight, unsigned long frameDelay, bool createDefaultFrameSequence )\n"
            "Invalid value for frame width"
    )
    
    A2DGE_ASSERT( 
        surface->getHeight() % frameHeight == 0,
        "Sprite::Sprite( RCPtr<Surface> surface, int frameWidth, int frameHeight, unsigned long frameDelay, bool createDefaultFrameSequence )\n"
            "Invalid value for frame height"
    )
    
    /*
    if ( ! surface.isValid() ) {
        throw string( "NULL surface pointer passed to Sprite constructor." );
    }
    else if ( surface->getWidth() % m_FRAME_WIDTH != 0 || surface->getHeight() % m_FRAME_HEIGHT != 0 ) {
        throw string( "Invalid frame width or height" );
    }*/
    
    m_Surface = surface;

    if ( createDefaultFrameSequence )
        createFrameSequence( "default", 0, getFrameTotal() - 1, true );
}
//============================================================================
Sprite::~Sprite()
{
    for ( map< string, vector< int > * >::iterator iter = m_FrameSequences.begin();
          iter != m_FrameSequences.end();
          ++iter )
        delete iter->second;
}
//============================================================================
void Sprite::paint( Surface * destination )
{
    if ( m_CurrentFrameSequence == NULL ) {
        throw string( "void Sprite::paint( Surface * destination )\n"
                      "No current frame sequence is set." );
    }

    if ( m_Visible ) {
        int index = (*m_CurrentFrameSequence)[ m_FrameIndex ];
        
        
        //char msg[255];
        //sprintf( msg, "index out of bounds. index value is: %d", index );
        //A2DGE_ASSERT( index < 0 || index >= getFrameTotal(), msg )
                                                       
                                                       
        A2DGE_ASSERT( index >= 0 && index < getFrameTotal(), "void Sprite::paint( Surface * destination )\n"
                                                       "Frame index out of bounds!" )
        
        int columns = m_Surface->getWidth() / m_FRAME_WIDTH;
        int row = index / columns;
        int col = index - (row * columns);
        
        SDL_Rect clip = { col * m_FRAME_WIDTH, row * m_FRAME_HEIGHT, m_FRAME_WIDTH, m_FRAME_HEIGHT };
        m_Surface->blitSurface( destination, m_XPos, m_YPos, &clip );
    }
}
//============================================================================
int Sprite::getFrameTotal()
{
    return (m_Surface->getWidth() / m_FRAME_WIDTH) * (m_Surface->getHeight() / m_FRAME_HEIGHT);
    //return frameTotal;
}
//============================================================================
/*
void Sprite::createAndSetDefaultFrameSequence()
{
    createFrameSequence( "default", 0, getFrameTotal() );
    setFrameSequence( "default" );
}*/
//============================================================================
void Sprite::createFrameSequence( string name, int first, int last, bool setAsCurrent )
{   
    vector<int> * frameSequence = new vector<int>;
    for ( int i = first; i <= last; ++i )
        frameSequence->push_back( i );
        
    addFrameSequence( name, frameSequence );
    
    if ( setAsCurrent )
        setFrameSequence( name );
}
//============================================================================
void Sprite::addFrameSequence( string name, vector< int > * sequence )
{
    if ( name == "" ) {
        string error( "void Sprite::addFrameSequence( string name, vector< int > * sequence )\n"
                      "Invalid name for frame sequence: " );
        error += name;
        throw error;
    }
    else if ( sequence == NULL ) {
        string error( "void Sprite::addFrameSequence( string name, vector< int > * sequence )\n"
                      "sequence pointer is NULL!." );
        throw error;
    }
    
    if ( m_FrameSequences[ name ] != NULL ) {
        delete m_FrameSequences[ name ];
    }
    
    m_FrameSequences[ name ] = sequence;
}
//============================================================================
void Sprite::setFrameSequence( string name )
{
    vector< int > * frameSequence = m_CurrentFrameSequence = m_FrameSequences[ name ];
    
    if ( frameSequence == NULL ) {
        string error( "void Sprite::setFrameSequence( string name )\n"
                      "Invalid frame sequence name: " );
        error += name;
        throw error;
    }
    
    
    m_FrameIndex = 0;
    m_CurrentFrameSequence = frameSequence;
    //loopCurrentFrameSequence = loop;
    
    //m_CurrentFrameRepeat = m_FrameRepeat[ name ];
}
//============================================================================
void Sprite::updateFrame( bool showNextFrame )
{    
    unsigned long newTicks = SDL_GetTicks();
    
/*    if ( m_PrevTicks == -1 )
        m_PrevTicks = newTicks; */
    
    if ( newTicks - m_PrevTicks > m_FrameDelay ) {
        m_PrevTicks = newTicks;
        
        if ( showNextFrame )
            nextFrame();
        else
            prevFrame();
    }
}
//============================================================================
void Sprite::nextFrame()
{
    if ( m_CurrentFrameSequence == NULL ) {
        string error( "void Sprite::nextFrame()\n"
                      "m_CurrentFrameSequence is NULL." );
        throw error;
    }
    
    if ( m_FrameIndex + 1 == static_cast<int>(m_CurrentFrameSequence->size()) )
        //if ( loopCurrentFrameSequence )
        m_FrameIndex = 0;
    else
        ++m_FrameIndex;
}
//============================================================================
void Sprite::prevFrame()
{
    if ( m_CurrentFrameSequence == NULL ) {
        throw string( "void Sprite::prevFrame()\n"
                      "m_CurrentFrameSequence is NULL." );
    }
    
    if ( m_FrameIndex == 0 )
        //if ( loopCurrentFrameSequence )
        m_FrameIndex = m_CurrentFrameSequence->size() - 1;
    else
        --m_FrameIndex;
}
//============================================================================
void Sprite::setFrameIndex( int index )
{
    if ( m_CurrentFrameSequence == NULL )
        throw string( "void Sprite::setFrameIndex( int index )\n"
                      "m_CurrentFrameSequence is NULL." );
    
    if ( index < 0 || index >= static_cast<int>(m_CurrentFrameSequence->size()) )
        throw string( "void Sprite::setFrameIndex( int index )\n"
                      "index outside range." );
    
    m_FrameIndex = index;
}
//============================================================================
void Sprite::addCollisionRectangle( int xOffset, int yOffset, int width, int height )
{
    SDL_Rect rect = { xOffset, yOffset, width, height };
    m_CollisionRectangles.push_back( rect );
}
//============================================================================
bool Sprite::collisionWith( Sprite * sprite, COLLISION_TEST collisionTest )
{
    if ( collisionTest == BEST_AVAILABLE ) {
        if ( hasCollisionBoxes() && sprite->hasCollisionBoxes() )        
            collisionTest = BOXES_BOXES;
        else if ( sprite->hasCollisionBoxes() )
            collisionTest = BOX_BOXES;
        else if ( hasCollisionBoxes() )
            collisionTest = BOXES_BOX;
        else
            collisionTest = BOX_BOX;
    }
            
    switch ( collisionTest ) {
    case BOX_BOX:
        return boxBoxCollisionTest( getXPos(), getXPos() + getWidth(),
                                    getYPos(), getYPos() + getHeight(),
                                    sprite->getXPos(), sprite->getXPos() + sprite->getWidth(),
                                    sprite->getYPos(), sprite->getYPos() + sprite->getHeight() );
            
    case BOX_BOXES:
        return boxBoxesCollisionTest( getXPos(), getXPos() + getWidth(),
                                      getYPos(), getYPos() + getHeight(),
                                      sprite );

    case BOXES_BOX:
        return boxBoxesCollisionTest( sprite->getXPos(),
                                      sprite->getXPos() + sprite->getWidth(),
                                      sprite->getYPos(),
                                      sprite->getYPos() + sprite->getHeight(),
                                      this );

    case BOXES_BOXES:
        for ( vector< SDL_Rect >::iterator iter = m_CollisionRectangles.begin();
              iter != m_CollisionRectangles.end();
              ++iter )
        {
            int left = getXPos() + iter->x;
            int right = left + iter->w;
            int top = getYPos() + iter->y;
            int bottom = top + iter->h;
            if ( boxBoxesCollisionTest( left, right, top, bottom, sprite ) )
                return true;
        }
        break;
        
    case BEST_AVAILABLE:  // To avoid compiler warning about "'BEST_AVAILABLE' not handled in switch"
    	break;            // We should never get here.
    }
    
    return false;
}
//============================================================================
bool Sprite::boxBoxesCollisionTest( int left_1, int right_1,
                                    int top_1, int bottom_1,
                                    Sprite * sprite )
{
    vector< SDL_Rect >::iterator iter;
    for ( iter = sprite->m_CollisionRectangles.begin(); iter != sprite->m_CollisionRectangles.end(); ++iter ) {    
        int left_2 = sprite->getXPos() + iter->x;
        int right_2 = left_2 + iter->w;
        int top_2 = sprite->getYPos() + iter->y;
        int bottom_2 = top_2 + iter->h;
        
        if ( boxBoxCollisionTest( left_1, right_1, top_1, bottom_1,
                                  left_2, right_2, top_2, bottom_2 ) )
            return true;
    }
    
    return false;
}
//============================================================================
bool Sprite::boxBoxCollisionTest( int left_1, int right_1, int top_1, int bottom_1,
                                  int left_2, int right_2, int top_2, int bottom_2 )
{
    return !(left_1 >= right_2 || right_1 <= left_2 || top_1 >= bottom_2 || bottom_1 <= top_2);
}
//============================================================================
} /* namespace A2DGE */
//============================================================================
