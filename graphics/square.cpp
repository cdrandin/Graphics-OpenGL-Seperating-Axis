#include "square.h"

square::square(void)
{
	verticieslist[0] = ( Vec3( -1.0, 1.0, 0.0 ) );
	verticieslist[1] = ( Vec3( -1.0, -1.0, 0.0 ) );
	verticieslist[2] = ( Vec3( 1.0, -1.0, 0.0 ) );
	verticieslist[3] =( Vec3( 1.0, 1.0, 0.0 ) );
}

Vec3 square::perp (Vec3 &in)
{
	Vec3 temp(0,0,0);
	temp[0] = -in[1];
	temp[1] = in[0];
	return temp;
}

square::square(Vec3 list[4])
{
	for(int i = 0; i < 4; i++)
		verticieslist[i] = list[i];
	for (int i = 0; i < 4; i++)
	{
		int next = (i+1)%4;
		Vec3 edge = list[next] - list[i];
		Normalize(edge);
		edgenormals.push_back(ray3(list[i], perp(edge)));
	}
}

	
