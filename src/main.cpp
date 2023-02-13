/** 
 * @file LevelScene.cpp
 *
 * @author Rohin Knight
 * @brief loads resources, initializes and runs the game engine, and
 * handles any thrown exceptions.
 */
//============================================================================
#include <unistd.h>


// Comment this line out to turn on Game Engine asserts during development
#define DISABLE_A2DGE_ASSERTS

#include "A2DGE/A2DGE.h"
using namespace A2DGE;

#include "common.h"
#include "MainMenuScene.h"
#include "SelectLevelScene.h"
#include "InstructionsScene.h"
#include "CreditsScene.h"
#include "KanaReviewScene.h"
#include "LevelScene.h"
#include "EndGameScene.h"
//============================================================================
void outputError( string title, string message );
void loadFonts();
void loadSounds();
void loadSavedData();
void loadScenes();
//============================================================================
int main( int argc, char* args[] )
{
    try {
        //TODO: Display a splash screen
        
        Engine* engine = Singleton<Engine>::getPtr();
        engine->initialize( "Kana Invaders 0.3beta" );

        loadFonts();
        loadSounds();
    	loadSavedData();
    	loadScenes();

		//TODO: Hide splash screen here

        engine->run( Engine::CONSTANT_GAME_SPEED_INDEPENDENT_OF_VAR_FPS_GAME_LOOP );
	}
    catch ( string error ) {
        outputError( "Exception Thrown", error );
	}
    catch( exception& e ) {
        outputError( "STL Exception Thrown", e.what() );
    }
	catch (...) {
        outputError( "Unknown Exception Thrown", "An unknown exception was thrown." );
        return 1;
    }

	return 0;
}
//============================================================================
void outputError( string title, string message )
{
    cerr << title << ": " << message << endl;
    #ifdef WIN32
        MessageBox( NULL, message.c_str(), title.c_str(), 0 );
    #endif
}
//============================================================================
void loadFonts()
{
    const string FONT_DIR = "data/fonts/";
    string forgottenFuturist = FONT_DIR + "Forgotte.ttf";
    string ethnocentricrg = FONT_DIR + "ethnocentricrg.ttf";    
    string secretAgent = FONT_DIR + "HEMIHEAD.TTF";
    
    
    //string normalText = FONT_DIR + "Forgotte.ttf";

    FontManager* fontManager = Singleton<FontManager>::getPtr();
    fontManager->loadFont( "SceneTitle", ethnocentricrg, 48 );
    fontManager->loadFont( "HUD", ethnocentricrg, 12 );
        
    fontManager->loadFont( "MenuOption", forgottenFuturist, 48 );
    fontManager->loadFont( "NormalText", forgottenFuturist, 24 );
    fontManager->loadFont( "NormalSelected", forgottenFuturist, 25 );

    fontManager->loadFont( "TempMessage", secretAgent, 18 );
    
    /*
    fontManager->loadFont( "Title", ethnocentricrg, 48 );
    
    fontManager->loadFont( "Normal", secretAgent, 24 );
    fontManager->loadFont( "Selected", secretAgent, 26 );
    
    fontManager->loadFont( "Message", secretAgent, 16 );
    fontManager->loadFont( "Forgotten", forgottenFuturist, 24 );
    */
    fontManager->loadFont( "CreditsHeader", secretAgent, 36 );
    fontManager->loadFont( "CreditsText", secretAgent, 18 );
    
}
//============================================================================
void loadSounds()
{
    const string SOUND_DIR = "data/sounds/";
    SoundManager* soundManager = Singleton<SoundManager>::getPtr();

    soundManager->addSound( "pop", SOUND_DIR + "pop.wav" );
    soundManager->addSound( "explosion", SOUND_DIR + "explosion.wav" );
    soundManager->addSound( "error", SOUND_DIR + "computerbeep2.wav" );

    for ( int i = 0; i < KanaCharacter::NUM_ROMANJI; ++i ) {
        char filename[80];
        sprintf( filename, "%skana/%s.wav", SOUND_DIR.c_str(), KanaCharacter::ROMANJI[ i ].c_str() ) ;
        soundManager->addSound( KanaCharacter::ROMANJI[ i ], filename );
    }
}
//============================================================================
void loadSavedData()
{
    Repository* repository = Singleton<Repository>::getPtr();

    if ( ! repository->loadFromDisk( false ) ) { // If the repository file cannot be found we will need to create a new one
        repository->setData( "HCL", 1 ); // HCL = Highest Completed Level
        repository->saveToDisk();
    }
}
//============================================================================
void loadScenes()
{
    SceneManager* sceneManager = Singleton<SceneManager>::getPtr();

    sceneManager->addScene( "MainMenu", new MainMenuScene() );
    sceneManager->addScene( "SelectLevel", new SelectLevelScene() );
    sceneManager->addScene( "Instructions", new InstructionsScene() );
    sceneManager->addScene( "Credits", new CreditsScene() );
    sceneManager->addScene( "KanaReview", new KanaReviewScene() );
    sceneManager->addScene( "Level", new LevelScene() );
    sceneManager->addScene( "EndGame", new EndGameScene() );
    sceneManager->setCurrentScene( "MainMenu" );
}
//============================================================================
