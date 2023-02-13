/** 
 * @file string_functions.cpp
 *
 * @author Rohin Knight
 * @brief Tools for converting strings to integers and vice versa.
 */

// TODO: Add to A2DGE namespace

#include "string_functions.h"

string convert_int_to_string(int value) {
	string output;
	stringstream ss;
	ss << value;
	ss >> output;
	
	return output;	
}

int convert_string_to_int(string value) {
	int output;
	stringstream ss;
	ss << value;
	ss >> output;
	
	return output;	
}
