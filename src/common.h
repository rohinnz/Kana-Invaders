/*
    Last modified:      3, January 2008
    Author(s):          Rohin Knight  -  rohin.knight@gmail.com
*/
//============================================================================
#ifndef common_H_
#define common_H_
//============================================================================



/* Windows */
#ifdef WIN32
    #include <windows.h>
#endif

/* old c libraries */
#include <stdio.h>

/* STL */
#include <exception>
using std::exception;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <sstream>
using std::stringstream;

#include <fstream>
using std::fstream;

#include <deque>
using std::deque;

//#include <cstdlib> 

/* old c libraries */
#include <stdio.h>
#include <cstdlib> 
//#include <string>
//#include <cctype>


/* SDL */
#include <SDL/SDL.h>
//============================================================================
#endif /*common_H_*/
//============================================================================
