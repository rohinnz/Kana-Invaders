/** 
 * @file Input.h
 *
 * @author Rohin Knight
 * @brief Engine component used to handle all input from SDL such as keyboard
 * and mouse events.
 */
//============================================================================
#ifndef Input_H_
#define Input_H_
//============================================================================
#include "Globals.h"
#include "EngineComponent.h"
#include "Singleton.h"
#include "Engine.h"
//============================================================================
namespace A2DGE {
//============================================================================
class Input : public EngineComponent
{
public:
	Input();
	virtual ~Input();

	virtual void initialize();
	virtual void shutdown();

    void update();
    bool keyDown( Uint16 key );
    bool keyPressed( Uint16 key );
    bool keyReleased( Uint16 key );
    bool newKeyPressed() { return m_NewKeyPressed; }
    Uint16 getLastKey();
    
    bool mouseMoved() { return m_MouseMoved; }
    bool leftMBDown() { return m_LeftMBDown; }
    bool rightMBDown() { return m_RightMBDown; }
    bool middleMBDown() { return m_MiddleMBDown; }
    
    int getMouseXPos() { return m_MouseXPos; }
    int getMouseYPos() {  return m_MouseYPos; }
    int getMBDownXPos() {  return m_MBDownXPos; }
    int getMBDownYPos() {  return m_MBDownYPos; }
    int getMBUpXPos() {  return m_MBUpXPos; }
    int getMBUpYPos() {  return m_MBUpYPos; }
    
    bool leftMBClicked() { return m_LeftMBClicked; }
    bool rightMBClicked() { return m_RightMBClicked; }
    bool middleMBClicked() { return m_MiddleMBClicked; } 
    
    
    bool modifierKeyDown( int keys );

    
private:   
    bool m_KeyDown[ SDLK_LAST ];	/* Array of keys that are currently being pressed */
    set<Uint16> m_KeyPressed;
    set<Uint16> m_KeyReleased;
    Uint16 m_LastKey;
    bool m_NewKeyPressed;
    
    bool m_MouseMoved;
    bool m_LeftMBDown;
    bool m_RightMBDown;                        
    bool m_MiddleMBDown;

    bool m_LeftMBClicked;
    bool m_RightMBClicked;
    bool m_MiddleMBClicked;

    int m_MouseXPos;
    int m_MouseYPos;
    int m_MBDownXPos;
    int m_MBDownYPos;
    int m_MBUpXPos;
    int m_MBUpYPos;
                        
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*Input_H_*/
//============================================================================
