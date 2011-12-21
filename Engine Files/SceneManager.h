/////////////////////////////////////////////////////////////////
//author: martin goulet
//SceneManager.h
/////////////////////////////////////////////////////////////////

#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

//includes
#include "SubComponent.h"
#include "Timer.h"
#include "EntitySet.h"
#include "SettingsSubSet.h"
#include "TextureSet.h"
#include "ModelSet.h"

class SceneManager: public SubComponent
{
public:
	SceneManager();
	~SceneManager();

	bool RenderScene(	const EntitySet& entityset_ref,
						const ModelSet& modelset_ref,
						const TextureSet& textureset_ref,
						const SettingsSubSet& sss_ref) const;

private:

	bool Init();
	bool Release();

	bool RenderEntityModels(const EntitySet& entityset_ref, const ModelSet& modelset_ref) const;
	bool RenderEntityMath(const EntitySet& entityset_ref) const;
	bool RenderMD2Frame(const CMD2Model* model_ptr) const;

	//personal timer
	Timer timer;

};


#endif SCENEMANAGER_H