#pragma once

#include <stdafx.h>

class Signal {

	// Function pointer that takes an Entity and returns void
	using SignalCallback = void (*)(Entity);

public:
	void Connect(SignalCallback callback);
	void Disconncet(SignalCallback callback);
	void Emit(Entity id);

private:

	// It's okay if function pointers are stored in the signal because if
	// one system is destroyed, all systems and their corresponding signals
	// are destroyed so there can't be any dangling pointers to deleted functions :D
	std::vector<SignalCallback> connections;

};