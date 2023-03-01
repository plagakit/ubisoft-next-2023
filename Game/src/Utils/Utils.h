#pragma once

#include <stdafx.h>

class Utils {

public:
	static inline int Sign(int i)
	{
		return i < 0 ? -1 : i > 0;
	}

	static inline int Sign(float f)
	{
		return f < 0 ? -1 : f > 0;
	}

};