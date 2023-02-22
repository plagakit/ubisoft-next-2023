#pragma once

#include <stdafx.h>

/* 
A class for using both free functions and member functions
(of possibly different types) as generic, type-safe delegates
which can be stored and invoked. Solves the problem of needing
to store functions of different types in the same list. A variable
amount of function arguments can be specified in the delegate's
template.
*/
template <typename... Args>
class Delegate
{
	/*
	The way these delegates work is by wrapping functions. When calling member functions,
	you need the instance of the class of the function in addition to its function pointer.
	In addition, you need to know the type of the class in the definition of the function
	pointer (ex. void (C::*)() -> C is there!), which means it can't be generic.

	Delegates converts the instance pointer into a void pointer when binding it (see Bind()).
	It then makes a generic void function by wrapping the function pointer with a static cast
	back to its original type (note how the Generalize functions are inlined). This is how the whole
	process would look like with a member function F of class C, to make it easier to understand:

	Upon creation:	m_function is nullptr							
	Upon Bind():	m_function is static_cast<C*>(void*)->*F	(made at compile-time with templates)
	Upon Invoke():	m_function (casts void*) and is C*->*F		(can actually call the function now!)

	During this whole process, m_function remains a GenericFunction and there's
	no weird shenanigans like dereferencing a null pointer or dynamically allocating
	memory (which I saw during my research). I'm proud of this! :D
	*/
	
	
	using GenericPtr = void*;
	using GenericFunction = void (*)(GenericPtr, Args...);
	
	// Converts a free function into a generic function by wrapping it
	template <void (*F)(Args...)>
	static inline void GeneralizeFree(GenericPtr unused, Args... args)
	{
		return (F)(args...);
	}
	
	// Converts a member function into a generic function by wrapping it
	template <class C, void (C::*F)(Args...)>
	static inline void GeneralizeMember(GenericPtr instance, Args... args)
	{
		// Cast it back into the original type and invoke
		return (static_cast<C*>(instance)->*F)(args...);
	}


public:
	Delegate() :
		m_instance(nullptr), m_function(nullptr)
	{}

	// Binds a free function to the delegate
	template <void (*F)(Args...)>
	void Bind()
	{
		m_instance = nullptr;
		m_function = &GeneralizeFree<F>;
	}

	// Binds a member function to the delegate
	template <typename T, void (T::*F)(Args...)>
	void Bind(T* instance)
	{
		m_instance = static_cast<GenericPtr>(instance);
		m_function = &GeneralizeMember<T, F>;
	}

	// Invokes the delegate, throws an error if not bound.
	void operator()(Args... args) const
	{
		assert("Delegate unbinded!" && m_function != nullptr);
		return m_function(m_instance, args...);
	}


private:
	GenericPtr m_instance;
	GenericFunction m_function;

};
