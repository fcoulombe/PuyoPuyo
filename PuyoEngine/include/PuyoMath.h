#ifndef PUYOMATH_H
#define PUYOMATH_H

#include <math.h>
#include "PuyoEngineTypes.h"

namespace PuyoEngine
{
	class Math
	{
	public:
		//const
		static const Real RADIAN;

		//functions
		static Real Sqrt(Real rhs) { return sqrt(rhs); }
		static Real DegreeToRadian(Real degree) { return degree*RADIAN; }
	};
}
#endif