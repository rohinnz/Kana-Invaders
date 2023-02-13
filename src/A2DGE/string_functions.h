/** 
 * @file string_functions.h
 *
 * @author Rohin Knight
 * @brief Tools for converting strings to integers and vice versa.
 */

#ifndef STRING_FUNCTIONS_H_
#define STRING_FUNCTIONS_H_

#include <string>
using std::string;
#include <sstream>
using std::stringstream;

string convert_int_to_string(int value);
int convert_string_to_int(string value);

#endif /*STRING_FUNCTIONS_H_*/
