/** 
 * @file Engine.cpp
 *
 * @author Rohin Knight
 * @brief Runs the game loop with update and render function calls.
 * Also starts/stops engine components like Display, Input, Soundmanger, etc.
 */
//============================================================================
#include "Engine.h"
//============================================================================
namespace A2DGE {
//============================================================================
Engine::Engine()
{    
    m_Display = Singleton<Display>::getPtr(); 
    m_Input = Singleton<Input>::getPtr();           
    m_SceneManager = Singleton<SceneManager>::getPtr();
    m_FontManager = Singleton<FontManager>::getPtr();
    m_SoundManager = Singleton<SoundManager>::getPtr();
    m_Repository = Singleton<Repository>::getPtr();
    m_GarbageCollector = Singleton<GarbageCollector>::getPtr();
}
//============================================================================
Engine::~Engine()
{
    m_Display->shutdown();
    m_Input->shutdown();
    m_SceneManager->shutdown();
    m_FontManager->shutdown();
    m_SoundManager->shutdown();
    m_Repository->shutdown();
    m_GarbageCollector->shutdown();
    
    SDL_Quit();
}
//============================================================================
void Engine::initialize( string windowCaption  /*, other options to be added... */ ) //TODO: Add other arguments
{    
	/* -----------------------
	 * INITIALIZE FLAG OPTIONS
	 * -----------------------
	 * SDL_INIT_TIMER   	Initializes the timer subsystem.
	 * SDL_INIT_AUDIO 	Initializes the audio subsystem.
	 * SDL_INIT_VIDEO 	Initializes the video subsystem.
	 * SDL_INIT_CDROM 	Initializes the cdrom subsystem.
	 * SDL_INIT_JOYSTICK 	Initializes the joystick subsystem.
	 * SDL_INIT_EVERYTHING 	Initialize all of the above.
	 * SDL_INIT_NOPARACHUTE 	Prevents SDL from catching fatal signals.
	 * SDL_INIT_EVENTTHREAD 	 
	 */	 
    if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) ) {
        string error( "SDL could not be initialized: " );
        error += SDL_GetError();
        throw error;
    }
    
    m_GarbageCollector->initialize();
    m_Display->initialize( 640, 480 );    
    m_Input->initialize();
    m_SceneManager->initialize();
    m_FontManager->initialize();
    m_SoundManager->initialize();
    m_Repository->initialize();
    
    m_Display->setWindowCaption( windowCaption );
}
//============================================================================
void Engine::run( GAME_LOOP gameLoop )
{
    switch ( gameLoop ) {
        case SIMPLE_GAME_LOOP:      
            Simple_GameLoop();
            break;        
    
        case FPS_DEPENDENT_ON_CONSTANT_GAME_SPEED_GAME_LOOP:
            FPSDOCGS_GameLoop();
            break;
            
        case CONSTANT_GAME_SPEED_WITH_MAX_FPS_GAME_LOOP:
            CGSWMFPS_GameLoop();
            break;
        
        case CONSTANT_GAME_SPEED_INDEPENDENT_OF_VAR_FPS_GAME_LOOP:
            CGSIOVFPS_GameLoop(); 
            break;
    
        default:                      
            throw string("Unknown game loop.");
    }
}
//============================================================================
//
// The most basic game loop - Definitely not recommended!!!!
// http://dewitters.koonsolo.com/gameloop.html
//
void Engine::Simple_GameLoop()
{
    m_GameLoopRunning = true;
    while( m_GameLoopRunning ) {
        update();
        render();
    }
}
//============================================================================
//
// FPS dependent on Constant Game Speed
// http://dewitters.koonsolo.com/gameloop.html
//
void Engine::FPSDOCGS_GameLoop()
{
    const int FRAMES_PER_SECOND = 45;
    const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

    unsigned long next_game_tick = SDL_GetTicks();
    unsigned int sleep_time = 0;

    m_GameLoopRunning = true;
    while( m_GameLoopRunning ) {
        update();
        render();

        next_game_tick += SKIP_TICKS;
        sleep_time = next_game_tick - SDL_GetTicks();
        if( sleep_time >= 0 ) {
            SDL_Delay( sleep_time / 1000 );
        }
        else {
            // We are running behind!
        }
    }
}
//============================================================================
//
// Constant Game Speed with Maximum FPS
// http://dewitters.koonsolo.com/gameloop.html
//
void Engine::CGSWMFPS_GameLoop()
{    
    const int TICKS_PER_SECOND = 50;
    const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    const int MAX_FRAMESKIP = 10;
        
    unsigned long next_game_tick = SDL_GetTicks();
    int loops;
    
    m_GameLoopRunning = true;
    while( m_GameLoopRunning ) {

        loops = 0;
        while( SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP) {
            update();
            
            next_game_tick += SKIP_TICKS;
            loops++;
        }
        
        render();
    }
}
//============================================================================
//
// Constant Game Speed independent of Variable FPS Game Loop 
// http://dewitters.koonsolo.com/gameloop.html
//
void Engine::CGSIOVFPS_GameLoop()
{
	const int TICKS_PER_SECOND = 50;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 5;
	
    unsigned long next_game_tick = SDL_GetTicks();
    int loops;

    m_GameLoopRunning = true;
    while( m_GameLoopRunning ) {
        
        loops = 0;
        while( SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP ) {
            
        	update();
            next_game_tick += SKIP_TICKS;
            loops++;
        }

        m_Interpolation = double( SDL_GetTicks() + SKIP_TICKS - next_game_tick ) / double( SKIP_TICKS );
        render();
    }    
}
//============================================================================
void Engine::update()
{
    m_Input->update();  // handle input
    m_SceneManager->updateCurrentScene();
}
//============================================================================
void Engine::render()
{
    m_SceneManager->renderCurrentScene();
    m_Display->swapBuffers();
}
//============================================================================
} /* namespace A2DGE */
//============================================================================
