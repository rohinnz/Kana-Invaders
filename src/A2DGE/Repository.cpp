/** 
 * @file Repository.cpp
 *
 * @author Rohin Knight
 * @brief Engine component representing saved game data.
 */
//============================================================================
#include "Repository.h"
//============================================================================
namespace A2DGE {
//============================================================================
const string Repository::DEFAULT( "data/repository.dat" );
const unsigned int Repository::MAX_STRING_LENGTH = 10000;
//============================================================================
Repository::Repository()
    : m_Filename( DEFAULT )
{
    
}
//============================================================================
Repository::~Repository()
{
    
}
//============================================================================
void Repository::initialize()
{
    
}
//============================================================================
void Repository::shutdown()
{
    
}
//============================================================================
void Repository::setData( string key, string data )
{
    m_Data[ key ] = data;
}
//============================================================================
void Repository::setData( string key, int data )
{
    char strValue[14];
    sprintf( strValue, "%d", data );
    
    m_Data[ key ] = strValue;
}
//============================================================================
string Repository::getData( string key )
{
    return m_Data[ key ];

}
//============================================================================
void Repository::getData( string key, string& data )
{
    data = m_Data[ key ];
}
//============================================================================
void Repository::getData( string key, int& data )
{
    string rawData = m_Data[ key ];
    
    if ( rawData.empty() ) {
        data = 0;
    }
    else {
        stringstream s;    
        s << rawData;
        s >> data;
    }
}
//============================================================================
bool Repository::loadFromDisk( bool throwExceptionOnFail )
{
    ifstream in( m_Filename.c_str(), ios::binary );

    if ( ! in.is_open() ) {
        if ( ! throwExceptionOnFail )
            return false;
        
        string error( "void Repositry::loadFromDisk()\n"
                      "Unable to open " );
        error += m_Filename;
        throw error;
    }
    
    const int SIZE = loadInteger( in );
    
    if ( ! m_Data.empty() )
        m_Data.erase( m_Data.begin(), m_Data.end() );
    
    for ( int i = 0; i < SIZE; ++i ) {        
        string key = loadString( in );
        string data = loadString( in );
        m_Data[ key ] = data;
    }
    
    return true;
}
//============================================================================
void Repository::saveToDisk()
{
    ofstream out( m_Filename.c_str(), ios::binary | ios::trunc );

    if ( ! out.is_open() ) {
        string error( "void Repositry::saveToDisk()\n"
                      "could not save " );
        error += m_Filename;
        throw error;
    }
    
    saveInteger( out, m_Data.size() );
    
    for ( map<string, string>::iterator iter = m_Data.begin(); iter != m_Data.end(); ++iter ) {
        saveString( out, iter->first );
        saveString( out, iter->second );
    }
}
//============================================================================
void Repository::saveInteger( ofstream& out, int value )
{
    out.write((char*)&value, sizeof(value));
}
//============================================================================
int Repository::loadInteger( ifstream& in )
{
    int value;
    in.read((char*)&value, sizeof(value));
    return value;
}
//============================================================================
void Repository::saveString( ofstream& out, string text )
{
    if ( text.size() > MAX_STRING_LENGTH ) {
        char msg[500];
        sprintf( msg, 
            "void Repository::saveString( ofstream& out, string text )\n"
                "string length is greater than %d", MAX_STRING_LENGTH );
                
        throw string( msg );
    }
    
    unsigned int size = text.size();
    char* chText = new char[ size + 1 ];
    strcpy( chText, text.c_str() );
    out.write((char*)&size, sizeof(size));
    out.write((char*)chText, size * sizeof(char) );
    delete[] chText;
}
//============================================================================
string Repository::loadString( ifstream& in )
{
    unsigned int size;
    in.read((char*)&size, sizeof(size));

    if ( size > MAX_STRING_LENGTH ) {
        char msg[500];
        sprintf( msg, 
            "string Repository::loadString( ifstream& in )\n"
                "string length is greater than %d\n"
                "%s may be corrupt!", MAX_STRING_LENGTH, m_Filename.c_str() );
                
        throw string( msg );
    }

    char* chText = new char[ size + 1 ];
    in.read((char*)chText, size * sizeof(char) );

    chText[ size ] = '\0';

    string text( chText );
    delete[] chText;

    return text;
}
//============================================================================
} /* namespace A2DGE */
//============================================================================
