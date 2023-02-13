/** 
 * @file FontManager.cpp
 *
 * @author Rohin Knight
 * @brief Handles Truetype font resources.
 */
//============================================================================
#include "FontManager.h"
//============================================================================
namespace A2DGE {
//============================================================================
FontManager::FontManager()
{

}
//============================================================================
FontManager::~FontManager()
{
    map< string, TTF_Font * >::iterator iter;
    
    for ( iter = m_Font.begin(); iter != m_Font.end(); ++iter )
        TTF_CloseFont( iter->second );
        
    TTF_Quit();
}
//============================================================================
void FontManager::initialize()
{
    if( TTF_Init() == -1 ) {
        string error( "Failed to initalize TrueType Font" );
        error += SDL_GetError();
        throw error; 
    }
}
//============================================================================
void FontManager::shutdown()
{
    
}
//============================================================================
TTF_Font * FontManager::loadFont( string name, string filename, int size )
{
    if ( name == "" )
        throw string( "TTF_Font * FontManager::loadFont( string name, string filename, int size )\n"
                      "Empty string used for font name!" );
    
    if ( m_Font[ name ] != NULL ) // Handle overwrite if name is already being used.
        TTF_CloseFont( m_Font[ name ] ); 

    TTF_Font * font = TTF_OpenFont( filename.c_str(), size );
    
    if ( font == NULL ) {
        string error( "void FontManager::loadFont( string name, string filename, int size )\n" );
        error += SDL_GetError();
        throw error;
    }
    
    m_Font[ name ] = font;
    return font;
}
//============================================================================
TTF_Font * FontManager::getFont( string name )
{
    TTF_Font * font = m_Font[ name ];
    
    if ( font == NULL ) {
        string error( "TTF_Font * FontManager::getFont( string name )\n"
                      "No such font with name " );
        error += name;
        throw error;
    }
    
    return font;
}
//============================================================================
} /* namespace A2DGE */
//============================================================================
