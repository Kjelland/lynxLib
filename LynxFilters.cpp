#include "LynxFilters.h"

namespace LynxFilters
{
	const double LynxLowpass::_z = (1.0 / sqrt(2.0));

	LynxLowpass::LynxLowpass(double dt, double wc)
	{
		_dt = dt;
		_wc = wc;
		_c = dt * wc;

		_y = 0;
		_dy = 0;
		_d2y = 0;
	}

	LynxLowpass::~LynxLowpass()
	{
	}

	double LynxLowpass::update(double u)
	{
		if ((_c < 1) && (_c > 0))
		{
			_d2y = (u - _y)*_c*_c - 2.0*_z*_c*_dy;

			_dy += _d2y;
			_y += _dy;
			return _y;
		}

		return 0;
	}

}