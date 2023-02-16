#pragma once

#include <stdafx.h>

#include "Scene/Systems/ISignalManager/ISignalManager.h"


class PhysicsSystem : public ISignalManager {

public:
	void UpdatePosition(Scene& scene);

};