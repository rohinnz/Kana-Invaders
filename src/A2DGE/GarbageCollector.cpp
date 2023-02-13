/** 
 * @file GarbageCollector.cpp
 *
 * @author Rohin Knight
 * @brief Deletes resources on engine shutdown which were passed to it.
 * Used by classes which are unable (or do not want to) take care of
 * cleaning up after themselves.
 */
//============================================================================
#include "GarbageCollector.h"
//============================================================================
namespace A2DGE {
//============================================================================
GarbageCollector::GarbageCollector()
{
    
}
//============================================================================
GarbageCollector::~GarbageCollector()
{

}
//============================================================================
void GarbageCollector::initialize()
{
    
}
//============================================================================
void GarbageCollector::shutdown()
{
    for ( vector< Layer* >::iterator iter = m_Layers.begin(); iter != m_Layers.end(); ++iter )
        delete *iter;
        
    for ( vector< Surface* >::iterator iter = m_Surfaces.begin(); iter != m_Surfaces.end(); ++iter )
        delete *iter;
}
//============================================================================
Layer* GarbageCollector::addLayer( Layer* layer )
{
	m_Layers.push_back(layer);
	return layer;
}
//============================================================================
Surface* GarbageCollector::addSurface( Surface* surface )
{
	m_Surfaces.push_back(surface);
	return surface;
}
//============================================================================
} /* namespace A2DGE */
//============================================================================
