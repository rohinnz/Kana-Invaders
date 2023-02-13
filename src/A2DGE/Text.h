/** 
 * @file Text.h
 *
 * @author Rohin Knight
 * @brief Displays True Type Font text
 */
//============================================================================
#ifndef Text_H_
#define Text_H_
//============================================================================
#include "Globals.h"
#include "Layer.h"
#include "Surface.h"
#include "Color.h"
//============================================================================
namespace A2DGE {
//============================================================================
class Text : public Layer
{
public:
	Text( string text, Color color, TTF_Font * font );
	virtual ~Text();

    string getText() { return m_Text; }
    void setText( string text );
    void setText( string text, Color color, TTF_Font * font );
    void setColor( Color color, bool update = true );
    void setFont( TTF_Font * font, bool update = true );
    virtual void paint( Surface * destination );

private:
	string m_Text;
	Color m_Color;
	TTF_Font * m_Font;
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*Text_H_*/
//============================================================================
