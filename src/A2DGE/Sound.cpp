/** 
 * @file Sound.cpp
 *
 * @author Rohin Knight
 * @brief Plays a sound. Multiple sounds can be played at once.
 */
//============================================================================
#include "Sound.h"
//============================================================================
namespace A2DGE {
//============================================================================
Sound::Sound( Mix_Chunk * sound )
    : m_Sound( sound )
{
    
}
//============================================================================
Sound::~Sound()
{
    
}
//============================================================================
bool Sound::play()
{    
    m_Channel = Mix_PlayChannel( -1, m_Sound, 0 );
    
    return m_Channel != -1;
    
    //return Mix_PlayChannel( -1, m_Sound, 0 ) == 0;
    
    /* ) {
        string error( "Unable to play sound file: ");
        error += Mix_GetError();
        throw error;
    }*/
}
//============================================================================

/*
int getMinVolume()
{
    
}

int getMaxVolume()
{
    
}

  //TODO: Finish implementing this function
void Sound::setVolume( int volume )
{
    A2DGE_ASSERT(
        volume <= 0 && volume >= 128,
        "void setVolume( int volume )\n"
            "Invalid value for volume!\n"
            "The volume level must be a value between 0 (min), and 128 (max)"
    )
            
            
                                       
    //the volume level must be a value between 0 (minimum), and 128 (maximum). If a value of -1 is given for the volume_level, the current volume of that particular chunk is returned.
    //http://www.cs.clemson.edu/~malloy/courses/3dgames-2007/tutor/web/audio/audio.html
    
    Mix_VolumeChunk( m_Sound, volume );
}

int Sound::getVolume()
{
    return Mix_VolumeChunk( m_Sound, -1 );
}

*/

/*  //TODO: Finish implementing this function
void stop()
{
    // If -1 is specified, ALL channels are stopped!
    
    
    // We need to first find out if the sound is still being played!
    
    //if ( m_Channel != -1 )    
    Mix_HaltChannel( channel_number );
}
*/

//============================================================================
} /* namespace A2DGE */
//============================================================================
