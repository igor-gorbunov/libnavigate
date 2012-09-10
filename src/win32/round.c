#include <math.h>

double round(double x)
{
	if (x >= 0.)
		return floor(fabs(x) + 0.5);
	else
		return -floor(fabs(x) + 0.5);
}
