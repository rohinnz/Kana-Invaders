/** 
 * @file TempLevelMsg.h
 *
 * @author Rohin Knight
 * @brief A tempory message used to display an instant point win/lose message.
 */
//============================================================================
#ifndef TEMPLEVELMSG_H_
#define TEMPLEVELMSG_H_
//============================================================================
#include "A2DGE/A2DGE.h"
using namespace A2DGE;

#include "common.h"
//============================================================================
class TempLevelMsg : public Text
{
public:
	TempLevelMsg( string text, Color color, TTF_Font * font );
	virtual ~TempLevelMsg();
    
    void update();
    
private:
    int m_Timeout;
};
//============================================================================
#endif /*TEMPLEVELMSG_H_*/
//============================================================================
