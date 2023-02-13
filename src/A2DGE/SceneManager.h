/** 
 * @file SceneManager.h
 *
 * @author Rohin Knight
 * @brief Engine component which holds all the game scenes and calls their
 * update and render functions when requested by the game engine.
 */
//============================================================================
#ifndef SceneManager_H_
#define SceneManager_H_
//============================================================================
#include "Globals.h"
#include "EngineComponent.h"
#include "Scene.h"
#include "Layer.h"
//============================================================================
namespace A2DGE {
//============================================================================
class SceneManager : public EngineComponent
{
public:
	SceneManager();
	virtual ~SceneManager();

	virtual void initialize();
	virtual void shutdown();

	void addScene( string name, Scene * scene );
	Scene * getScene( string name ) { return m_Scenes[ name ]; }
	void setCurrentScene( string name, string arg = "" );
	void updateCurrentScene();
	void renderCurrentScene();
	
	Scene * getCurrentScene();
	
	void addLayer( string name, Layer * layer);
	Layer* getLayer( string name );
	
private:
    map< string, Scene * > m_Scenes;
    map< string, Layer * > m_Layers;
    Scene * m_CurrentScene;
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*SceneManager_H_*/
//============================================================================
