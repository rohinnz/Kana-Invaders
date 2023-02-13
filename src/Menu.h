/** 
 * @file Menu.h
 *
 * @author Rohin Knight
 * @brief Inherited by scene classes with common functionality.
 */
//============================================================================
#ifndef Menu_H_
#define Menu_H_
//============================================================================
#include "A2DGE/A2DGE.h"
using namespace A2DGE;
//#include "common.h"
//============================================================================
class Menu
{
public:
	Menu();
	virtual ~Menu();

    void highlightText( Text* text, bool highlight );
    void playChangedSound();
    
};
//============================================================================
#endif /*Menu_H_*/
//============================================================================

