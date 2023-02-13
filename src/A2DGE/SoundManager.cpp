/** 
 * @file SoundManager.cpp
 *
 * @author Rohin Knight
 * @brief Engine component for handling music and sound objects.
 */
//============================================================================
#include "SoundManager.h"
//============================================================================
namespace A2DGE {
//============================================================================    
const int SoundManager::DEFAULT_RATE = MIX_DEFAULT_FREQUENCY; //22050;
const Uint16 SoundManager::DEFAULT_FORMAT = AUDIO_S16SYS;
const int SoundManager::DEFAULT_CHANNELS = 2;
const int SoundManager::DEFAULT_BUFFER_SIZE = 1024;  //4096;
//============================================================================
SoundManager::SoundManager()
{

}
//============================================================================
SoundManager::~SoundManager()
{
    
}
//============================================================================
void SoundManager::initialize( int rate, Uint16 format, int channels, int bufferSize )
{
    if( Mix_OpenAudio( rate, format, channels, bufferSize ) != 0 ) {
        string error( "Failed to set up audio: " );
        error += SDL_GetError();
        throw error;
    }
}
//============================================================================
void SoundManager::shutdown()
{
    stopAllSounds();
    stopMusic();
    
    for ( map< string, Mix_Chunk * >::iterator iter = m_Sounds.begin(); iter != m_Sounds.end(); ++iter )
        Mix_FreeChunk( iter->second );

    for ( map< string, Mix_Music * >::iterator iter = m_Music.begin(); iter != m_Music.end(); ++iter )
        Mix_FreeMusic( iter->second );
    
    Mix_CloseAudio();
}
//============================================================================
void SoundManager::addSound( string name, string filename )
{   
    Mix_Chunk * sound = Mix_LoadWAV( filename.c_str() );
    
    if ( sound == NULL) {
	   string error( "Unable to load WAV file " );
	   error += filename;
	   error += "\n";
	   error += Mix_GetError();
       throw error;
    }
    
    if ( soundExists( name ) )  // If a sound with the same name already exists, free the old one
        Mix_FreeChunk( m_Sounds[ name ] );        
     
    m_Sounds[ name ] = sound;
}
//============================================================================
void SoundManager::addMusic( string name, string filename )
{
    Mix_Music * music = Mix_LoadMUS( filename.c_str() );
    
    if( music == NULL) {
	   string error( "Unable to load music file: " );
	   error += filename;
	   error += Mix_GetError();
       throw error;
    }
    
    if ( musicExists( name ) )  // If music with the same name already exists, free the old one
        Mix_FreeMusic( m_Music[ name ] );        
     
    m_Music[ name ] = music;
}
//============================================================================
Sound SoundManager::getSound( string name )
{
    #ifdef A2DGE_ASSERTS 
    if ( ! soundExists( name ) ) {
        string error("Sound SoundManager::getSound( string name )\n"
                     "Sound does not exist with name ");
        error += name;
        throw error;
    }    
    #endif

    return Sound( m_Sounds[ name ] );
}
//============================================================================
Music SoundManager::getMusic( string name )
{
    #ifdef A2DGE_ASSERTS 
    if ( ! musicExists( name ) ) {
        string error("Music SoundManager::getMusic( string name )\n"
                     "Music does not exist with name ");
        error += name;
        throw error;
    }    
    #endif
    
    return Music( m_Music[ name ] );
}
//============================================================================
bool SoundManager::playSound( string name )
{
    #ifdef A2DGE_ASSERTS 
    if ( ! soundExists( name ) ) {
        /*string error("bool SoundManager::playSound( string name )\n"
                     "Sound does not exist with name ");
        error += name;
        throw error; */
    }    
    #endif
    
    return Mix_PlayChannel( -1, m_Sounds[ name ], 0 ) != -1;
}
//============================================================================
void SoundManager::playMusic( string name )
{
    #ifdef A2DGE_ASSERTS 
    if ( ! musicExists( name ) ) {
        string error("void SoundManager::playMusic( string name )\n"
                     "Music does not exist with name ");
        error += name;
        throw error;
    }    
    #endif
    
    if( Mix_PlayingMusic() )
        Mix_HaltMusic();
    
    if( Mix_PlayMusic( m_Music[ name ], 1 ) != 0 ) {
        string error( "Unable to play music: ");
        error += Mix_GetError();
        throw error;
    }
}
//============================================================================
void SoundManager::stopAllSounds()
{
    Mix_HaltChannel( -1 );
}
//============================================================================
void SoundManager::stopMusic()
{
    if ( Mix_PlayingMusic() )    
        Mix_HaltMusic();
}
//============================================================================
bool SoundManager::soundExists( string name )
{
    return !( m_Sounds.find( name ) == m_Sounds.end() );
}
//============================================================================
bool SoundManager::musicExists( string name )
{
    return !( m_Music.find( name ) == m_Music.end() );
}
//============================================================================
} /* namespace A2DGE */
//============================================================================
