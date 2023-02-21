#pragma once

#include <stdafx.h>

class Delegate
{
	using GenericPtr = void*;
	using GenericFunction = void (*)(GenericPtr);

	/*
	template <void (*Function)(int)>
	static inline void FunctionStub(InstancePtr, int ARG0)
	{
		// we don't need the instance pointer because we're dealing with free functions
		return (Function)(ARG0);
	}
	*/

	
	template <class C, void (C::*F)()>
	static inline void Generalize(GenericPtr instance)
	{
		return (static_cast<C*>(instance)->*F)();
	}


public:
	Delegate() :
		m_instance(nullptr), m_function(nullptr)
	{}

	// Create a free delegate
	template<void (*F)()>
	static Delegate CreateFree()
	{
		return Delegate(nullptr, nullptr);
	}

	// Create a member function delegate
	template <typename T, void (T::*F)()>
	void Bind(T* instance)
	{
		m_instance = static_cast<GenericPtr>(instance);
		m_function = &Generalize<T, F>;
	}

	// Invoke the delegate
	void operator()()
	{
		assert("Delegate unbinded!" && m_function != nullptr);
		return m_function(m_instance);
	}


private:
	GenericPtr m_instance;
	GenericFunction m_function;

};
