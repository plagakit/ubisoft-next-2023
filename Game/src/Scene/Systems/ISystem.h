#pragma once

#include <stdafx.h>

#include <Scene/EntityManager/EntityManager.h>
class Scene;

class ISystem {

public:
	ISystem(Scene* s) : scene(s) {}

	virtual void Update(EntityManager& entityMgr) {}

protected:
	Scene* scene; //smart pointer not needed b/c not deleting scene upon system deletion

};