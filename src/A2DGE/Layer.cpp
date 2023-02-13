/** 
 * @file Layer.cpp
 *
 * @author Rohin Knight
 * @brief Abstract class inherited by graphic classes like Spire, Image and
 * Text
 */
//============================================================================
#include "Layer.h"
//============================================================================
namespace A2DGE {
//============================================================================
Layer::Layer( bool isSharedSurface )
    : m_Visible( true ),
      m_XPos( 0 ),
      m_YPos( 0 ),
      m_IsSharedSurface( isSharedSurface )
{

}
//============================================================================
Layer::Layer( int xPos, int yPos, bool isSharedSurface )
    : m_Visible( true ),
      m_XPos( xPos ),
      m_YPos( yPos ),
      m_IsSharedSurface( isSharedSurface )
{

}
//============================================================================
Layer::~Layer()
{	
	if (! m_IsSharedSurface) {
		delete m_Surface;		
	}
}
//============================================================================
} /* namespace A2DGE */
//============================================================================
