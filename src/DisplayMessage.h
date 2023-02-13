/** 
 * @file DisplayMessage.h
 *
 * @author Rohin Knight
 * @brief Displays a centered, two-line message during a level.
 */
//============================================================================
#ifndef DisplayMessage_H_
#define DisplayMessage_H_
//============================================================================
#include "A2DGE/A2DGE.h"
using namespace A2DGE;

#include "common.h"
//============================================================================
class DisplayMessage
{
public:
	DisplayMessage();
	virtual ~DisplayMessage();

    void setMessage( string message, string subMessage, bool resetTimer = true );
    void render();
    bool isDisplayTimeUp();
    //void disappear();
	
private:
    Text * m_Message;
    Text * m_SubMessage;
    Timer displayTime;
};
//============================================================================
#endif /*DisplayMessage_H_*/
//============================================================================
