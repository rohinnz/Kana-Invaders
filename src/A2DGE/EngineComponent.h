/** 
 * @file EngineComponent.h
 *
 * @author Rohin Knight
 * @brief Inherited by Singleton classes which are started/stoped in the
 * engine and used throughout the game for graphics, input and sound.
 */
//============================================================================
#ifndef EngineComponent_H_
#define EngineComponent_H_
//============================================================================
#include "Globals.h"
#include "Singleton.h"
//#include "Engine.h"
//============================================================================
//class Engine;
//============================================================================
namespace A2DGE {
//============================================================================
class EngineComponent
{
public:
	EngineComponent();
	virtual ~EngineComponent();
	
	virtual void initialize();
	virtual void shutdown();
	
    //bool isInitialized() { return m_Initialized; }
	
private:
    //bool m_Initialized;

};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*EngineComponent_H_*/
//============================================================================
