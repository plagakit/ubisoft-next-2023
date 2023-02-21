#include <stdafx.h>

#include "Signal.h"

/*
void Signal::Connect(SignalCallback callback)
{
	assert("Function already connected." && std::find(connections.begin(), connections.end(), callback) == connections.end());
	connections.push_back(callback);
}

void Signal::Disconnect(SignalCallback callback)
{
	connections.erase(std::remove(connections.begin(), connections.end(), callback), connections.end());
}
*/

void Signal::Emit()
{
	for (Delegate d : connections)
		d();
}