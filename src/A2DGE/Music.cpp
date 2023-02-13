/** 
 * @file Music.cpp
 *
 * @author Rohin Knight
 * @brief Plays music. Only one song can be played at once.
 */
//============================================================================
#include "Music.h"
//============================================================================
namespace A2DGE {
//============================================================================
Music::Music( Mix_Music * music )
    : m_Music( music )
{

}
//============================================================================
Music::~Music()
{

}
//============================================================================
void Music::play( int loop )
{
    if( Mix_PlayingMusic() )
	{
	   Mix_HaltMusic();
	}
    
    if( Mix_PlayMusic( m_Music, 1 ) != 0 ) {
        string error( "Unable to play music: ");
        error += Mix_GetError();
        throw error;
    }
}
//============================================================================
//TODO: Finish implementing this function
/* 
void Music::setVolume( int volume )
{
    // "As with the other volume management functions, this function takes in values from 0 to 128. You guess it, -1 returns the current volume of the music."
    // - http://www.cs.clemson.edu/~malloy/courses/3dgames-2007/tutor/web/audio/audio.html
    
    Mix_VolumeMusic(volume_of_music)
}
*/
//============================================================================
} /* namespace A2DGE */
//============================================================================
