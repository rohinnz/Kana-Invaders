/** 
 * @file SoundManager.h
 *
 * @author Rohin Knight
 * @brief Engine component for handling music and sound objects.
 */
//============================================================================
#ifndef SoundManager_H_
#define SoundManager_H_
//============================================================================
#include "Globals.h"
#include "EngineComponent.h"
#include "Sound.h"
#include "Music.h"
//============================================================================
namespace A2DGE {
//============================================================================
class SoundManager : public EngineComponent
{
public:
    static const int DEFAULT_RATE;
    static const Uint16 DEFAULT_FORMAT;
    static const int DEFAULT_CHANNELS;
    static const int DEFAULT_BUFFER_SIZE;
    
    SoundManager();
    virtual ~SoundManager();
    virtual void initialize( int rate = DEFAULT_RATE, Uint16 format = DEFAULT_FORMAT, int channels = DEFAULT_CHANNELS, int bufferSize = DEFAULT_BUFFER_SIZE );
    virtual void shutdown();
    void addSound( string name, string filename );
    void addMusic( string name, string filename );
    Sound getSound( string name );
    Music getMusic( string name );
    bool playSound( string name );
    void playMusic( string name );   
    void stopAllSounds();	
    void stopMusic();
    bool soundExists( string name );
    bool musicExists( string name );
	
private:
    map< string, Mix_Chunk * > m_Sounds;
    map< string, Mix_Music * > m_Music;
	
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*SoundManager_H_*/
//============================================================================
