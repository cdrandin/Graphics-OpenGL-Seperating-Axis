#include "vector.h"
#include <iostream>

//function for creating a vector
//input: 3 components of a vector
//outut: a vector representation of 3 components within an array
Vec3::Vec3(void)
{
	for(int i = 0; i < 3; i++)
		vec[i] = 0;
}
Vec3::Vec3(float a[3])
{
	for(int i = 0; i < 3; i++)
		vec[i] = a[i];
}
Vec3::Vec3(double a, double b, double c)
{
	vec[0] = a;
	vec[1] = b;
	vec[2] = c;
}
Vec3::Vec3(double *a)
{
	for(int i = 0; i < 3; i++)
		vec[i] = a[i];
}
//functions for changing the values of the vector
void Vec3::setx(double x)
{
	vec[0] = x;
}
void Vec3::sety(double y)
{
	vec[1] = y;
}
void Vec3::setz(double z)
{
	vec[2] = z;
}

//function for adding vectors
//input: 2 vectors to be added
//output: 1 vector that is vec1 + vec2
Vec3 Vec3::operator+(const Vec3 &v)
{
	Vec3 temp(0, 0, 0);
	for(int i = 0; i < 3; i++)
		temp.vec[i] = vec[i] + v.vec[i];
	return temp;
}

//function for subtracting vectors
//input: 2 vectors to be subtracted
//output: 1 vector that is vec1 - vec2
Vec3 Vec3::operator-(const Vec3 &v)
{
	Vec3 temp(0, 0, 0);
	for(int i = 0; i < 3; i++)
		temp.vec[i] = vec[i] - v.vec[i];
	return temp;
}

//function for scaler multiplication and division
//input: 1 vector and the scale
//output: 1 vector that is vector * or / scale
Vec3 Vec3::operator*(const double scaler)
{
	Vec3 temp(0, 0, 0);
	for(int i = 0; i < 3; i++)
		temp.vec[i] = vec[i] * scaler;
	return temp;
}
Vec3 Vec3::operator/(const double scaler)
{
	Vec3 temp(0, 0, 0);
	for(int i = 0; i < 3; i++)
		temp.vec[i] = vec[i] / scaler;
	return temp;
}

//functions for boolean check of 2 vectors
bool Vec3::operator==(const Vec3 &v)
{
	for(int i = 0; i < 3; i++)
		if(vec[i] != v.vec[i])
			return false;
		else
			//continue with the loop
	return true;
}
bool Vec3::operator!=(const Vec3 &v)
{
	for(int i = 0; i < 3; i++)
		if(vec[i] != v.vec[i])
			return true;
		else
			//continue with the loop
	return false;
}
void Vec3::operator=(float *a)
{
	for(int i = 0; i < 3; i++)
		vec[i] = a[i];
}

Vec3 operator *(double y, Vec3 x)
{
	return x * y;
}

//function for dot product
//input: 2 vectors to conduct a dot product
//output: 1 value in double that is the dot product of the 2 vectors
double Vec3::dotProduct(const Vec3 &v)
{
	double result = 0;
	for(int i = 0; i < 3; i++)
		result = result + (vec[i] * v.vec[i]);
	return result;
}

//function for vector cross product
//input: 2 vectors to do cross product and 1 vector to store the cross product
//output: 1 vector that is the cross product of the 2 vectors
void Vec3::crossProduct(const Vec3 &a, const Vec3 &b, Vec3 &c)
{	
	c.vec[0] = a.vec[1] * b.vec[2] - b.vec[1] * a.vec[2];
	c.vec[1] = -(a.vec[0] * b.vec[2] - b.vec[0] * a.vec[2]);
	c.vec[2] = a.vec[0] * b.vec[1] - b.vec[0] * a.vec[1];
}
//second method of vector cross product
//input: 1 vector to be cross product with current vector
//output: 1 vector that is the cross product of the 2 vectors
Vec3 Vec3::crossProduct(const Vec3 &a)
{
	Vec3 temp(0,0,0);
	temp.vec[0] = vec[1] * a.vec[2] - a.vec[1] * vec[2];
	temp.vec[1] = -(vec[0] * a.vec[2] - a.vec[0] * vec[2]);
	temp.vec[2] = vec[0] * a.vec[1] - a.vec[0] * vec[1];
	return temp;
}

//function for negating a vector
//input: The current vector
//output: the negation of the vector
void Vec3::negation()
{
	for(int i = 0; i < 3; i++)
		vec[i] = -vec[i];
}

//function for finding the length of a vector
//input: the current vector class vector
//output: the length of the vector
double Vec3::length()
{
	double length = 0;
	length = sqrt(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
	return length;
}

//function for finding the squared length of a vector
//input: the current vector class vector
//output: the squared length of the vector
double Vec3::squaredLength()
{
	double length = 0;
	length = vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2];
	return length;
}

//function to print the current results of the vector within the vector class
void Vec3::printresults()
{
	for(int i = 0; i < 3; i ++)
		std::cout<<vec[i]<<" ";
	std::cout<<"\n";
}

//bracket operator for vectors
double &Vec3::operator [](const size_t index)
{
	return vec[index];
}

//function to normalize a vector
void Normalize(Vec3 &v)
{
	for(int i = 0; i < 3; i++)
		v[i] = v[i]/v.length();
}