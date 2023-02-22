#pragma once

#include <stdafx.h>

#include "Core/Delegate/Delegate.h"

template <typename... Args>
class Signal {

public:

	template <typename T, void (T::* Function)(Args...)>
	void Connect(T* instance)
	{
		Delegate<Args...> delegate_ = Delegate<Args...>();
		delegate_.Bind<T, Function>(instance);
		connections.push_back(delegate_);
	}

	///void Disconnect(SignalDelegate callback);

	void Emit(Args... args)
	{
		for (Delegate<Args...> d : connections)
			d(args...);
	}

private:

	// It's okay if delegates are stored in the signal because if
	// one system is destroyed, all systems and their corresponding signals
	// are destroyed so there can't be any dangling pointers to deleted functions :D
	std::vector<Delegate<Args...>> connections;

};