#pragma once
#include <math.h>

namespace LynxFilters
{
	class LynxLowpass
	{
	public:
		LynxLowpass(double dt, double wc);
		~LynxLowpass();

		double update(double u);
		double y() { return _y; };

	private:
		double _y;
		double _dy;
		double _d2y;

		double _dt;
		double _wc;
		double _c;

		static const double _z;
	};

}