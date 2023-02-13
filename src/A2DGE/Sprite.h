/** 
 * @file Sprite.h
 *
 * @author Rohin Knight
 * @brief Implementation of a Sprite object which can store multiple frame
 * sequences.
 */
//============================================================================
/*

  TODO: Move the collision detection stuff up to the Layer class
  so it can be used by the Text and Image class.
 
*/
//============================================================================
#ifndef Sprite_H_
#define Sprite_H_
//============================================================================
#include "Globals.h"
#include "Layer.h"
#include "Surface.h"
#include "Assert.h"
//============================================================================
namespace A2DGE {
//============================================================================
class Sprite : public Layer
{
public:
    enum COLLISION_TEST { BOX_BOX, BOX_BOXES, BOXES_BOX, BOXES_BOXES, BEST_AVAILABLE };

	Sprite( Surface * surface, int frameWidth, int frameHeight, unsigned long frameDelay = default_frame_delay, bool createDefaultFrameSequence = true, bool isSharedSurface = false );
	virtual ~Sprite();

    virtual void paint( Surface * destination );
	int getFrameTotal();
	void createAndSetDefaultFrameSequence();
	void createFrameSequence( string name, int start, int finish, bool setAsCurrent = false );
	void addFrameSequence( string name, vector<int> * sequence );
	void setFrameSequence( string name );
	void setFrameDelay( unsigned long frameDelay ) { m_FrameDelay = frameDelay; }
	void updateFrame( bool showNextFrame = true );
	void nextFrame();
	void prevFrame();
	void setFrameIndex( int index );
	int getFrameIndex() { return m_FrameIndex; }
	bool isLastFrame() { return m_FrameIndex + 1 == static_cast<int>(m_CurrentFrameSequence->size()); }

    virtual int getWidth() { return m_FRAME_WIDTH; }
    virtual int getHeight() { return m_FRAME_HEIGHT; }

    void addCollisionRectangle( int xOffset, int yOffset, int width, int height );
	bool collisionWith( Sprite * sprite, COLLISION_TEST collisionTest = BEST_AVAILABLE );
	bool hasCollisionBoxes() { return !(m_CollisionRectangles.empty()); }

	static void setDefaultFrameDelay( unsigned long frameDelay ) { default_frame_delay = frameDelay; }

private:
	map< string, vector< int > * > m_FrameSequences;
	int m_FrameIndex;
	vector< int > * m_CurrentFrameSequence;


	const int m_FRAME_WIDTH;
	const int m_FRAME_HEIGHT;
    unsigned long m_PrevTicks;
    unsigned long m_FrameDelay;

	vector< SDL_Rect > m_CollisionRectangles;

    //bool loopCurrentFrameSequence;

    static unsigned long default_frame_delay;

    bool boxBoxesCollisionTest( int left_1, int right_1,
                                    int top_1, int bottom_1,
                                    Sprite * sprite );
    bool boxBoxCollisionTest( int left_1, int right_1, int top_1, int bottom_1,
                          int left_2, int right_2, int top_2, int bottom_2 );
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*Sprite_H_*/
//============================================================================
