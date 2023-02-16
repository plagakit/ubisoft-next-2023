#pragma once

#include <stdafx.h>

#include "Scene/EntityManager/EntityManager.h"

class Scene;

class ISystem {

public:
	virtual void Update(Scene& scene) {}

};