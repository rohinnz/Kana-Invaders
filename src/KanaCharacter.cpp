/** 
 * @file KanaCharacter.cpp
 *
 * @author Rohin Knight
 * @brief Represents any Kana character. Used in the kana review scene and
 * level scene.
 */
//============================================================================
#include "KanaCharacter.h"
//============================================================================
const int KanaCharacter::NUM_ROMANJI = 71;
const int KanaCharacter::MAX_FRAMES = NUM_ROMANJI * 2;
const string KanaCharacter::ROMANJI[ NUM_ROMANJI ] = {
    "a", "i", "u", "e", "o",         // Levels 1 & 16
    "ka", "ki", "ku", "ke", "ko",    // Levels 2 & 17
    "sa", "shi", "su", "se", "so",   // Levels 3 & 18
    "ta", "chi", "tsu", "te", "to",  // Levels 4 & 19
    "na", "ni", "nu", "ne", "no",    // Levels 5 & 20
    "ha", "hi", "fu", "he", "ho",    // Levels 6 & 21
    "ma", "mi", "mu", "me", "mo",    // Levels 7 & 22
    "ya", "yu", "yo",                // Levels 8 & 23
    "ra", "ri", "ru", "re", "ro",    // Levels 9 & 24
    "wa", "o", "n",                  // Levels 10 & 25
    "ga", "gi", "gu", "ge", "go",    // Levels 11 & 26
    "za", "ji", "zu", "ze", "zo",    // Levels 12 & 27
    "da", "ji", "zu", "de", "do",    // Levels 13 & 28
    "ba", "bi", "bu", "be", "bo",    // Levels 14 & 29
    "pa", "pi", "pu", "pe", "po" };  // Levels 15 & 30
const int KanaCharacter::LEVEL_LIMIT[] = {
    5,    // Level 1
    10,   // Level 2
    15,   // Level 3
    20,   // Level 4
    25,   // Level 5
    30,   // Level 6
    35,   // Level 7
    38,   // Level 8
    43,   // Level 9
    46,   // Level 10
    51,   // Level 11
    56,   // Level 12
    61,   // Level 13
    66,   // Level 14
    71,   // Level 15
    76,   // Level 16
    81,   // Level 17
    86,   // Level 18
    91,   // Level 19
    96,   // Level 20
    101,  // Level 21
    106,  // Level 22
    109,  // Level 23
    114,  // Level 24
    117,  // Level 25
    122,  // Level 26
    127,  // Level 27
    132,  // Level 28
    137,  // Level 29
    142 };// Level 30
//============================================================================
KanaCharacter::KanaCharacter( int frameIndex )
    : Sprite( getKanaSurface(), 80, 80, 30, false, true )
{
    createFrameSequence( "normal", 0, 141, true );
    createFrameSequence( "destroy", 142, 149 );
    
    setFrameIndex( frameIndex );
    m_Destroyed = false;
}
//============================================================================
KanaCharacter::~KanaCharacter()
{
	
}
//============================================================================
string KanaCharacter::getRomanji()
{
    return ( getFrameIndex() >= NUM_ROMANJI ? ROMANJI[ getFrameIndex() - NUM_ROMANJI ] : ROMANJI[ getFrameIndex() ] );
}
//============================================================================
vector< KanaCharacter * > KanaCharacter::getKanaCharacters( int level )
{
    vector< KanaCharacter * > characters;
    int i = ( level == 1 ? 0 : LEVEL_LIMIT[ level - 2 ] );
    const int LIMIT = LEVEL_LIMIT[ level - 1 ];
    
    for ( ; i < LIMIT; ++i )
        characters.push_back( new KanaCharacter( i ) );
        
    return characters;
}
//============================================================================
Surface * KanaCharacter::getKanaSurface()  // class function (no destructor)
{
    static Surface* surface =
    	Singleton<GarbageCollector>::getPtr()->addSurface(  // Must use Garbage collector
    		new Surface( "data/gfx/kana_2.png", Color::BLACK )
    	);
    
    return surface;
}
//============================================================================
void KanaCharacter::setDestroyed( bool destroyed )
{    
    m_Destroyed = destroyed;
    
    if ( m_Destroyed ) {
        setFrameSequence( "destroy" );
    }
    else { 
        setFrameSequence( "normal" );
    }
}
//============================================================================
void KanaCharacter::playSound()
{
    Singleton<SoundManager>::getPtr()->playSound( getRomanji() );
}
//============================================================================
void KanaCharacter::reset()
{
    setVisible( false );
    m_Destroyed = false;
    setFrameSequence( "normal" );
}
//============================================================================
