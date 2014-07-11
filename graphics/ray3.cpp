#include "ray3.h"

//using namespace rayspace;
ray3::ray3()
{
}

ray3::ray3(const Vec3& origin, const Vec3& direction)
{
	Origin = origin;
	Direction = direction;
}

ray3::ray3(const ray3& input)
{
	Origin = input.Origin;
	Direction = input.Direction;
}