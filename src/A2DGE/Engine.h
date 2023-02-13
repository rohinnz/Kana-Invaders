/** 
 * @file Engine.h
 *
 * @author Rohin Knight
 * @brief Runs the game loop with update and render function calls.
 * Also starts/stops engine components like Display, Input, Soundmanger, etc.
 */
//============================================================================
#ifndef Engine_H_
#define Engine_H_
//============================================================================
#include "Globals.h"
//============================================================================
#include "Singleton.h"
#include "Display.h"
#include "Input.h"
#include "SceneManager.h"
#include "FontManager.h"
#include "SoundManager.h"
#include "Repository.h"
#include "GarbageCollector.h"
//============================================================================
namespace A2DGE {
//============================================================================
class EngineComponent;
class Display;
class Input;
class SceneManager;
class FontManager;
class SoundManager;
class Repository;
//============================================================================
class Engine
{
public:
    enum GAME_LOOP { 
        SIMPLE_GAME_LOOP,
        FPS_DEPENDENT_ON_CONSTANT_GAME_SPEED_GAME_LOOP,
        CONSTANT_GAME_SPEED_WITH_MAX_FPS_GAME_LOOP,
        CONSTANT_GAME_SPEED_INDEPENDENT_OF_VAR_FPS_GAME_LOOP };
    
	Engine();
	virtual ~Engine();
	
    void initialize( string windowCaption );
    void run( GAME_LOOP gameLoop );
	void quit() { m_GameLoopRunning = false; }
	
	double getInterpolation() { return m_Interpolation; }
	
	bool isNotInInitializeMode() { return false; }
	bool isNotInShutDownMode() { return false; }
	
	
	
private:	
    bool m_GameLoopRunning;
    double m_Interpolation;
    
    Display * m_Display;     
	Input * m_Input;
    SceneManager * m_SceneManager;
    FontManager * m_FontManager;
    SoundManager * m_SoundManager;
    Repository * m_Repository;
    GarbageCollector * m_GarbageCollector;

    void Simple_GameLoop();
    void FPSDOCGS_GameLoop();
    void CGSWMFPS_GameLoop();
    void CGSIOVFPS_GameLoop();

	void update();
	void render();
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*Engine_H_*/
//============================================================================
