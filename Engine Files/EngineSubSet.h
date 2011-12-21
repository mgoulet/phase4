/////////////////////////////////////////////////////////////////
//Author: mg goulet
//EngineSubSet.h
/////////////////////////////////////////////////////////////////

#ifndef ENGINESUBSET_H
#define ENGINESUBSET_H

//includes
#include "SubSetDeclarations.h"
#include "SubSetDefinitions.h"

class EngineSubSet
{
	//friendship to classes
	friend class EnginePhase4;
	friend class KernelStateMachine;
	friend class GameStateMachine;

public:
	//constructors/destructor
	EngineSubSet();
	~EngineSubSet();

	//const accessors...
	const Timer& GetTimer() const;
	const InputManager& GetInputManager() const;
	const Console& GetConsole() const;
	const FPSCounter& GetFPSCounter() const;
	const EntitySet& GetEntitySet() const;
	const FontManager& GetFontManager() const;
	const TextureSet& GetTextureSet() const;
	const SkySphere& GetSkySphere() const;
	const EntityManager& GetEntityManager() const;
	const ModelSet& GetModelSet() const;
	const SceneManager& GetSceneManager() const;
	const HeadsUpDisplay& GetHeadsUpDisplay() const;
	const HeightMap& GetHeightMap() const;
	const ComplexMap& GetComplexMap() const;

private:

	//members
	Timer timer;
	InputManager inputmanager;
	Console console;
	FPSCounter fpscounter;
	FontManager fontmanager;
	EntitySet entityset;
	TextureSet textureset;
	SkySphere skysphere;
	EntityManager entitymanager;
	ModelSet modelset;
	SceneManager scenemanager;
	HeadsUpDisplay headsupdisplay;
	HeightMap heightmap;
	ComplexMap complexmap;

};

#endif ENGINESUBSET_H