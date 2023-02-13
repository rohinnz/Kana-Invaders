/** 
 * @file Display.h
 *
 * @author Rohin Knight
 * @brief Holds the primary surface for rendering graphics.
 */
//============================================================================
#ifndef DISPLAY_H_
#define DISPLAY_H_
//============================================================================
#include "Globals.h"
#include "EngineComponent.h"
#include "Surface.h"
//============================================================================
namespace A2DGE {
//============================================================================
class Display : public EngineComponent
{
public:
    static const int DEFAULT_WIDTH;
    static const int DEFAULT_HEIGHT;
    static const int DEFAULT_BPP;
    static const Uint32 DEFAULT_FLAGS;
    
    Display();
	virtual ~Display();
	
	virtual void initialize( int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, int bpp = DEFAULT_BPP, Uint32 flags = DEFAULT_FLAGS );
	virtual void shutdown();
	
	void setWindowCaption( string caption );
	void clearSurface( Uint32 color );
	void swapBuffers();
	Surface* getSurface() { return m_Screen; }
	int getWidth() { return m_Width; }
	int getHeight() { return m_Height; }
	
private:
	Surface* m_Screen;
	int m_Width;
	int m_Height;
	
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*Display_H_*/
//============================================================================
