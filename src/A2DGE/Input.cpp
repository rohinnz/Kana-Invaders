/** 
 * @file Input.cpp
 *
 * @author Rohin Knight
 * @brief Engine component used to handle all input from SDL such as keyboard
 * and mouse events.
 */
//============================================================================
#include "Input.h"
//============================================================================
namespace A2DGE {
//============================================================================
Input::Input()
{
    for ( int i = 0; i < SDLK_LAST; ++i ) m_KeyDown[ i ] = false;

    m_MouseMoved = false;    
    m_LeftMBDown = false;
    m_RightMBDown = false;                        
    m_MiddleMBDown = false;
    m_MouseXPos = 0;
    m_MouseYPos = 0;
    m_MBDownXPos = 0;
    m_MBDownYPos = 0;
    m_MBUpXPos = 0;
    m_MBUpYPos = 0;
}
//============================================================================
Input::~Input()
{
    
}
//============================================================================
void Input::initialize()
{
    SDL_EnableUNICODE( SDL_ENABLE );
}
//============================================================================
void Input::shutdown()
{
    
}
//============================================================================
void Input::update()
{
    m_KeyPressed.clear();
    m_KeyReleased.clear();
    m_LeftMBClicked = false;
    m_RightMBClicked = false;
    m_MiddleMBClicked = false;
	m_MouseMoved = false;
	
	SDL_Event event;
	while( SDL_PollEvent( &event ) ) {
        switch ( event.type ) {                   
            case SDL_KEYDOWN:
                m_KeyDown[ event.key.keysym.sym ] = true;
                m_KeyPressed.insert( event.key.keysym.sym );
                m_LastKey = event.key.keysym.unicode;
                m_NewKeyPressed = true;
                break;
                
            case SDL_KEYUP:
                m_KeyDown[ event.key.keysym.sym ] = false;
                m_KeyReleased.insert( event.key.keysym.sym );
                break;
                
            case SDL_MOUSEMOTION:
                m_MouseXPos = event.motion.x;
                m_MouseYPos = event.motion.y;
                m_MouseMoved = true;
                break;
                
            case SDL_MOUSEBUTTONDOWN:
                m_MBDownXPos = event.button.x;
                m_MBDownYPos = event.button.y;
                
                switch ( event.button.button ) {
                    case SDL_BUTTON_LEFT:
                        m_LeftMBDown = true;
                        break;
                        
                    case SDL_BUTTON_RIGHT:
                        m_RightMBDown = true;
                        break;
                        
                    case SDL_BUTTON_MIDDLE:
                        m_MiddleMBDown = true;
                        break;
                }
                break;
                
            case SDL_MOUSEBUTTONUP:                
                m_MBUpXPos = event.button.x;
                m_MBUpYPos = event.button.y;
                
                switch ( event.button.button ) {
                    case SDL_BUTTON_LEFT:
                        m_LeftMBDown = false;
                        m_LeftMBClicked = true;
                        break;
                        
                    case SDL_BUTTON_RIGHT:
                        m_RightMBDown = false;
                        m_RightMBClicked = true;
                        break;
                        
                    case SDL_BUTTON_MIDDLE:
                        m_MiddleMBDown = false;
                        m_MiddleMBClicked = true;
                        break;
                }
                break;

            case SDL_ACTIVEEVENT:
                //TODO: Add code for when window gets minimized, etc.
                break;
            
            case SDL_QUIT:
                Singleton<Engine>::getPtr()->quit();
                break;
        }
    }
}
//============================================================================
bool Input::keyDown( Uint16 key )
{
    return m_KeyDown[ key ];
}
//============================================================================
bool Input::keyPressed( Uint16 key )
{
    return !(m_KeyPressed.find( key ) == m_KeyPressed.end());
}
//============================================================================
bool Input::keyReleased( Uint16 key )
{
    return !(m_KeyReleased.find( key ) == m_KeyReleased.end());
}
//============================================================================
Uint16 Input::getLastKey()
{
    m_NewKeyPressed = false;
    return m_LastKey;
}
//============================================================================
bool Input::modifierKeyDown( int key )
{
    return (SDL_GetModState() & key) != 0;
}
//============================================================================
} /* namespace A2DGE */
//============================================================================
