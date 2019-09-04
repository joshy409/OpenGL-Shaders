#include "math.h"

float mylerp(float a, float b, float t)
{
	return a + t * (b - a);
}

float invlerp(float a, float b, float t)
{
	return (t - a) / (b - a);
}
