#include <stdafx.h>

#include "Core/Vector2/Vector2.h"
#include "Utils/Utils.h"

class Vector2Test {

public:
	static void RunTests()
	{
		// Equality tests
		assert(Vector2(0.0f, 0.0f) == Vector2(0.0f, 0.0f));
		assert(Vector2(1, 5) != Vector2(7, 4));
		assert(Vector2(0.0f, 0.00000001f).ApproxEqual(Vector2(0.0f, 0.0f)));
		assert(!Vector2(0.0f, 0.001f).ApproxEqual(Vector2(0.0f, 0.0f)));
		

		// Negation
		Vector2 negate = -Vector2(1, 1);
		assert(negate == Vector2(-1, -1));


		// Addition/subtraction
		assert(Vector2(1, 1) + Vector2(1, 2) == Vector2(2, 3));
		assert(Vector2(4, 5) - Vector2(6, 1) == Vector2(-2, 4));

		Vector2 add = Vector2(1, 1);
		add += Vector2(1, 2);
		assert(add == Vector2(2, 3));

		Vector2 subt = Vector2(4, 5);
		subt -= Vector2(6, 1);
		assert(subt == Vector2(-2, 4));


		// Scalar/vector multiplication
		assert(Vector2(1, 1) * 4.7f == Vector2(4.7f, 4.7f));
		assert(Vector2(2, -2) * Vector2(-2, 2) == Vector2(-4, -4));

		Vector2 smult = Vector2(1, 1);
		smult *= 4.7f;
		assert(smult == Vector2(4.7f, 4.7f));

		Vector2 vmult = Vector2(2, -2);
		vmult *= Vector2(-2, 2);
		assert(vmult == Vector2(-4, -4));


		// Scalar/vector divison
		assert((Vector2(1, 1) / 3.0f).ApproxEqual(Vector2(1 / 3.0f, 1 / 3.0f)));
		assert((Vector2(1, 1) / Vector2(3, 2)).ApproxEqual(Vector2(1 / 3.0f, 1 / 2.0f)));

		Vector2 sdiv = Vector2(1, 1);
		sdiv /= 3.0f;
		assert(sdiv.ApproxEqual(Vector2(1 / 3.0f, 1 / 3.0f)));

		Vector2 vdiv = Vector2(1, 1);
		vdiv /= Vector2(3, 2);
		assert(vdiv.ApproxEqual(Vector2(1 / 3.0f, 1 / 2.0f)));


		// Others
		Vector2 zero;
		Vector2 specialTriangle = Vector2(3, 4);
		Vector2 unit = Vector2(cosf(PI / 4), sinf(PI / 4));

		assert(Utils::Equalf(specialTriangle.Length(), 5.0f));
		assert(Utils::Equalf(specialTriangle.LengthSquared(), 25.0f));
		assert(Utils::Equalf(zero.Distance(specialTriangle), 5.0f));
		assert(Utils::Equalf(zero.DistanceSquared(specialTriangle), 25.0f));

		assert(Utils::Equalf(unit.Length(), 1.0f));
		assert((unit * 34).Normalized().ApproxEqual(unit));
		assert(unit.Rotated(-PI / 4).ApproxEqual(Vector2(1, 0)));
		assert(Utils::Equalf(unit.Atan2(), PI / 4));

	}

};

