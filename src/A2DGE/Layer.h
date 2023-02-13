/** 
 * @file Layer.h
 *
 * @author Rohin Knight
 * @brief Abstract class inherited by graphic classes like Spire, Image and
 * Text
 */
//============================================================================
#ifndef Layer_H_
#define Layer_H_
//============================================================================
#include "Surface.h"
//============================================================================
namespace A2DGE {
//============================================================================
class Layer
{
public:
	Layer( bool isSharedSurface = false );
    Layer( int xPos, int yPos, bool isSharedSurface = false );
	virtual ~Layer();
	
	virtual void paint( Surface * destination ) = 0;
	void setPosition( int x, int y ) { m_XPos = x; m_YPos = y; }
	void move( int dx, int dy ) { m_XPos += dx; m_YPos += dy; }

	void setXPos( int x ) { m_XPos = x; }
	void setYPos( int y ) { m_YPos = y; }    
	int getXPos() { return m_XPos; }
	int getYPos() { return m_YPos; }
	void setVisible( bool visible ) { m_Visible = visible; }
	bool isVisible() { return m_Visible; }
	
    virtual int getWidth() { return m_Surface->getWidth(); }
    virtual int getHeight() { return m_Surface->getHeight(); }
	
protected:
	Surface * m_Surface;
	bool m_Visible;
	int m_XPos;
	int m_YPos;
	bool m_IsSharedSurface;
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*Layer_H_*/
//============================================================================
