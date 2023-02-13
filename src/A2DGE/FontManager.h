/** 
 * @file FontManager.h
 *
 * @author Rohin Knight
 * @brief Handles Truetype font resources.
 */
//============================================================================
#ifndef FontManager_H_
#define FontManager_H_
//============================================================================
#include "Globals.h"
#include "EngineComponent.h"
//============================================================================
namespace A2DGE {
//============================================================================
class FontManager : public EngineComponent
{
public:
	FontManager();
	virtual ~FontManager();

	virtual void initialize();
	virtual void shutdown();

	TTF_Font * loadFont( string name, string filename, int size );
	TTF_Font * getFont( string name );
	//TTF_Font * getFont( string filename, int size );
	
private:
    map< string, TTF_Font * > m_Font;
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*FontManager_H_*/
//============================================================================
