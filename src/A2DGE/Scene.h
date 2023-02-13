/** 
 * @file Scene.h
 *
 * @author Rohin Knight
 * @brief Abstract class inherited by game scenes.
 */
//============================================================================
#ifndef Scene_H_
#define Scene_H_
//============================================================================
#include "Globals.h"
//============================================================================
namespace A2DGE {
//============================================================================
class Scene
{
public:
	Scene();
	virtual ~Scene();

        /* Called when the scene is set as the current scene. This gives the scene a chance to set up
           variables and/or reset things before the update function is called. */
    virtual void started(string arg) = 0;
    
        /* called when the scene needs to update (e.g. handle input, update object positions */
    virtual void update() = 0;
    
        /* called when the scene needs to be rendered (e.g. display objects, text, etc. at their current positions */
    virtual void render() = 0;
};
//============================================================================
} /* namespace A2DGE */
//============================================================================
#endif /*Scene_H_*/
//============================================================================
