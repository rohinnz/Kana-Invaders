/** 
 * @file Sound.h
 *
 * @author Rohin Knight
 * @brief Plays a sound. Multiple sounds can be played at once.
 */
//============================================================================

//TODO: Add doxygen comments with code example

//============================================================================
#ifndef Sound_H_
#define Sound_H_
//============================================================================
#include "Globals.h"
//#include "RCObject.h"
//============================================================================
namespace A2DGE {
//============================================================================
class Sound
{
public:
	Sound( Mix_Chunk * sound );    //TODO: Create assignmet and copy constructors
	virtual ~Sound();
	
	bool play();

private:
    Mix_Chunk * m_Sound;
    int m_Channel;
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*Sound_H_*/
//============================================================================
