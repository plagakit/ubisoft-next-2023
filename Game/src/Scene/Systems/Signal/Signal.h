#pragma once

#include <stdafx.h>

#include "Utils/Delegate.h"

class Signal {


public:

	template <typename T, void (T::* func)()>
	void Connect(T* instance)
	{
		auto delegate_ = Delegate();
		delegate_.Bind<T, func>(instance);
		connections.push_back(delegate_);
	}

	///void Disconnect(SignalDelegate callback);
	void Emit();

private:

	// It's okay if function pointers are stored in the signal because if
	// one system is destroyed, all systems and their corresponding signals
	// are destroyed so there can't be any dangling pointers to deleted functions :D
	std::vector<Delegate> connections;

};