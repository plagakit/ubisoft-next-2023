#pragma once

#include <stdafx.h>

class Scene;

class ISignalManager {

	// Implementation of the observer pattern but for systems
	// Using messages as strings is bad practice but considering
	// the time limit and the scope of the game, it was the 
	// simplest option! 

public:
	void Connect(ISignalManager* receiver, std::string message);
	void EmitSignal(std::string message, Entity id);
	

private:

	// Holding a list of pointers is not a problem here because
	// systems won't be deleted unless the scene is deleted, in which case
	// ALL systems will be deleted and there will be no more pointers :)
	std::unordered_map<std::string, std::vector<ISignalManager*>> m_signals;

	virtual void ReceiveSignal(std::string message, Entity id);

};