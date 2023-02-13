/** 
 * @file EngineComponent.cpp
 *
 * @author Rohin Knight
 * @brief Inherited by Singleton classes which are started/stoped in the
 * engine and used throughout the game for graphics, input and sound.
 */
//============================================================================
#include "EngineComponent.h"
//============================================================================
namespace A2DGE {
//============================================================================
EngineComponent::EngineComponent()
   // : m_Initialized( false )
{
    
}
//============================================================================
EngineComponent::~EngineComponent()
{
    
}
//============================================================================
void EngineComponent::initialize()
{
    /*
    if ( Singleton<Engine>::getPtr()->isNotInInitializeMode() ) {
        throw string("Only the Engine may initialize an engine component!");
    }*/
    
    //m_Initialized = true;
}
//============================================================================
void EngineComponent::shutdown()
{
    /*
    if ( Singleton<Enine>::getPtr()->isNotInShutDownMode() ) {
        throw string("Only the Engine may shut down an engine component!");
    }*/
}
//============================================================================
} /* namespace A2DGE */
//============================================================================
