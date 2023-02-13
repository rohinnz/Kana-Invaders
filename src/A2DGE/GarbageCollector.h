/** 
 * @file GarbageCollector.h
 *
 * @author Rohin Knight
 * @brief Deletes resources on engine shutdown which were passed to it.
 * Used by classes which are unable (or do not want to) take care of
 * cleaning up after themselves.
 */
//============================================================================
#ifndef GarbageCollector_H_
#define GarbageCollector_H_
//============================================================================
#include "Globals.h"
#include "EngineComponent.h"
#include "Layer.h"
#include "Surface.h"
//============================================================================
namespace A2DGE {
//============================================================================
class GarbageCollector : public EngineComponent 
{
public:
	GarbageCollector();
	virtual ~GarbageCollector();
	
	virtual void initialize();
	virtual void shutdown();
	
	Layer* addLayer( Layer* layer );
	Surface* addSurface( Surface* surface );
	
private:
    vector< Layer* > m_Layers;
    vector< Surface* > m_Surfaces;
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*GARBAGECOLLECTOR_H_*/
//============================================================================
