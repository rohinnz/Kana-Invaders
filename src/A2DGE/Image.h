/** 
 * @file Image.h
 *
 * @author Rohin Knight
 * @brief A static image layer which can be rendered to a Surface.
 */
//============================================================================
#ifndef Image_H_
#define Image_H_
//============================================================================
#include "Globals.h"
#include "Layer.h"
#include "Surface.h"
//============================================================================
namespace A2DGE {
//============================================================================
/**
 * @brief An image that has a position, size, and can be rendered to a surface.
 * <p>
 * <h2>Overview</h2>
 * Overview...
 * <h2>Example</h2>
 * Image* background = new Image( "background.png" );
 * Image* player = new Image( new Surface( "player.png", Color::PINK );
 * player->setPosition( 50, Singleton<Display>::getPtr()->getHeight() - player->getHeight() );
 * background->paint( Singleton<Display>::getPtr()->getSurface() )
 * player->paint( Singleton<Display>::getPtr()->getSurface() )
 * </p>
 */
class Image : public Layer
{
public:
    /**
     * Creates an image with the given filename
     * @param[in] filename The image filename
     */
	Image( string filename );
    /**
     * Creates an image with the parsed surface
     * @param[in] surface The image filename
     */
	Image( Surface * surface );
    /**
     * Destructor is currently empty.
     */
	virtual ~Image();
    /**
     * Renders the image to a surface (Can render to another image or the screen)
     * @param[in] destination Surface to render the image on.
     */
    virtual void paint( Surface* destination );

private:

};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*Image_H_*/
//============================================================================
