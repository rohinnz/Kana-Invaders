/*
    Filename:           Assert.h
    Last modified:      3, January 2008
    Author(s):          Rohin Knight    -   rohin.knight@gmail.com
      
    A custom assert which will throw a STL string containing a parsed error 
    message if the condition is false.
*/
//============================================================================

//TODO: Add doxygen comments with code example

//============================================================================
#ifndef Assert_H_
#define Assert_H_
//============================================================================
namespace A2DGE {
//============================================================================
#ifdef DISABLE_A2DGE_ASSERTS
    #define A2DGE_ASSERT(c, s)

#else
    #define A2DGE_ASSERT(c, s) \
        if ( !(c) ) { \
            string error( "Assert Failed\n" ); \
            error += s; \
            throw error; \
        } \

    #define A2DGE_ASSERTS
      
#endif
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*Assert_H_*/
//============================================================================
