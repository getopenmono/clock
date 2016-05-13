// This software is part of OpenMono, see http://developer.openmono.com
// Released under the MIT license, see LICENSE.txt
#if !defined(__clock_trigonometry_h)
#define __clock_trigonometry_h
#include <math.h>

namespace trigonometry {

float minutesToRadians (int minutes)
{
	int wrapped = minutes - 15;
	if (wrapped < 0) wrapped = 60 + wrapped;
	return wrapped / float(30.0 / M_PI);
}

float hoursToRadians (int hours)
{
	int wrapped = (hours % 12) - 3;
	if (wrapped < 0) wrapped = 12 + wrapped;
	return wrapped / float(6.0 / M_PI);
}

};

#endif // __clock_trigonometry_h
