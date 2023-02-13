/** 
 * @file Repository.h
 *
 * @author Rohin Knight
 * @brief Engine component representing saved game data.
 */
//============================================================================
#ifndef Repository_H_
#define Repository_H_
//============================================================================
#include "Globals.h"
#include "EngineComponent.h"
#include "Engine.h"
//============================================================================
namespace A2DGE {
//============================================================================
class Repository : public EngineComponent
{
public:
	Repository();
	virtual ~Repository();

	virtual void initialize();
	virtual void shutdown();

    void setData( string key, string data );
    void setData( string key, int data );
    string getData( string key );
    void getData( string key, string& data );
    void getData( string key, int& data );

    void setDiskFile( string filename ) { m_Filename = filename; }
    bool loadFromDisk( bool throwExceptionOnFail = true );
    void saveToDisk();

private:
    static const string DEFAULT;
    static const unsigned int MAX_STRING_LENGTH;
    string m_Filename;
    map< string, string > m_Data;
    
    void saveInteger( ofstream& out, int value );
    int loadInteger( ifstream& in );
    void saveString( ofstream& out, string text );
    string loadString( ifstream& in );

};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*Repository_H_*/
//============================================================================

