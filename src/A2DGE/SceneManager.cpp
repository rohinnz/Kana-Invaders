/** 
 * @file SceneManager.cpp
 *
 * @author Rohin Knight
 * @brief Engine component which holds all the game scenes and calls their
 * update and render functions when requested by the game engine.
 */
//============================================================================
#include "SceneManager.h"
//============================================================================
namespace A2DGE {
//============================================================================
SceneManager::SceneManager()
    : m_CurrentScene( NULL )
{
    
}
//============================================================================
SceneManager::~SceneManager()
{

}
//============================================================================
void SceneManager::initialize()
{
    
}
//============================================================================
void SceneManager::shutdown()
{
    map< string, Scene * >::iterator iter;
    
    for ( iter = m_Scenes.begin(); iter != m_Scenes.end(); ++iter )
        delete iter->second;
}
//============================================================================
void SceneManager::addScene( string name, Scene * scene )
{
    if ( name == "" ) {
        string error( "void SceneManager::addScene( string name, Scene * scene )\n"
                      "Invalid name for scene!" );
        throw error;
    }
    else if ( scene == NULL ) {
        string error( "void SceneManager::addScene( string name, Scene * scene )\n"
                      "scene pointer is NULL!" );
        throw error;
    }
    
    m_Scenes[ name ] = scene;
}
//============================================================================
void SceneManager::setCurrentScene( string name, string args )
{
    Scene * scene = m_Scenes[ name ];
    
    if ( scene == NULL ) {
        string error( "void SceneManager::setCurrentScene( string name )\n"
                      "Invalid scene name: " );
        error += name;
        throw error;
    }
    
    m_CurrentScene = scene;
    m_CurrentScene->started( args );
}
//============================================================================
Scene * SceneManager::getCurrentScene()
{
    if ( m_CurrentScene == NULL ) {
        string error( "Scene * SceneManager::getCurrentScene()\n"
                      "No Current scene defined!" );
        throw error;
    }

    return m_CurrentScene;
}
//============================================================================
void SceneManager::addLayer( string name, Layer * layer)
{
	m_Layers[ name ] = layer;
}
//============================================================================
Layer* SceneManager::getLayer( string name )
{
    Layer * layer = m_Layers[ name ];
    
    if ( layer == NULL ) {
        string error( "void SceneManager::getLayer( string name )\n"
                      "Invalid layer name: " );
        error += name;
        throw error;
    }
    
    return layer;
}
//============================================================================
void SceneManager::updateCurrentScene()
{
    if (m_CurrentScene != NULL)
        m_CurrentScene->update();
}
//============================================================================
void SceneManager::renderCurrentScene()
{
    if (m_CurrentScene != NULL)
        m_CurrentScene->render();
}	
//============================================================================
} /* namespace A2DGE */
//============================================================================
