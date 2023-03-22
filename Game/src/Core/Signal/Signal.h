#pragma once

#include <stdafx.h>

#include "Core/Delegate/Delegate.h"

class Scene;

// Signals are a wrapper for a list of delegates that implicitly take
// in Scene& and Entity as arguments. For example, Signal<int> needs
// to connect to a function like: void func(Scene&, Entity, int).
template <typename... Args>
class Signal {

public:

	template <typename T, void (T::* Function)(Scene&, Entity, Args...)>
	void Connect(T* instance)
	{
		Delegate<Scene&, Entity, Args...> delegate_ = Delegate<Scene&, Entity, Args...>();
		delegate_.Bind<T, Function>(instance);
		connections.push_back(delegate_);
	}

	///void Disconnect(SignalDelegate callback);

	void Emit(Scene& scene, Entity id, Args... args) const
	{
		for (Delegate<Scene&, Entity, Args...> d : connections)
			d(scene, id, args...);
	}

private:

	// It's okay if delegates are stored in the signal because if
	// one system is destroyed, all systems and their corresponding signals
	// are destroyed so there can't be any dangling pointers to deleted functions :D
	std::vector<Delegate<Scene&, Entity, Args...>> connections;

};