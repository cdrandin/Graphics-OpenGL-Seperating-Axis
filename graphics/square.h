#ifndef _SQUARE_
#define _SQUARE_
#include <vector>
#include "ray3.h"
#include "vector.h"

class square
{
public:
	square(void);
	Vec3 verticieslist[4];
	square(Vec3 list[4]);
	Vec3 perp (Vec3 &in);
	std::vector<ray3> edgenormals;
};
#endif