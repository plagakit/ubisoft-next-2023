#pragma once

#include <stdafx.h>

class Scene;

class ISystem {

public:
	ISystem(Scene* s) : scene(s) {}

	virtual void Update(Scene& scene) {}

protected:
	Scene* scene; //smart pointer not needed b/c not deleting scene upon system deletion

};